#include "decls.h"
#include "imports.h"

// entry: 0041deea
// name : expand_extst_record
// size : 625
// sig  : void __cdecl expand_extst_record(psd *rec)


int __cdecl expand_extst_record(psd *rec)

{
  ea *operand;
  int reg_no;
  int last_ix;
  byte orig_flg;
  
  orig_flg = rec->flg;
  set_psd_record(g_expanded_records + g_expanded_record_count,0xee,'\x02','\0','\0',0,rec->expno,
                 rec->filno,rec->linno);
  g_expanded_records[g_expanded_record_count].ea1 = (ea *)0x0;
  g_expanded_records[g_expanded_record_count].ea2 = (ea *)0x0;
  g_expanded_record_count = g_expanded_record_count + 1;
  set_psd_record(g_expanded_records + g_expanded_record_count,'`','\x02','\0','\0',0,rec->expno,
                 rec->filno,rec->linno);
  operand = alloc_ea_operand('\a',0xff,0xff,0x40,(label_ref *)0x0);
  g_expanded_records[g_expanded_record_count].ea1 = operand;
  operand = alloc_ea_operand('\x01',rec->ea2->base,0xff,0,(label_ref *)0x0);
  g_expanded_records[g_expanded_record_count].ea2 = operand;
  for (reg_no = 0xf; g_expanded_record_count = g_expanded_record_count + 1, -1 < reg_no;
      reg_no = reg_no + -1) {
    set_psd_record(g_expanded_records + g_expanded_record_count,0xb0,'\x02','\0','\0',0,rec->expno,
                   rec->filno,rec->linno);
    operand = alloc_ea_operand('\x01',(char)reg_no + '\x10',0xff,0,(label_ref *)0x0);
    g_expanded_records[g_expanded_record_count].ea1 = operand;
    operand = alloc_ea_operand('\x03',rec->ea2->base,0xff,0,(label_ref *)0x0);
    g_expanded_records[g_expanded_record_count].ea2 = operand;
  }
  set_psd_record(g_expanded_records + g_expanded_record_count,0xee,'\x02','\0','\0',0,rec->expno,
                 rec->filno,rec->linno);
  g_expanded_records[g_expanded_record_count].ea1 = (ea *)0x0;
  g_expanded_records[g_expanded_record_count].ea2 = (ea *)0x0;
  last_ix = g_expanded_record_count;
  g_expanded_record_count = g_expanded_record_count + 1;
  if ((orig_flg & 0x40) != 0) {
    g_expanded_records[last_ix].flg = g_expanded_records[last_ix].flg | 0x40;
  }
  return;
}
