"""OFB serialized grammar tests; no native stage execution."""
import sys, struct, unittest
from pathlib import Path
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tools'))
import stage_ofb as codec
u16=lambda x:struct.pack('<H',x)
u32=lambda x:struct.pack('<I',x)
refs=u32(3)+u16(1)+u16(0)+u16(65535)

class OfbTests(unittest.TestCase):
    def check(self,data):
        self.assertFalse([r.warning for r in codec.decode(data) if r.warning])
        self.assertEqual(codec.encode(codec.dumps(data)),data)
    def test_all_serialized_forms(self):
        bodies={0x10:u32(42)+u32(43),0x11:b'\x08'+u32(44)+u16(45)+u16(46)+u32(47)+u32(48),
                0x14:u32(49)+u32(50),0x20:b'\x00',0x21:b'\x06'+u32(51)+u16(52),
                0x27:b'\x02\xff\xfe'+u32(53)+u32(54),0x28:b'\x02\xff'+u32(55)+u32(56),
                0x2e:b'\x02\xff'}
        for op in (0x18,0x19,0x1a,0x1b):bodies[op]=u16(57)
        for op in (0x22,0x24,0x23,0x25,0x26,0x29,0x2b):
            bodies[op]=b'\x06'+(b'\xff' if op in (0x25,0x26) else b'')+u32(58)+u32(59)+refs+(u16(60) if op in (0x22,0x24) else b'')
        for op in (0x2a,0x2c):bodies[op]=b'\x02\xff'+u32(61)+refs
        for op in (0x8e,0x92,0x94,0x96):bodies[op]=b'\x04'+u32(62)+u16(63)+b'\xff'
        for op,body in bodies.items():
            with self.subTest(op=op):self.check(bytes([op])+body)
        self.check(b''.join(bytes([op])+body for op,body in bodies.items()))
    def test_unknown_and_truncated_lossless(self):
        for data in (b'\xff\x00\x00',b'\x1b\x01',b'\x2a\x02'):
            self.assertTrue(codec.decode(data)[0].warning)
            self.assertEqual(codec.encode(codec.dumps(data)),data)
    def test_reinterpretation_rejected(self):
        data=b'\x2a\x02\x02'+u32(42)+refs
        text=codec.dumps(data)
        with self.assertRaisesRegex(ValueError,'grammar differs'):
            codec.encode(text.replace('\tlabels.count\tu32\t3','\tlabels.count\tu32\t2'))
        with self.assertRaisesRegex(ValueError,'grammar differs'):
            codec.encode(text.replace('\topcode\tu8\t42','\topcode\tu8\t39'))
    def test_scalar_edit(self):
        data=b'\x2a\x02\x02'+u32(42)+refs
        edited=codec.encode(codec.dumps(data).replace('\tvalue\ti32\t42','\tvalue\ti32\t43'))
        self.assertEqual(sum(a!=b for a,b in zip(data,edited)),1)

if __name__=='__main__':unittest.main(verbosity=2)
