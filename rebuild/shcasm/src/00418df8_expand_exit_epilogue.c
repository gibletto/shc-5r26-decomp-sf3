#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_aux_record_table
#define g_aux_record_table (*(aux_record * *)(g_sd + 0x10c74))
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))
#undef g_lit_input
#define g_lit_input (*(FILE * *)(g_sd + 0x10c84))
#undef g_stack_adjust_list
#define g_stack_adjust_list (*(stack_adjust_node * *)(g_sd + 0xcf28))


// entry: 00418df8
// name : expand_exit_epilogue
// size : 3100
// sig  : void __cdecl expand_exit_epilogue(psd *rec)


int __cdecl expand_exit_epilogue(psd *rec)

{
  unsigned char _frec_38[56];
#define reg_end (*(int *)(_frec_38 + 0))
#define reg_no (*(int *)(_frec_38 + 4))
#define reg_bit (*(ushort *)(_frec_38 + 12))
#define movi_rec (*(psd *)(_frec_38 + 16))
#define tail_node (*(stack_adjust_node * *)(_frec_38 + 40))
#define adjust_node (*(stack_adjust_node * *)(_frec_38 + 44))
#define lit_byte (*(char (*)[4])(_frec_38 + 48))
  symbol *func_sym;
  int disp;
  ea *operand;
  uint nread;
  stack_adjust_node *adjust_list;
  short aux_ix;
  
  func_sym = find_symbol_by_id(g_function_label);
  aux_ix = func_sym->aux_index;
  disp = g_aux_record_table[aux_ix].sp_adjust + g_aux_record_table[aux_ix].frame_size;
  adjust_list = g_stack_adjust_list;
  if (disp != 0) {
    if (disp < 0x80) {
      set_psd_record(g_expanded_records + g_expanded_record_count,'`','\x02','\0','\0',0,rec->expno,
                     rec->filno,rec->linno);
      operand = alloc_ea_operand('\a',0xff,0xff,disp,(label_ref *)0x0);
      g_expanded_records[g_expanded_record_count].ea1 = operand;
      operand = alloc_ea_operand('\x01','\x0f',0xff,0,(label_ref *)0x0);
      g_expanded_records[g_expanded_record_count].ea2 = operand;
      g_expanded_record_count = g_expanded_record_count + 1;
      adjust_list = g_stack_adjust_list;
    }
    else {
      set_psd_record(&movi_rec,'*','\x02','\0','\0',0,rec->expno,rec->filno,rec->linno);
      movi_rec.ea1 = alloc_ea_operand('\a',0xff,0xff,disp,(label_ref *)0x0);
      movi_rec.ea2 = alloc_ea_operand('\x01','\x01',0xff,0,(label_ref *)0x0);
      expand_movi_record(&movi_rec);
      set_psd_record(g_expanded_records + g_expanded_record_count,'`','\x02','\0','\0',0,rec->expno,
                     rec->filno,rec->linno);
      operand = alloc_ea_operand('\x01','\x01',0xff,0,(label_ref *)0x0);
      g_expanded_records[g_expanded_record_count].ea1 = operand;
      operand = alloc_ea_operand('\x01','\x0f',0xff,0,(label_ref *)0x0);
      g_expanded_records[g_expanded_record_count].ea2 = operand;
      g_expanded_record_count = g_expanded_record_count + 1;
      adjust_list = g_stack_adjust_list;
      if (g_current_request->debug != 0) {
        adjust_node = pool_alloc(8);
        adjust_node->amount = disp;
        adjust_list = adjust_node;
        if (g_stack_adjust_list != (stack_adjust_node *)0x0) {
          for (tail_node = g_stack_adjust_list; tail_node->next != (stack_adjust_node *)0x0;
              tail_node = tail_node->next) {
          }
          tail_node->next = adjust_node;
          adjust_list = g_stack_adjust_list;
        }
      }
    }
  }
  g_stack_adjust_list = adjust_list;
  if ((g_aux_record_table[aux_ix].saved_sys & 2) != 0) {
    set_psd_record(g_expanded_records + g_expanded_record_count,0x8d,'\x02','\0','\0',0,rec->expno,
                   rec->filno,rec->linno);
    operand = alloc_ea_operand('\x04','\x0f',0xff,0,(label_ref *)0x0);
    g_expanded_records[g_expanded_record_count].ea1 = operand;
    operand = alloc_ea_operand('\x10','h',0xff,0,(label_ref *)0x0);
    g_expanded_records[g_expanded_record_count].ea2 = operand;
    g_expanded_record_count = g_expanded_record_count + 1;
  }
  if ((g_aux_record_table[aux_ix].saved_sys & 1) != 0) {
    set_psd_record(g_expanded_records + g_expanded_record_count,0x8d,'\x02','\0','\0',0,rec->expno,
                   rec->filno,rec->linno);
    operand = alloc_ea_operand('\x04','\x0f',0xff,0,(label_ref *)0x0);
    g_expanded_records[g_expanded_record_count].ea1 = operand;
    operand = alloc_ea_operand('\x0f','g',0xff,0,(label_ref *)0x0);
    g_expanded_records[g_expanded_record_count].ea2 = operand;
    g_expanded_record_count = g_expanded_record_count + 1;
  }
  if ((g_aux_record_table[aux_ix].saved_mac & 1) != 0) {
    set_psd_record(g_expanded_records + g_expanded_record_count,0x8d,'\x02','\0','\0',0,rec->expno,
                   rec->filno,rec->linno);
    operand = alloc_ea_operand('\x04','\x0f',0xff,0,(label_ref *)0x0);
    g_expanded_records[g_expanded_record_count].ea1 = operand;
    operand = alloc_ea_operand('\x06','e',0xff,0,(label_ref *)0x0);
    g_expanded_records[g_expanded_record_count].ea2 = operand;
    g_expanded_record_count = g_expanded_record_count + 1;
  }
  if ((g_aux_record_table[aux_ix].saved_mac & 2) != 0) {
    set_psd_record(g_expanded_records + g_expanded_record_count,0x8d,'\x02','\0','\0',0,rec->expno,
                   rec->filno,rec->linno);
    operand = alloc_ea_operand('\x04','\x0f',0xff,0,(label_ref *)0x0);
    g_expanded_records[g_expanded_record_count].ea1 = operand;
    operand = alloc_ea_operand('\x06','d',0xff,0,(label_ref *)0x0);
    g_expanded_records[g_expanded_record_count].ea2 = operand;
    g_expanded_record_count = g_expanded_record_count + 1;
  }
  if (((int)(short)g_aux_record_table[aux_ix].flags & 0x8000U) == 0) {
    set_psd_record(g_expanded_records + g_expanded_record_count,0x8d,'\x02','\0','\0',0,rec->expno,
                   rec->filno,rec->linno);
    operand = alloc_ea_operand('\x04','\x0f',0xff,0,(label_ref *)0x0);
    g_expanded_records[g_expanded_record_count].ea1 = operand;
    operand = alloc_ea_operand('\x06','f',0xff,0,(label_ref *)0x0);
    g_expanded_records[g_expanded_record_count].ea2 = operand;
    g_expanded_record_count = g_expanded_record_count + 1;
  }
  reg_bit = 1;
  for (reg_no = 0; reg_no < 0x10; reg_no = reg_no + 1) {
    if ((reg_bit & g_aux_record_table[aux_ix].saved_regs2) != 0) {
      set_psd_record(g_expanded_records + g_expanded_record_count,0xb0,'\x02','\0','\0',0,rec->expno
                     ,rec->filno,rec->linno);
      operand = alloc_ea_operand('\x04','\x0f',0xff,0,(label_ref *)0x0);
      g_expanded_records[g_expanded_record_count].ea1 = operand;
      operand = alloc_ea_operand('\x01',(char)reg_no + '\x10',0xff,0,(label_ref *)0x0);
      g_expanded_records[g_expanded_record_count].ea2 = operand;
      g_expanded_record_count = g_expanded_record_count + 1;
    }
    reg_bit = reg_bit << 1;
  }
  if (((g_aux_record_table[aux_ix].flags & 0x4000) == 0) ||
     ((g_aux_record_table[aux_ix].flags & 0x1800) == 0)) {
    reg_no = 0;
    reg_end = 0x10;
    reg_bit = 1;
  }
  else {
    reg_no = 1;
    reg_end = 0xf;
    reg_bit = 2;
  }
  for (; reg_no < reg_end; reg_no = reg_no + 1) {
    if ((reg_bit & g_aux_record_table[aux_ix].saved_regs) != 0) {
      set_psd_record(g_expanded_records + g_expanded_record_count,'@','\x02','\0','\0',0,rec->expno,
                     rec->filno,rec->linno);
      operand = alloc_ea_operand('\x04','\x0f',0xff,0,(label_ref *)0x0);
      g_expanded_records[g_expanded_record_count].ea1 = operand;
      operand = alloc_ea_operand('\x01',(uchar)reg_no,0xff,0,(label_ref *)0x0);
      g_expanded_records[g_expanded_record_count].ea2 = operand;
      g_expanded_record_count = g_expanded_record_count + 1;
    }
    reg_bit = reg_bit << 1;
  }
  if (((g_aux_record_table[aux_ix].flags & 0x4000) != 0) &&
     ((g_aux_record_table[aux_ix].flags & 0x1800) != 0)) {
    set_psd_record(g_expanded_records + g_expanded_record_count,'@','\x02','\0','\0',0,rec->expno,
                   rec->filno,rec->linno);
    operand = alloc_ea_operand('\x04','\x0f',0xff,0,(label_ref *)0x0);
    g_expanded_records[g_expanded_record_count].ea1 = operand;
    operand = alloc_ea_operand('\x01','\x0f',0xff,0,(label_ref *)0x0);
    g_expanded_records[g_expanded_record_count].ea2 = operand;
    g_expanded_record_count = g_expanded_record_count + 1;
    set_psd_record(g_expanded_records + g_expanded_record_count,'@','\x02','\0','\0',0,rec->expno,
                   rec->filno,rec->linno);
    operand = alloc_ea_operand('\x04','\x0f',0xff,0,(label_ref *)0x0);
    g_expanded_records[g_expanded_record_count].ea1 = operand;
    operand = alloc_ea_operand('\x01','\0',0xff,0,(label_ref *)0x0);
    g_expanded_records[g_expanded_record_count].ea2 = operand;
    g_expanded_record_count = g_expanded_record_count + 1;
  }
  if (((g_aux_record_table[aux_ix].flags & 0x4000) == 0) ||
     ((g_aux_record_table[aux_ix].flags & 0x2000) == 0)) {
    if ((g_aux_record_table[aux_ix].flags & 0x4000) == 0) {
      set_psd_record(g_expanded_records + g_expanded_record_count,0x96,'\x02','\0','\0',0,rec->expno
                     ,rec->filno,rec->linno);
      g_expanded_records[g_expanded_record_count].ea1 = (ea *)0x0;
      g_expanded_records[g_expanded_record_count].ea2 = (ea *)0x0;
      g_expanded_record_count = g_expanded_record_count + 1;
    }
    else {
      set_psd_record(g_expanded_records + g_expanded_record_count,0x8e,'\x02','\0','\0',0,rec->expno
                     ,rec->filno,rec->linno);
      g_expanded_records[g_expanded_record_count].ea1 = (ea *)0x0;
      g_expanded_records[g_expanded_record_count].ea2 = (ea *)0x0;
      g_expanded_record_count = g_expanded_record_count + 1;
    }
  }
  else {
    set_psd_record(g_expanded_records + g_expanded_record_count,0x9e,'\x02','\0','\0',0,rec->expno,
                   rec->filno,rec->linno);
    operand = alloc_ea_operand('\a',0xff,0xff,(uint)g_aux_record_table[aux_ix].trap_number,
                               (label_ref *)0x0);
    g_expanded_records[g_expanded_record_count].ea1 = operand;
    g_expanded_records[g_expanded_record_count].ea2 = (ea *)0x0;
    g_expanded_record_count = g_expanded_record_count + 1;
  }
  if (((g_current_request->optimize != 0) && ((g_aux_record_table[aux_ix].flags & 0x4000) == 0)) &&
     (((g_aux_record_table[aux_ix].saved_regs != 0 || (g_aux_record_table[aux_ix].saved_regs2 != 0))
      || ((((int)(short)g_aux_record_table[aux_ix].flags & 0x8000U) != 0 &&
          (((disp != 0 || ((g_aux_record_table[aux_ix].saved_sys & 3) != 0)) ||
           ((g_aux_record_table[aux_ix].saved_mac & 3) != 0)))))))) {
    g_expanded_records[g_expanded_record_count + -2].flg =
         g_expanded_records[g_expanded_record_count + -2].flg | 0x40;
  }
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
#undef reg_end
#undef reg_no
#undef reg_bit
#undef movi_rec
#undef tail_node
#undef adjust_node
#undef lit_byte
}
