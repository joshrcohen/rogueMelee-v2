import struct
import tempfile
import unittest
from pathlib import Path
from tools.lib.movie import write_ui_movie


class MovieTests(unittest.TestCase):
    def test_controller_stream_has_exact_header_and_button_alignment(self):
        with tempfile.TemporaryDirectory() as folder:
            root = Path(folder)
            (root/'input.iso').write_bytes(b'fixture')
            raw = write_ui_movie(root/'input.iso', root/'input.dtm').read_bytes()
            self.assertEqual(len(raw), 256 + 1000 * 8)
            self.assertEqual(raw[:4], b'DTM\x1a')
            self.assertEqual(struct.unpack_from('<Q',raw,21)[0],1000)
            for frame, mask in [(299,0),(300,4),(310,0),(400,8),(450,512),(500,2)]:
                self.assertEqual(struct.unpack_from('<H',raw,256+frame*8)[0],0x4000|mask)
