import hashlib
import json
import shutil
import subprocess
import tomllib
from .config import ROOT
from .deps import ensure
from .process import run


def hooks():
    return tomllib.loads((ROOT / 'integration/hook_manifest.toml').read_text())['hook']


def validate(entries, upstream):
    ids, sites = set(), set()
    for h in entries:
        if h['id'] in ids or (h['file'], h['anchor']) in sites:
            raise ValueError('Duplicate hook id or site: ' + h['id'])
        ids.add(h['id']); sites.add((h['file'], h['anchor']))
        source = (upstream / h['file']).read_text(encoding='utf-8')
        if source.count(h['anchor']) != 1:
            raise ValueError('Expected unique original source at hook ' + h['id'])
        if not h.get('abi') or not h.get('owner'):
            raise ValueError('Missing hook ownership/ABI')


def prepare(profile):
    clean = ensure('melee')
    entries = hooks()
    validate(entries, clean)
    digest = hashlib.sha256(profile.encode())
    for path in [ROOT / 'integration/hook_manifest.toml'] + sorted((ROOT / 'src').rglob('*')):
        if path.is_file():
            digest.update(path.relative_to(ROOT).as_posix().encode())
            digest.update(path.read_bytes())
    work = ROOT / 'build/work' / digest.hexdigest()[:16]
    if not work.exists():
        run(['git', 'worktree', 'add', '--detach', work, 'HEAD'], clean)
    for h in entries:
        p = work / h['file']
        # Rebuild each retail file from the exact clean source, never cumulative edits.
        source = (clean / h['file']).read_text(encoding='utf-8')
        for same in entries:
            if same['file'] == h['file']:
                source = source.replace(same['anchor'], same['replacement'], 1)
        source = '#include <melee/rogue/platform/melee/rogue_hooks.h>\n' + source
        p.write_text(source, encoding='utf-8')
    shutil.copytree(ROOT / 'src', work / 'src/melee/rogue', dirs_exist_ok=True)
    source = (clean / 'configure.py').read_text(encoding='utf-8')
    objects = ',\n'.join('            Object(Equivalent, "melee/rogue/' + p.relative_to(ROOT / 'src').as_posix() + '")' for p in sorted((ROOT / 'src').rglob('*.c')))
    source = source.replace('config.libs = [', 'config.libs = [\n    MeleeLib("rogueMelee", [\n' + objects + '\n    ]),', 1)
    source = source.replace('config.libs = [', 'cflags_base.append("-DROGUE_DEBUG=' + ('1' if profile == 'debug' else '0') + '")\nconfig.libs = [', 1)
    (work / 'configure.py').write_text(source,encoding='utf-8')
    target = work / 'orig/GALE01/sys/main.dol'
    target.parent.mkdir(parents=True,exist_ok=True)
    shutil.copyfile(clean / 'orig/GALE01/sys/main.dol', target)
    return work
