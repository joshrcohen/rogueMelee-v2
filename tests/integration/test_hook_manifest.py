import unittest
from tools.lib.integration import hooks, validate
from tools.lib.config import ROOT


class HookTests(unittest.TestCase):
    def test_real_sites(self):
        validate(hooks(), ROOT / '.cache/deps/melee')

    def test_duplicate_site_rejected(self):
        entries = hooks()
        copy = dict(entries[0], id='another_owner')
        with self.assertRaises(ValueError):
            validate(entries + [copy], ROOT / '.cache/deps/melee')

    def test_wrong_original_rejected(self):
        entries = hooks()
        entries[0]['anchor'] = 'not a retail source statement'
        with self.assertRaises(ValueError):
            validate(entries, ROOT / '.cache/deps/melee')
