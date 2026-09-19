import random
import subprocess
import tempfile
import unittest
from pathlib import Path
from tools.lib.config import ROOT


class DeltaTests(unittest.TestCase):
    def test_pinned_tool_reconstructs_modified_and_grown_input(self):
        tool = ROOT/'build/tools/xdelta3.exe'
        if not tool.exists():
            self.skipTest('Pinned xdelta3 has not been built; package builds it before release')
        with tempfile.TemporaryDirectory() as folder:
            root = Path(folder)
            original = random.Random(7).randbytes(262144)
            modified = original[:65536]+b'replacement'*100+original[66536:]+b'new ending'
            (root/'source').write_bytes(original)
            (root/'modified').write_bytes(modified)
            subprocess.run([tool,'-e','-s',root/'source',root/'modified',root/'patch'],check=True)
            subprocess.run([tool,'-d','-s',root/'source',root/'patch',root/'result'],check=True)
            self.assertEqual((root/'result').read_bytes(),modified)
            self.assertLess((root/'patch').stat().st_size,4096)
