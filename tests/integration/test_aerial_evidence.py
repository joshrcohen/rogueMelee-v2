import unittest
from tools.lib.emulator import verify_aerial_log


class AerialEvidenceTests(unittest.TestCase):
    def test_completion_requires_landing_and_shared_owner_transitions(self):
        log='\n'.join([
            '[rogue] aerial_entry index=0 air=0 entered=1',
            '[rogue] aerial_cleanup index=0 air=0 restored=1',
            '[rogue] aerial_entry index=0 air=1 entered=1',
            '[rogue] aerial_cleanup index=0 air=1 restored=1',
            '[rogue] aerial_result index=0 won=1 entries=2 cleanups=2 failures=0',
            '[rogue] aerial_matrix_complete start=0 count=1 failures=0',
            '[rogue] native_scene=1 active=0',
            '[rogue] match_generation=1 resources=0'])
        with self.assertRaises(ValueError): verify_aerial_log(log,0,1)
        log+='\n[rogue] aerial_mixed index=0 valid=1'
        with self.assertRaises(ValueError): verify_aerial_log(log,0,1)
        for cancel in (0,1): log+=f'\n[rogue] aerial_landing index=0 cancel={cancel} lag=20 rate=1 expected=1 failures=0'
        self.assertTrue(verify_aerial_log(log,0,1))
        with self.assertRaises(ValueError): verify_aerial_log(log.replace('valid=1','valid=0'),0,1)
        with self.assertRaises(ValueError): verify_aerial_log(log,0,1,True)
