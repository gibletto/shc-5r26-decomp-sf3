from pathlib import Path
import os,sys,tempfile,shutil,unittest
repo=Path(__file__).resolve().parents[1]
root=Path(os.environ.get('SHC_STAGE_REG_FIXTURES', str(repo/'tests/stage_reg_fixtures')))
sys.path.insert(0,str(repo/'tools'));import stage_reg_edit as p
codec=Path(os.environ.get('SHC_STAGE_CODEC_DIR', str(repo/'tools')))
class Checks(unittest.TestCase):
 def test_callee_implicit_writes_rejected(self):
  for word in (0xc701,0x8431,0x8541,0xc401,0xc501,0xc601):self.assertTrue(p.call_scan_barrier(word,0))
 def test_callee_postincrement_and_control_rejected(self):
  for word,reg in ((0x6136,3),(0x043f,3),(0x043f,4),(0xc300,2),(0x002b,2),(0x001b,2)):
   self.assertTrue(p.call_scan_barrier(word,reg))
 def test_unique_register_permutation(self):
  old={0:0x6e6f,2:0x4700,4:0x6373,6:0x33bc};new={0:0x62b3,2:0x4700,4:0x327c,6:0x6e6f}
  self.assertEqual(p.align_register_schedule(old,new),{0:6,2:2,4:0,6:4})
 def test_no_displacement_mask(self):
  for a,b in [(0xd201,0xd202),(0x9123,0x9124),(0x8121,0x8122),(0x7123,0x7124),(0xa000,0xa001)]:
   self.assertNotEqual((a^b)&~p.reg_mask(a),0)
 def test_branch_permutation_rejected(self):
  with self.assertRaises(p.Ineligible):p.align_register_schedule({0:0xa000,2:0x6373},{0:0x6373,2:0xa000})
 def test_repeated_opcode_permutation_rejected(self):
  with self.assertRaises(p.Ineligible):p.align_register_schedule({0:0x6373,2:0x6263,4:0x4000},{0:0x4000,2:0x6373,4:0x6263})
 @unittest.skipUnless((root/'score_pilot_v2/edited.sub').is_file(), 'retained stage fixtures not configured')
 def test_stale_source_rejected(self):
  with tempfile.TemporaryDirectory(dir=root) as folder:
   folder=Path(folder);source=folder/'bad.sub';raw=bytearray((root/'score_pilot_v2/edited.sub').read_bytes());raw[-1]^=1;source.write_bytes(raw)
   with self.assertRaises((p.Ineligible,ValueError)):p.apply(source,root/'score_pilot_v2/PATCH.tsv',folder/'out.sub',codec)
   self.assertFalse((folder/'out.sub').exists())
 @unittest.skipUnless((root/'score_pilot_v2/edited.sub').is_file(), 'retained stage fixtures not configured')
 def test_tampered_field_rejected(self):
  with tempfile.TemporaryDirectory(dir=root) as folder:
   folder=Path(folder);source=root.parent/'stage_targets01/eff16_current_codec/unit.sub'
   shutil.copyfile(root/'score_pilot_v2/PATCH_BINDING.txt',folder/'PATCH_BINDING.txt')
   patch=(root/'score_pilot_v2/PATCH.tsv').read_text().replace('ea1.base','line',1);(folder/'PATCH.tsv').write_text(patch)
   with self.assertRaises(p.Ineligible):p.apply(source,folder/'PATCH.tsv',folder/'out.sub',codec)
   self.assertFalse((folder/'out.sub').exists())
 @unittest.skipUnless((root/'score_pilot_v2/edited.sub').is_file(), 'retained stage fixtures not configured')
 def test_exact_reapply(self):
  with tempfile.TemporaryDirectory(dir=root) as folder:
   out=Path(folder)/'out.sub';p.apply(root.parent/'stage_targets01/eff16_current_codec/unit.sub',root/'score_pilot_v2/PATCH.tsv',out,codec)
   self.assertEqual(out.read_bytes(),(root/'score_pilot_v2/edited.sub').read_bytes())
if __name__=='__main__':unittest.main()
