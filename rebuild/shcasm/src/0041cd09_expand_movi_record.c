#include "decls.h"
#include "imports.h"

// entry: 0041cd09
// name : expand_movi_record
// size : 1239
// sig  : void __cdecl expand_movi_record(psd *rec)


int __cdecl expand_movi_record(psd *rec)

{
  unsigned char _frec_1c[28];
#define label_hi (*(undefined1 *)(_frec_1c + 0))
#define label_lo (*(undefined1 *)(_frec_1c + 1))
#define lit_table (*(literal_table * *)(_frec_1c + 4))
#define flag40 (*(char *)(_frec_1c + 8))
#define lit_size (*(uchar *)(_frec_1c + 12))
#define pool_disp (*(int *)(_frec_1c + 16))
#define pool_ref (*(label_ref * *)(_frec_1c + 20))
  short spool_byte;
  int iVar1;
  ea *operand;
  symbol *pool_sym;
  layout_record *pool_start;
  
  flag40 = (rec->flg & 0x40) != 0;
  if ((((rec->ea1->labels == (label_ref *)0x0) && (-0x81 < rec->ea1->disp)) &&
      (rec->ea1->disp < 0x80)) ||
     (iVar1 = get_marked_symbol_attr_low_bits(rec->ea1->labels), iVar1 == 1)) {
    set_psd_record(g_expanded_records + g_expanded_record_count,'@','\x02','\0','\0',0,rec->expno,
                   rec->filno,rec->linno);
    g_expanded_records[g_expanded_record_count].ea1 = rec->ea1;
    operand = alloc_ea_operand('\x01',rec->ea2->base,0xff,0,(label_ref *)0x0);
    g_expanded_records[g_expanded_record_count].ea2 = operand;
    g_expanded_record_count = g_expanded_record_count + 1;
    if (((rec->misc & 0x40U) != 0) && ((rec->flg & 3) != 2)) {
      set_psd_record(g_expanded_records + g_expanded_record_count,'|',rec->flg & 3,'\0','\0',0,
                     rec->expno,rec->filno,rec->linno);
      operand = alloc_ea_operand('\x01',rec->ea2->base,0xff,0,(label_ref *)0x0);
      g_expanded_records[g_expanded_record_count].ea1 = operand;
      g_expanded_records[g_expanded_record_count].ea2 = rec->ea2;
      rec->ea2 = (ea *)0x0;
      g_expanded_record_count = g_expanded_record_count + 1;
    }
  }
  else {
    if ((((rec->ea1->labels == (label_ref *)0x0) && (-0x8001 < rec->ea1->disp)) &&
        (rec->ea1->disp < 0x8000)) ||
       ((iVar1 = is_word_symbol_literal(rec->ea1->disp,rec->ea1->labels), iVar1 == 1 ||
        (iVar1 = get_marked_symbol_attr_low_bits(rec->ea1->labels), iVar1 == 2)))) {
      lit_size = '\x01';
      lit_table = &g_word_literal_table;
    }
    else {
      lit_size = '\x02';
      lit_table = &g_long_literal_table;
    }
    set_psd_record(g_expanded_records + g_expanded_record_count,'@',lit_size,'\0','\0',0,rec->expno,
                   rec->filno,rec->linno);
    if ((g_word_literal_table.count == 0) && (g_long_literal_table.count == 0)) {
      spool_byte = read_spool_byte();
      label_hi = (undefined1)spool_byte;
      spool_byte = read_spool_byte();
      label_lo = (undefined1)spool_byte;
      store_u16_big_endian((ushort *)&label_hi,(ushort *)&g_literal_pool_label);
    }
    iVar1 = find_pool_literal(lit_table,rec->ea1->disp,rec->ea1->labels);
    if (iVar1 == 0) {
      add_pool_literal(lit_table,rec->ea1->disp,rec->ea1->labels);
    }
    iVar1 = find_literal_pool_index(lit_table,rec->ea1->disp,rec->ea1->labels);
    if (lit_size == '\x02') {
      pool_sym = find_symbol_by_id(g_literal_pool_label);
      pool_start = pool_sym->layout_records;
      pool_sym = find_symbol_by_id(g_literal_pool_label);
      pool_disp = (int)pool_start + ((iVar1 * 4 + -4) - pool_sym->value);
    }
    else {
      pool_disp = iVar1 * 2 + -2;
    }
    pool_ref = pool_alloc(8);
    pool_ref->labno1 = g_literal_pool_label;
    operand = alloc_ea_operand('\n','k',0xff,pool_disp,pool_ref);
    g_expanded_records[g_expanded_record_count].ea1 = operand;
    operand = alloc_ea_operand('\x01',rec->ea2->base,0xff,0,(label_ref *)0x0);
    g_expanded_records[g_expanded_record_count].ea2 = operand;
    g_expanded_record_count = g_expanded_record_count + 1;
    if (((rec->misc & 0x40U) != 0) && ((rec->flg & 3) != 2)) {
      set_psd_record(g_expanded_records + g_expanded_record_count,'|',rec->flg & 3,'\0','\0',0,
                     rec->expno,rec->filno,rec->linno);
      operand = alloc_ea_operand('\x01',rec->ea2->base,0xff,0,(label_ref *)0x0);
      g_expanded_records[g_expanded_record_count].ea1 = operand;
      operand = alloc_ea_operand('\x01',rec->ea2->base,0xff,0,(label_ref *)0x0);
      g_expanded_records[g_expanded_record_count].ea2 = operand;
      g_expanded_record_count = g_expanded_record_count + 1;
    }
  }
  if (flag40 == '\x01') {
    g_expanded_records[g_expanded_record_count + -1].flg =
         g_expanded_records[g_expanded_record_count + -1].flg | 0x40;
  }
  return;
#undef label_hi
#undef label_lo
#undef lit_table
#undef flag40
#undef lit_size
#undef pool_disp
#undef pool_ref
}
