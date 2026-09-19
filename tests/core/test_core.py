import unittest
from tools.lib.host import compile_test
from tools.lib.config import ROOT
from tools.generate_data import generate


class CoreTests(unittest.TestCase):
    def test_host_core(self):
        generate()
        sources = [ROOT/'tests/core/core_test.c'] + sorted((ROOT/'src/core').glob('*.c'))
        sources += [ROOT/'src/upgrades/upgrade_registry.c',ROOT/'src/encounters/encounter_registry.c']
        compile_test('core_test',sources)
