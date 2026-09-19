import re
import struct
import unittest
from tools.generate_ui import generate
from tools.lib.config import ROOT

class NativeAssetTests(unittest.TestCase):
    def test_authored_archive_graph_and_gpu_alignment(self):
        generate()
        raw=(ROOT/'build/assets/RogueUi.dat').read_bytes()
        size,body,relocs,publics,external=struct.unpack_from('>5I',raw)
        self.assertEqual(size,len(raw))
        self.assertEqual((publics,external),(1,0))
        data=raw[32:32+body]
        u=lambda at:struct.unpack_from('>I',data,at)[0]
        pointers=struct.unpack_from('>'+str(relocs)+'I',raw,32+body)
        self.assertEqual(len(pointers),len(set(pointers)))
        for at in pointers:
            self.assertEqual(at%4,0)
            self.assertLess(at+3,body)
            self.assertLess(u(at),body)
        joint=u(8);seen=set()
        while joint:
            self.assertNotIn(joint,seen);seen.add(joint)
            self.assertTrue(u(joint+4)&0x40000,'Opaque JOBJ must participate in native draw pass')
            dobj=u(joint+16);pobj=u(dobj+12)
            display=u(pobj+16)
            self.assertEqual((32+display)%32,0)
            self.assertEqual(data[display],0xA0)
            count=struct.unpack_from('>H',data,display+1)[0]
            blocks=struct.unpack_from('>H',data,pobj+14)[0]
            self.assertGreaterEqual(blocks*32,3+count*12)
            joint=u(joint+12)
        self.assertEqual(len(seen),46)
        embedded=bytes(int(x,16) for x in re.findall(r'0x([0-9a-f]{2})', (ROOT/'src/platform/melee/ui_asset_data.c').read_text()))
        self.assertEqual(embedded,raw)
