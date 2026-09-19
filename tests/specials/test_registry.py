import json
import struct
import unittest
from pathlib import Path
from tools.lib.config import ROOT
from tools.lib.elf import Elf


class RegistryTests(unittest.TestCase):
    def test_compiled_target_registry(self):
        manifest=json.loads((ROOT/'build/build-manifest.json').read_text())
        elf=Elf(Path(manifest['work'])/'build/GALE01/main.elf')
        address,size,_=elf.symbols['abilities']
        self.assertEqual(size,104*60)
        rows=[struct.unpack('>15I',elf.read(address+i*60,60)) for i in range(104)]
        keys=[elf.string(row[1]) for row in rows]
        catalog = {r['id']: r for r in json.loads((ROOT/'data/specials.json').read_text())}
        for row in rows:
            entry = catalog[row[0]]
            self.assertEqual((entry['key'], entry['name'], entry['character'], entry['donor'], entry['slot']),
                             (elf.string(row[1]), elf.string(row[2]), row[3], row[4], row[5]))
        self.assertEqual(len(set(keys)),104)
        self.assertEqual(len({row[0] for row in rows}),104)
        self.assertEqual({row[4] for row in rows},set(range(27))-{11})
        for donor in set(row[4] for row in rows):
            self.assertEqual({row[5] for row in rows if row[4]==donor},{0,1,2,3})
        for row in rows:
            self.assertGreater(row[12],0)
            self.assertGreaterEqual(row[11],row[10])
            self.assertGreater(row[14],0)
            self.assertLessEqual(row[14],0x424)
