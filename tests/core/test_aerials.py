import unittest
from tools.lib.config import ROOT
from tools.lib.host import compile_test


class AerialTests(unittest.TestCase):
    def test_acquisition_and_independent_disable(self):
        sources=[ROOT/'tests/core/aerial_test.c']+sorted((ROOT/'src/core').glob('*.c'))
        sources += [ROOT/'src/upgrades/upgrade_registry.c',ROOT/'src/encounters/encounter_registry.c']
        sources += sorted((ROOT/'src/combat/specials').glob('*.c'))
        sources += sorted((ROOT/'src/combat/aerials').glob('*.c'))
        compile_test('aerials_test',sources)
        compile_test('aerials_disabled_test',sources,('ROGUE_ENABLE_AERIALS=0',))
