import unittest
from tools.lib.emulator import verify_special_log, verify_match_log, verify_extended_log

class EmulatorEvidenceTests(unittest.TestCase):
    def special_log(self):
        return '\n'.join([
            '[rogue] special_entry index=7 air=0 entered=1',
            '[rogue] special_cleanup index=7 air=0 restored=1',
            '[rogue] special_entry index=7 air=1 entered=1',
            '[rogue] special_cleanup index=7 air=1 restored=1',
            '[rogue] special_result index=7 won=1 entries=2 cleanups=2 failures=0',
            '[rogue] special_matrix_complete start=7 count=1 failures=0',
            '[rogue] native_scene=1 active=0'])
    def test_only_complete_native_evidence_passes(self):
        log=self.special_log()
        self.assertTrue(verify_special_log(log,7,1))
        self.assertFalse(verify_special_log(log.split('[rogue] special_matrix_complete')[0],7,1))
        with self.assertRaises(ValueError): verify_special_log(log.replace('air=1 entered=1','air=1 entered=0'),7,1)
        with self.assertRaises(ValueError): verify_special_log(log,7,2)
        with self.assertRaises(ValueError): verify_special_log(log+'\nMemory Empty\n in "sislib.c" on line 86.',7,1)
        with self.assertRaises(ValueError): verify_special_log(log.replace('failures=0','failures=1'),7,1)
        self.assertFalse(verify_special_log(log.replace('[rogue] native_scene=1 active=0',''),7,1))
    def test_match_completion_line_is_insufficient(self):
        with self.assertRaises(ValueError):
            verify_match_log('[rogue] match_qa_complete transitions=20 failures=0 phase=6\n[rogue] native_scene=1 active=0')

    def test_extended_gate_requires_actual_interrupt_and_stock_loss(self):
        log = self.special_log()
        with self.assertRaises(ValueError): verify_extended_log(log,7,1)
        log += '\n[rogue] special_interrupt index=7 restored=1'
        log += '\n[rogue] special_respawn index=7 stocks=98 restored=1 motion=42'
        with self.assertRaises(ValueError): verify_extended_log(log,7,1)
        log += '\n[rogue] special_ledge index=7 restored=1 motion=252'
        log += '\n[rogue] special_grab index=7 restored=1 linked=1'
        self.assertTrue(verify_extended_log(log,7,1))
        with self.assertRaises(ValueError): verify_extended_log(log.replace('stocks=98','stocks=99'),7,1)
        with self.assertRaises(ValueError): verify_extended_log(log+'\nUNHANDLED EXCEPTION',7,1)
