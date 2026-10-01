#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))
#undef g_stack_adjust_list
#define g_stack_adjust_list (*(stack_adjust_node * *)(g_sd + 0xcf28))


// entry: 00419b8d
// name : expand_call
// size : 1467
// sig  : void __cdecl expand_call(psd *rec)


int __cdecl expand_call(psd *rec)

{
  unsigned char _frec_28[40];
#define pool_index (*(int *)(_frec_28 + 0))
#define label_hi (*(undefined1 *)(_frec_28 + 4))
#define label_lo (*(undefined1 *)(_frec_28 + 5))
#define call_kind (*(char *)(_frec_28 + 8))
#define pc_label (*(ushort (*)[2])(_frec_28 + 12))
#define pool_disp (*(int *)(_frec_28 + 16))
#define lit_table (*(literal_table * *)(_frec_28 + 20))
#define tail_node (*(stack_adjust_node * *)(_frec_28 + 24))
#define lab_ref (*(label_ref * *)(_frec_28 + 28))
#define adjust_node (*(stack_adjust_node * *)(_frec_28 + 32))
  short spool_byte;
  int iVar1;
  symbol *pool_sym;
  ea *operand;
  stack_adjust_node *adjust_list;
  layout_record *pool_start;
  
  spool_byte = read_spool_byte();
  call_kind = (char)spool_byte;
  if (call_kind == '\0') {
    set_psd_record(g_expanded_records + g_expanded_record_count,0x93,'\x02','\0','\0',0,rec->expno,
                   rec->filno,rec->linno);
    g_expanded_records[g_expanded_record_count].ea1 = rec->ea1;
    rec->ea1 = (ea *)0x0;
    g_expanded_records[g_expanded_record_count].ea2 = (ea *)0x0;
  }
  else {
    if ((call_kind == '\x01') &&
       (iVar1 = is_word_symbol_literal(rec->ea1->disp,rec->ea1->labels), iVar1 != 0)) {
      set_psd_record(g_expanded_records + g_expanded_record_count,'@','\x01','\0','\0',0,rec->expno,
                     rec->filno,rec->linno);
    }
    else {
      set_psd_record(g_expanded_records + g_expanded_record_count,'@','\x02','\0','\0',0,rec->expno,
                     rec->filno,rec->linno);
    }
    if (call_kind == '\x02') {
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
    if (call_kind == '\x01') {
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
    if ((call_kind == '\x01') &&
       (iVar1 = is_word_symbol_literal(rec->ea1->disp,rec->ea1->labels), iVar1 != 0)) {
      pool_disp = pool_index * 2 + -2;
    }
    else {
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
    if (call_kind == '\x02') {
      g_expanded_records[g_expanded_record_count].op = OP_LABEL;
      g_expanded_records[g_expanded_record_count].expno = rec->expno;
      g_expanded_records[g_expanded_record_count].filno = rec->filno;
      g_expanded_records[g_expanded_record_count].linno = rec->linno;
      *(ushort *)&g_expanded_records[g_expanded_record_count].ea1 = pc_label[0];
      g_expanded_record_count = g_expanded_record_count + 1;
    }
    if (((g_current_request->debug == 0) || (0xb6 < rec->ea1->labels->labno1)) ||
       (*(int *)(&g_runtime_routine_stack_adjust + rec->ea1->labels->labno1 * 4) == 0)) {
      set_psd_record(g_expanded_records + g_expanded_record_count,
                     (-(call_kind == '\x01') & 0xfcU) + 0x99,'\x02','\0','\0',0,rec->expno,
                     rec->filno,rec->linno);
    }
    else {
      adjust_node = pool_alloc(8);
      adjust_node->amount = *(int *)(&g_runtime_routine_stack_adjust + rec->ea1->labels->labno1 * 4)
      ;
      adjust_list = adjust_node;
      if (g_stack_adjust_list != (stack_adjust_node *)0x0) {
        for (tail_node = g_stack_adjust_list; tail_node->next != (stack_adjust_node *)0x0;
            tail_node = tail_node->next) {
        }
        tail_node->next = adjust_node;
        adjust_list = g_stack_adjust_list;
      }
      g_stack_adjust_list = adjust_list;
      set_psd_record(g_expanded_records + g_expanded_record_count,
                     (-(call_kind == '\x01') & 0xfcU) + 0x99,'\x06','\0','\0',0,rec->expno,
                     rec->filno,rec->linno);
    }
    operand = alloc_ea_operand('\x02',rec->tmp,0xff,0,(label_ref *)0x0);
    g_expanded_records[g_expanded_record_count].ea1 = operand;
    g_expanded_records[g_expanded_record_count].ea2 = (ea *)0x0;
  }
  g_expanded_record_count = g_expanded_record_count + 1;
  return;
#undef pool_index
#undef label_hi
#undef label_lo
#undef call_kind
#undef pc_label
#undef pool_disp
#undef lit_table
#undef tail_node
#undef lab_ref
#undef adjust_node
}
