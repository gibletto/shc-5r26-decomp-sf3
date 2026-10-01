#include "decls.h"
#include "imports.h"

// entry: 0041e15b
// name : expand_mov_to_r0_with_nop
// size : 346
// sig  : void __cdecl expand_mov_to_r0_with_nop(psd *rec)


int __cdecl expand_mov_to_r0_with_nop(psd *rec)

{
  ea *operand;
  
  set_psd_record(g_expanded_records + g_expanded_record_count,rec->op,'\x02','\0','\0',0,rec->expno,
                 rec->filno,rec->linno);
  operand = alloc_ea_operand('\x01',rec->ea1->base,0xff,0,(label_ref *)0x0);
  g_expanded_records[g_expanded_record_count].ea1 = operand;
  operand = alloc_ea_operand('\x01',rec->ea2->base,0xff,0,(label_ref *)0x0);
  g_expanded_records[g_expanded_record_count].ea2 = operand;
  g_expanded_records[g_expanded_record_count].flg =
       g_expanded_records[g_expanded_record_count].flg | 0x80;
  g_expanded_record_count = g_expanded_record_count + 1;
  set_psd_record(g_expanded_records + g_expanded_record_count,0x88,'\x02','\0','\0',0,rec->expno,
                 rec->filno,rec->linno);
  g_expanded_records[g_expanded_record_count].ea1 = (ea *)0x0;
  g_expanded_records[g_expanded_record_count].ea2 = (ea *)0x0;
  g_expanded_records[g_expanded_record_count].flg =
       g_expanded_records[g_expanded_record_count].flg | 0x80;
  g_expanded_record_count = g_expanded_record_count + 1;
  return;
}
