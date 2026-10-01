#include "decls.h"
#include "imports.h"

// entry: 00422dd0
// name : relax_fprset_record
// size : 281
// sig  : void __cdecl relax_fprset_record(layout_record *item,int pass)


int __cdecl relax_fprset_record(layout_record *item,int pass)

{
  unsigned char _frec_40[64];
#define movi_item (*(layout_record *)(_frec_40 + 0))
#define movi_rec (*(psd *)(_frec_40 + 32))
#define new_size (*(char *)(_frec_40 + 56))
  char size_so_far;
  short code_size;
  
  new_size = '\x02';
  movi_item.op = OP_MOVI;
  if (pass == 0) {
    movi_rec.op = OP_MOVI;
    movi_rec.flg = '\x02';
    movi_rec.misc = '\0';
    code_size = compute_record_code_size(&movi_rec);
    item->part_size[0] = (char)code_size;
  }
  movi_item.size = item->part_size[0];
  movi_item.flg = '\x02';
  if ((item->flg & 3) == 3) {
    movi_item.value = 0x80000;
  }
  else {
    movi_item.value = -0x180001;
  }
  movi_item.labels = (label_ref *)0x0;
  relax_movi_record(&movi_item,pass);
  item->size = item->size - (item->part_size[0] - movi_item.size);
  size_so_far = movi_item.size + new_size;
  item->part_size[0] = movi_item.size;
  new_size = size_so_far + '\x04';
  if ((item->flg & 0x40) != 0) {
    new_size = size_so_far + '\x02';
  }
  if (pass == 0) {
    g_layout_shrink_pass0 = g_layout_shrink_pass0 + ((int)item->size - (int)new_size);
  }
  else {
    g_layout_shrink_pass1 = g_layout_shrink_pass1 + ((int)item->size - (int)new_size);
  }
  item->size = new_size;
  return;
#undef movi_item
#undef movi_rec
#undef new_size
}
