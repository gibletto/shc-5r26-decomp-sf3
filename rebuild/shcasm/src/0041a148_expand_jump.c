#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_lit_input
#define g_lit_input (*(FILE * *)(g_sd + 0x10c84))


// entry: 0041a148
// name : expand_jump
// size : 1326
// sig  : void __cdecl expand_jump(psd *rec)


int __cdecl expand_jump(psd *rec)

{
  unsigned char _frec_24[36];
#define pool_index (*(int *)(_frec_24 + 0))
#define label_hi (*(undefined1 *)(_frec_24 + 4))
#define label_lo (*(undefined1 *)(_frec_24 + 5))
#define jump_kind (*(char *)(_frec_24 + 8))
#define pc_label (*(ushort (*)[2])(_frec_24 + 12))
#define pool_disp (*(int *)(_frec_24 + 16))
#define lit_table (*(literal_table * *)(_frec_24 + 20))
#define lab_ref (*(label_ref * *)(_frec_24 + 24))
#define lit_byte (*(char (*)[4])(_frec_24 + 28))
  short spool_byte;
  int iVar1;
  symbol *pool_sym;
  ea *operand;
  uint nread;
  layout_record *pool_start;
  
  spool_byte = read_spool_byte();
  jump_kind = (char)spool_byte;
  if (jump_kind == '\0') {
    set_psd_record(g_expanded_records + g_expanded_record_count,0x92,'\x02','\0','\0',0,rec->expno,
                   rec->filno,rec->linno);
    g_expanded_records[g_expanded_record_count].ea1 = rec->ea1;
    rec->ea1 = (ea *)0x0;
    g_expanded_records[g_expanded_record_count].ea2 = (ea *)0x0;
    goto LAB_0041a5fa;
  }
  if (jump_kind == '\x01') {
    iVar1 = is_word_symbol_literal(rec->ea1->disp,rec->ea1->labels);
    if (iVar1 == 0) goto LAB_0041a212;
    set_psd_record(g_expanded_records + g_expanded_record_count,'@','\x01','\0','\0',0,rec->expno,
                   rec->filno,rec->linno);
  }
  else {
LAB_0041a212:
    set_psd_record(g_expanded_records + g_expanded_record_count,'@','\x02','\0','\0',0,rec->expno,
                   rec->filno,rec->linno);
  }
  if (jump_kind == '\x02') {
    lab_ref = pool_alloc(8);
    spool_byte = read_spool_byte();
    label_hi = (undefined1)spool_byte;
    spool_byte = read_spool_byte();
    label_lo = (undefined1)spool_byte;
    store_u16_big_endian((ushort *)&label_hi,pc_label);
  }
  if ((g_word_literal_table.count == 0) && (g_long_literal_table.count == 0)) {
    spool_byte = read_spool_byte();
    label_hi = (undefined1)spool_byte;
    spool_byte = read_spool_byte();
    label_lo = (undefined1)spool_byte;
    store_u16_big_endian((ushort *)&label_hi,(ushort *)&g_literal_pool_label);
  }
  if (jump_kind == '\x01') {
    iVar1 = is_word_symbol_literal(rec->ea1->disp,rec->ea1->labels);
    if (iVar1 == 0) {
      lit_table = &g_long_literal_table;
    }
    else {
      lit_table = &g_word_literal_table;
    }
    iVar1 = find_pool_literal(lit_table,rec->ea1->disp,rec->ea1->labels);
    if (iVar1 == 0) {
      add_pool_literal(lit_table,rec->ea1->disp,rec->ea1->labels);
    }
    pool_index = find_literal_pool_index(lit_table,rec->ea1->disp,rec->ea1->labels);
  }
  else {
    lab_ref->labno1 = rec->ea1->labels->labno1;
    lab_ref->labno2 = -pc_label[0];
    add_pool_literal(&g_long_literal_table,0xfffffffc,lab_ref);
    pool_index = find_literal_pool_index(&g_long_literal_table,-4,lab_ref);
    pool_free(lab_ref,8);
  }
  if (jump_kind == '\x01') {
    iVar1 = is_word_symbol_literal(rec->ea1->disp,rec->ea1->labels);
    if (iVar1 == 0) goto LAB_0041a43f;
    pool_disp = pool_index * 2 + -2;
  }
  else {
LAB_0041a43f:
    pool_sym = find_symbol_by_id(g_literal_pool_label);
    pool_start = pool_sym->layout_records;
    pool_sym = find_symbol_by_id(g_literal_pool_label);
    pool_disp = (int)pool_start + ((pool_index * 4 + -4) - pool_sym->value);
  }
  lab_ref = pool_alloc(8);
  lab_ref->labno1 = g_literal_pool_label;
  operand = alloc_ea_operand('\n','k',0xff,pool_disp,lab_ref);
  g_expanded_records[g_expanded_record_count].ea1 = operand;
  operand = alloc_ea_operand('\x01',rec->tmp,0xff,0,(label_ref *)0x0);
  g_expanded_records[g_expanded_record_count].ea2 = operand;
  g_expanded_record_count = g_expanded_record_count + 1;
  if (jump_kind == '\x02') {
    g_expanded_records[g_expanded_record_count].op = OP_LABEL;
    g_expanded_records[g_expanded_record_count].expno = rec->expno;
    g_expanded_records[g_expanded_record_count].filno = rec->filno;
    g_expanded_records[g_expanded_record_count].linno = rec->linno;
    *(ushort *)&g_expanded_records[g_expanded_record_count].ea1 = pc_label[0];
    g_expanded_record_count = g_expanded_record_count + 1;
  }
  set_psd_record(g_expanded_records + g_expanded_record_count,
                 (-(jump_kind == '\x01') & 0xfaU) + 0x9a,'\x02','\0','\0',0,rec->expno,rec->filno,
                 rec->linno);
  operand = alloc_ea_operand('\x02',rec->tmp,0xff,0,(label_ref *)0x0);
  g_expanded_records[g_expanded_record_count].ea1 = operand;
  g_expanded_records[g_expanded_record_count].ea2 = (ea *)0x0;
LAB_0041a5fa:
  g_expanded_record_count = g_expanded_record_count + 1;
  if ((rec->flg & 0x10) == 0) {
    nread = read_file_bytes(g_lit_input,lit_byte,1);
    if (nread == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    if (lit_byte[0] == '\x01') {
      g_expanded_records[g_expanded_record_count + -1].flg =
           g_expanded_records[g_expanded_record_count + -1].flg | 0x10;
    }
  }
  return;
#undef pool_index
#undef label_hi
#undef label_lo
#undef jump_kind
#undef pc_label
#undef pool_disp
#undef lit_table
#undef lab_ref
#undef lit_byte
}
