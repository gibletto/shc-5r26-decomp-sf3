#include "decls.h"
#include "imports.h"

// entry: 0041d95e
// name : expand_fprset_record
// size : 937
// sig  : void __cdecl expand_fprset_record(psd *rec)


int __cdecl expand_fprset_record(psd *rec)

{
  unsigned char _frec_20[32];
#define movi_rec (*(psd *)(_frec_20 + 0))
  ea *operand;
  int last_ix;
  byte orig_flg;
  
  orig_flg = rec->flg;
  set_psd_record(g_expanded_records + g_expanded_record_count,0x9d,'\x02','\0','\0',0,rec->expno,
                 rec->filno,rec->linno);
  operand = alloc_ea_operand('\x10','h',0xff,0,(label_ref *)0x0);
  g_expanded_records[g_expanded_record_count].ea1 = operand;
  operand = alloc_ea_operand('\x01',rec->ea1->base,0xff,0,(label_ref *)0x0);
  g_expanded_records[g_expanded_record_count].ea2 = operand;
  g_expanded_record_count = g_expanded_record_count + 1;
  if ((rec->flg & 3) == 3) {
    set_psd_record(&movi_rec,'*','\x02','\0','\0',0,rec->expno,rec->filno,rec->linno);
    movi_rec.ea1 = alloc_ea_operand('\a',0xff,0xff,0x80000,(label_ref *)0x0);
    movi_rec.ea2 = alloc_ea_operand('\x01',rec->ea2->base,0xff,0,(label_ref *)0x0);
    expand_movi_record(&movi_rec);
    set_psd_record(g_expanded_records + g_expanded_record_count,0x81,'\x02','\0','\0',0,rec->expno,
                   rec->filno,rec->linno);
    operand = alloc_ea_operand('\x01',rec->ea2->base,0xff,0,(label_ref *)0x0);
    g_expanded_records[g_expanded_record_count].ea1 = operand;
    operand = alloc_ea_operand('\x01',rec->ea1->base,0xff,0,(label_ref *)0x0);
    g_expanded_records[g_expanded_record_count].ea2 = operand;
  }
  else {
    set_psd_record(&movi_rec,'*','\x02','\0','\0',0,rec->expno,rec->filno,rec->linno);
    movi_rec.ea1 = alloc_ea_operand('\a',0xff,0xff,-0x180001,(label_ref *)0x0);
    movi_rec.ea2 = alloc_ea_operand('\x01',rec->ea2->base,0xff,0,(label_ref *)0x0);
    expand_movi_record(&movi_rec);
    set_psd_record(g_expanded_records + g_expanded_record_count,0x80,'\x02','\0','\0',0,rec->expno,
                   rec->filno,rec->linno);
    operand = alloc_ea_operand('\x01',rec->ea2->base,0xff,0,(label_ref *)0x0);
    g_expanded_records[g_expanded_record_count].ea1 = operand;
    operand = alloc_ea_operand('\x01',rec->ea1->base,0xff,0,(label_ref *)0x0);
    g_expanded_records[g_expanded_record_count].ea2 = operand;
  }
  g_expanded_record_count = g_expanded_record_count + 1;
  set_psd_record(g_expanded_records + g_expanded_record_count,0x8d,'\x02','\0','\0',0,rec->expno,
                 rec->filno,rec->linno);
  operand = alloc_ea_operand('\x01',rec->ea1->base,0xff,0,(label_ref *)0x0);
  g_expanded_records[g_expanded_record_count].ea1 = operand;
  operand = alloc_ea_operand('\x10','h',0xff,0,(label_ref *)0x0);
  g_expanded_records[g_expanded_record_count].ea2 = operand;
  last_ix = g_expanded_record_count;
  g_expanded_record_count = g_expanded_record_count + 1;
  if ((orig_flg & 0x40) != 0) {
    g_expanded_records[last_ix].flg = g_expanded_records[last_ix].flg | 0x40;
  }
  return;
#undef movi_rec
}
