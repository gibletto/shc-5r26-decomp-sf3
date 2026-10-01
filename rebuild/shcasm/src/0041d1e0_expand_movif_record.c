#include "decls.h"
#include "imports.h"

// entry: 0041d1e0
// name : expand_movif_record
// size : 922
// sig  : void __cdecl expand_movif_record(psd *rec)


int __cdecl expand_movif_record(psd *rec)

{
  unsigned char _frec_14[20];
#define label_hi (*(undefined1 *)(_frec_14 + 0))
#define label_lo (*(undefined1 *)(_frec_14 + 1))
#define flag40 (*(char *)(_frec_14 + 4))
#define pool_disp (*(int *)(_frec_14 + 8))
#define pool_ref (*(label_ref * *)(_frec_14 + 12))
  short spool_byte;
  int iVar1;
  symbol *pool_sym;
  ea *operand;
  layout_record *pool_start;
  
  flag40 = (rec->flg & 0x40) != 0;
  set_psd_record(g_expanded_records + g_expanded_record_count,(-(rec->tmp == '\0') & 4U) + 0x40,
                 '\x02','\0','\0',0,rec->expno,rec->filno,rec->linno);
  if ((g_word_literal_table.count == 0) && (g_long_literal_table.count == 0)) {
    spool_byte = read_spool_byte();
    label_hi = (undefined1)spool_byte;
    spool_byte = read_spool_byte();
    label_lo = (undefined1)spool_byte;
    store_u16_big_endian((ushort *)&label_hi,(ushort *)&g_literal_pool_label);
  }
  iVar1 = find_pool_literal(&g_long_literal_table,rec->ea1->disp,(label_ref *)0x0);
  if (iVar1 == 0) {
    add_pool_literal(&g_long_literal_table,rec->ea1->disp,(label_ref *)0x0);
  }
  iVar1 = find_literal_pool_index(&g_long_literal_table,rec->ea1->disp,(label_ref *)0x0);
  pool_sym = find_symbol_by_id(g_literal_pool_label);
  pool_start = pool_sym->layout_records;
  pool_sym = find_symbol_by_id(g_literal_pool_label);
  pool_disp = (int)pool_start + ((iVar1 * 4 + -4) - pool_sym->value);
  pool_ref = pool_alloc(8);
  pool_ref->labno1 = g_literal_pool_label;
  operand = alloc_ea_operand('\n','k',0xff,pool_disp,pool_ref);
  g_expanded_records[g_expanded_record_count].ea1 = operand;
  operand = alloc_ea_operand('\x01',rec->tmp,0xff,0,(label_ref *)0x0);
  g_expanded_records[g_expanded_record_count].ea2 = operand;
  g_expanded_record_count = g_expanded_record_count + 1;
  if (rec->tmp == '\0') {
    set_psd_record(g_expanded_records + g_expanded_record_count,0xb0,'\x02','\0','\0',0,rec->expno,
                   rec->filno,rec->linno);
    operand = alloc_ea_operand('\x02','\0',0xff,0,(label_ref *)0x0);
    g_expanded_records[g_expanded_record_count].ea1 = operand;
    operand = alloc_ea_operand('\x01',rec->ea2->base,0xff,0,(label_ref *)0x0);
    g_expanded_records[g_expanded_record_count].ea2 = operand;
    iVar1 = g_expanded_record_count;
  }
  else {
    set_psd_record(g_expanded_records + g_expanded_record_count,0x8d,'\x02','\0','\0',0,rec->expno,
                   rec->filno,rec->linno);
    operand = alloc_ea_operand('\x01',rec->tmp,0xff,0,(label_ref *)0x0);
    g_expanded_records[g_expanded_record_count].ea1 = operand;
    operand = alloc_ea_operand('\x0f','g',0xff,0,(label_ref *)0x0);
    g_expanded_records[g_expanded_record_count].ea2 = operand;
    g_expanded_record_count = g_expanded_record_count + 1;
    set_psd_record(g_expanded_records + g_expanded_record_count,0xde,'\x02','\0','\0',0,rec->expno,
                   rec->filno,rec->linno);
    operand = alloc_ea_operand('\x0f','g',0xff,0,(label_ref *)0x0);
    g_expanded_records[g_expanded_record_count].ea1 = operand;
    operand = alloc_ea_operand('\x01',rec->ea2->base,0xff,0,(label_ref *)0x0);
    g_expanded_records[g_expanded_record_count].ea2 = operand;
    iVar1 = g_expanded_record_count;
  }
  g_expanded_record_count = iVar1 + 1;
  if (flag40 == '\x01') {
    g_expanded_records[iVar1].flg = g_expanded_records[iVar1].flg | 0x40;
  }
  return;
#undef label_hi
#undef label_lo
#undef flag40
#undef pool_disp
#undef pool_ref
}
