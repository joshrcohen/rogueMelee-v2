import json
import unittest
from tools.lib.config import ROOT
from tools.lib.migration import inventory


class InventoryTests(unittest.TestCase):
    def test_inventory_and_adapter_coverage(self):
        records=inventory()
        manifest=json.loads((ROOT/'integration/special_adapters.json').read_text())
        covered={e['evidence_sha256'] for d in manifest['files'].values() for e in d['edits']}
        for r in records:
            if all(c.startswith('excluded-') for c in r['categories']): continue
            if r['categories']==['special-interface']: continue
            changed=[l for l in r['changes'].splitlines() if not ('#include' in l and 'melee/rogue/' in l)]
            if not changed: continue
            self.assertIn(r['sha256'],covered,r['file']+' '+r['hunk'])

    def test_legacy_special_overlay_excludes_old_aerial_hooks(self):
        manifest=json.loads((ROOT/'integration/special_adapters.json').read_text())
        for d in manifest['files'].values():
            for e in d['edits']:
                self.assertNotIn('Rogue_Aerial','\n'.join(e['after']))
