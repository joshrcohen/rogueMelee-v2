import struct
import tempfile
import unittest
from pathlib import Path
from tools.lib.image_build import assemble, layout


class ImageAssemblyTests(unittest.TestCase):
    def test_growing_dol_preserves_filesystem_and_payload(self):
        with tempfile.TemporaryDirectory() as folder:
            root = Path(folder)
            original, executable, output = [root / x for x in ('source.iso', 'main.dol', 'output.iso')]
            image = bytearray(0x20000)
            struct.pack_into('>4I', image, 0x420, 0x3000, 0x4000, 32, 32)
            struct.pack_into('>I', image, 0x3000, 256)
            struct.pack_into('>I', image, 0x3090, 256)
            struct.pack_into('>3I', image, 0x4000, 0x01000000, 0, 2)
            struct.pack_into('>3I', image, 0x400c, 0, 0x18000, 1024)
            image[0x4018:0x4020] = b'data\0\0\0\0'
            image[0x18000:0x18400] = b'R' * 1024
            original.write_bytes(image)
            grown = bytearray(0x6000)
            struct.pack_into('>I', grown, 0, 256)
            struct.pack_into('>I', grown, 0x90, len(grown) - 256)
            executable.write_bytes(grown)
            address = assemble(original, executable, output)
            self.assertGreaterEqual(address, 0x4020)
            self.assertEqual(original.read_bytes(), image)
            rebuilt = output.read_bytes()
            self.assertEqual(rebuilt[0x4000:0x4020], image[0x4000:0x4020])
            self.assertEqual(rebuilt[0x18000:0x18400], b'R' * 1024)
            self.assertEqual(rebuilt[address:address + len(grown)], grown)
            with self.assertRaises(ValueError):
                assemble(original, executable, original)
