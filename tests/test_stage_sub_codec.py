"""Meaningful serialized-format coverage; no compiler invocations."""
import random
import struct
import sys
import tempfile
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'tools'))
import stage_sub as codec

U16 = lambda n: struct.pack('<H', n)
U32 = lambda n: struct.pack('<I', n)
LOCATION = U16(0x1234) + U16(0xfedc) + U32(0xdeadbeef)


class CodecTests(unittest.TestCase):
    def complete(self, data):
        records = codec.decode(data)
        self.assertFalse([r.warning for r in records if r.warning])
        text = codec.dumps(data)
        self.assertEqual(codec.encode(text), data)
        return records, text

    def test_all_fixed_record_formats(self):
        formats, _ = codec.load_tables()
        lengths = {1: 0, 2: 16, 3: 4, 4: 2, 5: 6, 6: 5, 7: 0, 10: 4, 11: 12, 12: 2}
        for fmt, length in lengths.items():
            opcode = formats.index(fmt)
            with self.subTest(fmt=fmt):
                self.complete(bytes([opcode]) + bytes(range(0xff-length, 0xff)))

    def test_pseudo_full_raw_bits_and_unused_words(self):
        refs = U32(3) + U16(0x1234) + U16(0) + U16(0xffff)
        bodies = {
            0x22: U16(0xfe01),
            0x23: b'\xff' + U16(0xabcd) + b'\xff',
            0x24: U16(0xabcd) + b'\xfe',
            0x25: U16(0xabcd) + b'\xfd',
            0x26: U16(0xabcd) + b'\xfc',
            0x27: bytes([0xff,0xff,14,3,0xa5]) + U32(0xfedcba98) + U32(0x76543210) + U32(0xffffffff),
            0x28: bytes([0xff,14,0xa5]) + U32(0xfedcba98) + U32(0x76543210) + U32(0xffffffff),
            0x29: bytes([3,0xa5]) + U32(0xfedcba98) + refs,
            0x2a: bytes([0xff,0xff,3,0xa5]) + U32(0xfedcba98) + refs,
            0x2b: bytes([0xff,0xe3,0xa5]) + U32(0xfedcba98) + refs,
            0x2c: bytes([0xff,0xff,3,2,0xa5]) + U32(0xfedcba98) + refs,
            0x2e: bytes([0xff,2,14]),
            0x30: bytes([7]),
            0x31: bytes([8]),
        }
        for op, body in bodies.items():
            with self.subTest(op=op):
                self.complete(bytes([op]) + LOCATION + body)

    def test_all_operands_and_sizes(self):
        for size in range(3):
            payloads = {
                0: b'', 1:b'\x03', 2:b'\x0e', 3:b'\x0f', 4:b'\x0f',
                5:b'\x01', 6:b'\x00',
                7:bytes([0x81])*(1<<size) + U32(2) + U16(0x1234) + U16(0x8765),
                8:b'\x0e' + U16(0xfff8), 9:b'\xe3', 10:U16(0xfff8),
                11:U32(0xf1234567)+U32(1)+U16(0x9876), 12:b'\x03', 15:b'\x04',16:b'\x05',
            }
            for kind, payload in payloads.items():
                with self.subTest(size=size, kind=kind):
                    operand = bytes([kind | 0xe0]) + payload
                    self.complete(b'\x40'+LOCATION+bytes([0xfc|size,0xff,2])+operand+b'\x01\x02')

    def test_random_valid_streams_and_edit(self):
        rng = random.Random(26)
        data = b''.join(b'\x40'+LOCATION+b'\xe2\xff\x02\x01'+bytes([rng.randrange(16)])
                        +b'\x01'+bytes([rng.randrange(16)]) for _ in range(100))
        records, text = self.complete(data)
        row = next(line for line in text.splitlines() if line.startswith('0\t') and '\tea2.base\t' in line)
        columns = row.split('\t')
        old = int(columns[-1],0)
        columns[-1] = str((old+1)%16)
        edited = codec.encode(text.replace(row, '\t'.join(columns),1))
        self.assertEqual([i for i,(a,b) in enumerate(zip(data,edited)) if a!=b], [15])
        self.complete(edited)

    def test_record_reorder(self):
        first = b'\x18'+U16(1)+U32(0)
        second = b'\x18'+U16(2)+U32(0)
        text = codec.dumps(first+second)
        header = [line for line in text.splitlines() if line.startswith('#') or line.startswith('record\t')]
        rows = [line for line in text.splitlines() if line and not line.startswith('#') and not line.startswith('record\t')]
        reordered = '\n'.join(header+[row for row in rows if row.startswith('1\t')]+[row for row in rows if row.startswith('0\t')])+'\n'
        self.assertEqual(codec.encode(reordered), second+first)

    def test_opaque_and_malformed_are_lossless_not_complete(self):
        for data in (b'\x00arbitrary\x00\xff', b'\x40\x01', b'\x40'+LOCATION+b'\x03\x00\x01\x07'):
            self.assertTrue(any(record.warning for record in codec.decode(data)))
            self.assertEqual(codec.encode(codec.dumps(data)),data)
        data=bytes(range(256))*3
        self.assertEqual(codec.encode(codec.dumps(data,opaque=True)),data)
        self.assertEqual(codec.encode(codec.dumps(b'')),b'')

    def test_invalid_edit_rejected(self):
        _, text = self.complete(b'\x40'+LOCATION+b'\x02\x00\x02\x01\x02\x01\x03')
        with self.assertRaises(ValueError):
            codec.encode(text.replace('\tea2.base\tu8\t0x03','\tea2.base\tu8\t999'))
        with self.assertRaises(ValueError):
            codec.encode(text.replace('0\t0xf\tea2.base','0\t0x10\tea2.base'))

    def test_inconsistent_count_type_and_form_edits_rejected(self):
        _, text = self.complete(b'\x40'+LOCATION+b'\x02\x00\x02\x01\x02\x01\x03')
        for old,new in (('\toperand_count\tu8\t0x02','\toperand_count\tu8\t0x01'),
                        ('\tea1.type_raw\tu8\t0x01','\tea1.type_raw\tu8\t0x08'),
                        ('\topcode\tu8\t0x40','\topcode\tu8\t0x2a')):
            with self.subTest(old=old),self.assertRaisesRegex(ValueError,'grammar differs'):
                codec.encode(text.replace(old,new,1))
        # Same schema instruction edit is deliberately permitted.
        changed=codec.encode(text.replace('\topcode\tu8\t0x40','\topcode\tu8\t0x85',1))
        self.assertEqual(changed[0],0x85)

    def test_inconsistent_relocation_count_rejected(self):
        data=b'\x2a'+LOCATION+b'\x02\x00\x03\x07'+U32(42)+U32(2)+U16(1)+U16(2)
        _,text=self.complete(data)
        with self.assertRaisesRegex(ValueError,'grammar differs'):
            codec.encode(text.replace('\tlabels.count\tu32\t0x00000002','\tlabels.count\tu32\t0x00000001'))

    def test_cli_rejects_input_output_alias_and_existing_output(self):
        with tempfile.TemporaryDirectory(dir=Path(__file__).parent) as tmp:
            path=Path(tmp)/'input.sub'
            output=Path(tmp)/'existing.tsv'
            path.write_bytes(b'\x1e')
            output.write_text('preserved')
            for command in ('dump','encode'):
                with self.assertRaisesRegex(ValueError,'different files'):
                    codec.main([command,str(path),str(path),'--force'])
                with self.assertRaisesRegex(ValueError,'output already exists'):
                    codec.main([command,str(path),str(output)])
            self.assertEqual(path.read_bytes(),b'\x1e')
            self.assertEqual(output.read_text(),'preserved')


if __name__ == '__main__':
    unittest.main(verbosity=2)
