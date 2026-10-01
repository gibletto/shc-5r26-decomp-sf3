#include "decls.h"
#include "imports.h"

// entry: 0041ca2c
// name : expand_mva_pc_record
// size : 723
// sig  : void __cdecl expand_mva_pc_record(psd *rec)


int __cdecl expand_mva_pc_record(psd *rec)

{
  unsigned char _frec_18[24];
#define label_hi (*(undefined1 *)(_frec_18 + 0))
#define label_lo (*(undefined1 *)(_frec_18 + 1))
#define lit_table (*(literal_table * *)(_frec_18 + 4))
#define lit_size (*(uchar *)(_frec_18 + 8))
#define pool_disp (*(int *)(_frec_18 + 12))
#define pool_ref (*(label_ref * *)(_frec_18 + 16))
  short spool_byte;
  int lit_index;
  symbol *pool_sym;
  ea *operand;
  layout_record *pool_start;
  
  spool_byte = read_spool_byte();
  if (spool_byte == 0) {
    set_psd_record(g_expanded_records + g_expanded_record_count,'D','\x02','\0','\0',0,rec->expno,
                   rec->filno,rec->linno);
    operand = alloc_ea_operand('\n','k',0xff,rec->ea1->disp,rec->ea1->labels);
    g_expanded_records[g_expanded_record_count].ea1 = operand;
    g_expanded_records[g_expanded_record_count].ea2 = rec->ea2;
    rec->ea2 = (ea *)0x0;
    g_expanded_record_count = g_expanded_record_count + 1;
  }
  else if ((spool_byte != 1) && (spool_byte == 2)) {
    if ((rec->ea1->labels == (label_ref *)0x0) &&
       ((-0x8001 < rec->ea1->disp && (rec->ea1->disp < 0x8000)))) {
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
    lit_index = find_pool_literal(lit_table,rec->ea1->disp,rec->ea1->labels);
    if (lit_index == 0) {
      add_pool_literal(lit_table,rec->ea1->disp,rec->ea1->labels);
    }
    lit_index = find_literal_pool_index(lit_table,rec->ea1->disp,rec->ea1->labels);
    if (lit_size == '\x02') {
      pool_sym = find_symbol_by_id(g_literal_pool_label);
      pool_start = pool_sym->layout_records;
      pool_sym = find_symbol_by_id(g_literal_pool_label);
      pool_disp = (int)pool_start + ((lit_index * 4 + -4) - pool_sym->value);
    }
    else {
      pool_disp = lit_index * 2 + -2;
    }
    pool_ref = pool_alloc(8);
    pool_ref->labno1 = g_literal_pool_label;
    operand = alloc_ea_operand('\n','k',0xff,pool_disp,pool_ref);
    g_expanded_records[g_expanded_record_count].ea1 = operand;
    operand = alloc_ea_operand('\x01',rec->ea2->base,0xff,0,(label_ref *)0x0);
    g_expanded_records[g_expanded_record_count].ea2 = operand;
    g_expanded_record_count = g_expanded_record_count + 1;
  }
  return;
#undef label_hi
#undef label_lo
#undef lit_table
#undef lit_size
#undef pool_disp
#undef pool_ref
}
