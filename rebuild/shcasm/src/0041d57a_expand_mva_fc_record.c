#include "decls.h"
#include "imports.h"

// entry: 0041d57a
// name : expand_mva_fc_record
// size : 996
// sig  : void __cdecl expand_mva_fc_record(psd *rec)


int __cdecl expand_mva_fc_record(psd *rec)

{
  unsigned char _frec_18[24];
#define label_hi (*(undefined1 *)(_frec_18 + 0))
#define label_lo (*(undefined1 *)(_frec_18 + 1))
#define pc_label (*(ushort (*)[2])(_frec_18 + 4))
#define label_slot (*(int *)(_frec_18 + 8))
#define pool_disp (*(int *)(_frec_18 + 12))
#define lab_ref (*(label_ref * *)(_frec_18 + 16))
  short spool_byte;
  int lit_index;
  symbol *pool_sym;
  ea *operand;
  layout_record *pool_start;
  
  set_psd_record(g_expanded_records + g_expanded_record_count,'@','\x02','\0','\0',0,rec->expno,
                 rec->filno,rec->linno);
  lab_ref = pool_alloc(8);
  spool_byte = read_spool_byte();
  label_hi = (undefined1)spool_byte;
  spool_byte = read_spool_byte();
  label_lo = (undefined1)spool_byte;
  store_u16_big_endian((ushort *)&label_hi,pc_label);
  spool_byte = read_spool_byte();
  label_slot = (int)spool_byte;
  if ((g_word_literal_table.count == 0) && (g_long_literal_table.count == 0)) {
    spool_byte = read_spool_byte();
    label_hi = (undefined1)spool_byte;
    spool_byte = read_spool_byte();
    label_lo = (undefined1)spool_byte;
    store_u16_big_endian((ushort *)&label_hi,(ushort *)&g_literal_pool_label);
  }
  lab_ref->labno1 = rec->ea1->labels->labno1;
  lab_ref->labno2 = -pc_label[0];
  add_pool_literal(&g_long_literal_table,0,lab_ref);
  lit_index = find_literal_pool_index(&g_long_literal_table,0,lab_ref);
  pool_free(lab_ref,8);
  pool_sym = find_symbol_by_id(g_literal_pool_label);
  pool_start = pool_sym->layout_records;
  pool_sym = find_symbol_by_id(g_literal_pool_label);
  pool_disp = (int)pool_start + ((lit_index * 4 + -4) - pool_sym->value);
  lab_ref = pool_alloc(8);
  lab_ref->labno1 = g_literal_pool_label;
  operand = alloc_ea_operand('\n','k',0xff,pool_disp,lab_ref);
  g_expanded_records[g_expanded_record_count].ea1 = operand;
  operand = alloc_ea_operand('\x01',rec->ea2->base,0xff,0,(label_ref *)0x0);
  g_expanded_records[g_expanded_record_count].ea2 = operand;
  g_expanded_record_count = g_expanded_record_count + 1;
  set_psd_record(g_expanded_records + g_expanded_record_count,'D','\x02','\0','\0',0,rec->expno,
                 rec->filno,rec->linno);
  lab_ref = pool_alloc(8);
  lab_ref->labno1 = pc_label[0];
  operand = alloc_ea_operand('\n','k',0xff,0,lab_ref);
  g_expanded_records[g_expanded_record_count].ea1 = operand;
  operand = alloc_ea_operand('\x01',rec->tmp,0xff,0,(label_ref *)0x0);
  g_expanded_records[g_expanded_record_count].ea2 = operand;
  g_expanded_record_count = g_expanded_record_count + 1;
  if (label_slot == 0) {
    g_expanded_records[g_expanded_record_count].op = OP_LABEL;
    g_expanded_records[g_expanded_record_count].expno = rec->expno;
    g_expanded_records[g_expanded_record_count].filno = rec->filno;
    g_expanded_records[g_expanded_record_count].linno = rec->linno;
    *(ushort *)&g_expanded_records[g_expanded_record_count].ea1 = pc_label[0];
    g_expanded_record_count = g_expanded_record_count + 1;
  }
  set_psd_record(g_expanded_records + g_expanded_record_count,'`','\x02','\0','\0',0,rec->expno,
                 rec->filno,rec->linno);
  operand = alloc_ea_operand('\x01',rec->tmp,0xff,0,(label_ref *)0x0);
  g_expanded_records[g_expanded_record_count].ea1 = operand;
  operand = alloc_ea_operand('\x01',rec->ea2->base,0xff,0,(label_ref *)0x0);
  g_expanded_records[g_expanded_record_count].ea2 = operand;
  g_expanded_record_count = g_expanded_record_count + 1;
  if (label_slot == 1) {
    g_expanded_records[g_expanded_record_count].op = OP_LABEL;
    g_expanded_records[g_expanded_record_count].expno = rec->expno;
    g_expanded_records[g_expanded_record_count].filno = rec->filno;
    g_expanded_records[g_expanded_record_count].linno = rec->linno;
    *(ushort *)&g_expanded_records[g_expanded_record_count].ea1 = pc_label[0];
    g_expanded_record_count = g_expanded_record_count + 1;
  }
  return;
#undef label_hi
#undef label_lo
#undef pc_label
#undef label_slot
#undef pool_disp
#undef lab_ref
}
