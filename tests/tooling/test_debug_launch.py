import unittest
from tools.lib.debug_launch import options, header

class DebugLaunchTests(unittest.TestCase):
    def test_full_width_seed_and_registry_resolution(self):
        fixture = options(2**64-1,'encounter','elite_juggernaut','fox_down','Mario')
        self.assertEqual(fixture['recipient'],8)
        self.assertEqual(fixture['encounter'],2)
        self.assertEqual(fixture['special'],8)
        self.assertIn('4294967295U',header(fixture))
    def test_invalid_input_rejected_before_build(self):
        for params in [dict(seed=-1),dict(seed=2**64),dict(recipient='unknown'),dict(special='fake'),dict(encounter='fake'),dict(aerials=['fake']),dict(aerials=['fox_nair','mario_nair'])]:
            with self.assertRaises(ValueError): options(**params)

    def test_independent_aerial_launch_slots(self):
        fixture=options(aerials=['fox_nair','link_dair'])
        self.assertEqual(fixture['scene'],'encounter')
        self.assertEqual(fixture['aerials'],[11,0,0,0,35])
        self.assertIn('ROGUE_LAUNCH_AERIALS { 11, 0, 0, 0, 35 }',header(fixture))
