from pathlib import Path
import copy,sys,types,unittest
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'tools'))
import stage_reg_edit as p
import stage_reg_probe as probe

class Checks(unittest.TestCase):
    def test_direct_bijection(self):
        items=[(types.SimpleNamespace(index=i),[('ea1.base',4,0)]) for i in (10,20)]
        got=p.direct_occurrences(0x6233,items,[0,4],{0:0x6243,4:0x6253},{10:4,20:0})
        self.assertEqual([x[2] for x in got],[[4],[0]])
    def test_missing_duplicate_and_outside_maps_rejected(self):
        items=[(types.SimpleNamespace(index=i),[]) for i in (10,20)]
        for mapping in (None,{10:0},{10:0,20:0},{10:0,20:8}):
            with self.assertRaises(p.Ineligible):p.direct_occurrences(0x6233,items,[0,4],{0:0x6243,4:0x6253},mapping)
    def test_clean_single_nibble(self):
        self.assertEqual(probe.clean_probe(bytes.fromhex('0009623300096233'),bytes.fromhex('0009623300096223'),0,8,0x6233,4,3,2,{2,6}),6)
    def test_other_effects_rejected(self):
        before=bytes.fromhex('0009623300096233')
        for text in ('0009623300096233','0009622300096223','0009623300096222','00096233000962230009','00096233000b6223'):
            with self.assertRaises(p.Ineligible):probe.clean_probe(before,bytes.fromhex(text),0,8,0x6233,4,3,2,{2,6})
    def test_outside_group_and_wrong_old_rejected(self):
        before=bytes.fromhex('0009623300096233');after=bytes.fromhex('0009623300096223')
        for end,old,offsets in ((6,3,{2,6}),(8,4,{2,6}),(8,3,{2})):
            with self.assertRaises(p.Ineligible):probe.clean_probe(before,after,0,end,0x6233,4,old,2,offsets)
    def test_section_address_symbol_order_endian_rejected(self):
        section=types.SimpleNamespace(name='P',address=0,lenght=2,align=2,relocs=[])
        old=types.SimpleNamespace(sections=[section],loc_syms=['a','b'],ext_syms=[],endian='big')
        self.assertTrue(probe.native_metadata_equal(old,copy.deepcopy(old),None))
        for mutate in ('address','symbols','endian'):
            new=copy.deepcopy(old)
            if mutate=='address':new.sections[0].address=2
            if mutate=='symbols':new.loc_syms.reverse()
            if mutate=='endian':new.endian='little'
            self.assertFalse(probe.native_metadata_equal(old,new,None))

if __name__=='__main__':unittest.main()
