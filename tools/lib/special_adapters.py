"""Named, baseline-checked special compatibility source overlay.

This consumes repository-owned adapter definitions, never a legacy checkout or
numbered patch script. All modified callsites dispatch to the platform facade.
"""
import hashlib
import json
from .config import ROOT


def apply(clean, work):
    manifest=json.loads((ROOT/'integration/special_adapters.json').read_text())
    for name, definition in manifest['files'].items():
        text=(clean/name).read_text(encoding='utf-8')
        if hashlib.sha256(text.encode()).hexdigest()!=definition['base_sha256']:
            raise ValueError('Special adapter baseline differs: '+name)
        lines=text.splitlines()
        occupied=set()
        for edit in definition['edits']:
            start=edit['line']; old=edit['before']
            if lines[start:start+len(old)]!=old:
                raise ValueError('Special adapter original mismatch: '+name+' '+str(start))
            for index in range(start,start+max(1,len(old))):
                if index in occupied:
                    raise ValueError('Overlapping special adapter sites: '+name)
                occupied.add(index)
        for edit in sorted(definition['edits'],key=lambda e:e['line'],reverse=True):
            start=edit['line']; lines[start:start+len(edit['before'])]=edit['after']
        result='#include <melee/rogue/platform/melee/specials/special_engine.h>\n'+'\n'.join(lines)+'\n'
        if 'Rogue_Aerial' in result:
            raise ValueError('Aerial code reached special overlay')
        (work/name).write_text(result,encoding='utf-8')
