#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_aux_record_table
#define g_aux_record_table (*(aux_record * *)(g_sd + 0x10c74))
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))
#undef g_stack_adjust_list
#define g_stack_adjust_list (*(stack_adjust_node * *)(g_sd + 0xcf28))


// entry: 00418033
// name : expand_enter_prologue
// size : 3525
// sig  : void __cdecl expand_enter_prologue(psd *rec)


int __cdecl expand_enter_prologue(psd *rec)

{
  unsigned char _frec_38[56];
#define low_reg (*(int *)(_frec_38 + 0))
#define reg_no (*(int *)(_frec_38 + 4))
#define tmp_rec (*(psd *)(_frec_38 + 16))
#define tail_node (*(stack_adjust_node * *)(_frec_38 + 40))
#define lref (*(label_ref * *)(_frec_38 + 44))
  symbol *func_sym;
  ea *operand;
  int attr_bits;
  stack_adjust_node *psVar1;
  short aux_ix;
  ushort reg_bit;
  
  func_sym = find_symbol_by_id(g_function_label);
  aux_ix = func_sym->aux_index;
  if (((g_aux_record_table[aux_ix].flags & 0x4000) != 0) &&
     ((g_aux_record_table[aux_ix].flags & 0x1800) != 0)) {
    set_psd_record(g_expanded_records + g_expanded_record_count,'@','\x02','\0','\0',0,rec->expno,
                   rec->filno,rec->linno);
    operand = alloc_ea_operand('\x01','\0',0xff,0,(label_ref *)0x0);
    g_expanded_records[g_expanded_record_count].ea1 = operand;
    operand = alloc_ea_operand('\x03','\x0f',0xff,0,(label_ref *)0x0);
    g_expanded_records[g_expanded_record_count].ea2 = operand;
    g_expanded_record_count = g_expanded_record_count + 1;
    if ((((byte)(g_aux_record_table[aux_ix].flags >> 8) & 0x18) == 0x10) &&
       (attr_bits = get_symbol_attribute_bits((short)g_aux_record_table[aux_ix].stack_value),
       attr_bits != 0)) {
      set_psd_record(g_expanded_records + g_expanded_record_count,'@','\x02','\0','\0',0,rec->expno,
                     rec->filno,rec->linno);
      lref = pool_alloc(8);
      lref->labno1 = (short)g_aux_record_table[aux_ix].stack_value;
      lref->labno2 = -0x8000;
      operand = alloc_ea_operand('\v','b',0xff,0,lref);
      g_expanded_records[g_expanded_record_count].ea1 = operand;
      operand = alloc_ea_operand('\x01','\0',0xff,0,(label_ref *)0x0);
      g_expanded_records[g_expanded_record_count].ea2 = operand;
      g_expanded_record_count = g_expanded_record_count + 1;
    }
    else if ((((byte)(g_aux_record_table[aux_ix].flags >> 8) & 0x18) == 0x18) &&
            (attr_bits = get_symbol_attribute_bits((short)g_aux_record_table[aux_ix].stack_value),
            attr_bits == 1)) {
      set_psd_record(g_expanded_records + g_expanded_record_count,0x9c,'\x02','\0','\0',0,rec->expno
                     ,rec->filno,rec->linno);
      operand = alloc_ea_operand('\x05','b',0xff,0,(label_ref *)0x0);
      g_expanded_records[g_expanded_record_count].ea1 = operand;
      operand = alloc_ea_operand('\x01','\0',0xff,0,(label_ref *)0x0);
      g_expanded_records[g_expanded_record_count].ea2 = operand;
      g_expanded_record_count = g_expanded_record_count + 1;
      set_psd_record(g_expanded_records + g_expanded_record_count,'`','\x02','\0','\0',0,rec->expno,
                     rec->filno,rec->linno);
      lref = pool_alloc(8);
      lref->labno1 = (short)g_aux_record_table[aux_ix].stack_value;
      lref->labno2 = -0x8000;
      operand = alloc_ea_operand('\a',0xff,0xff,0,lref);
      g_expanded_records[g_expanded_record_count].ea1 = operand;
      operand = alloc_ea_operand('\x01','\0',0xff,0,(label_ref *)0x0);
      g_expanded_records[g_expanded_record_count].ea2 = operand;
      g_expanded_record_count = g_expanded_record_count + 1;
    }
    else {
      set_psd_record(&tmp_rec,'*','\x02','\0','\0',0,rec->expno,rec->filno,rec->linno);
      if (((byte)(g_aux_record_table[aux_ix].flags >> 8) & 0x18) == 8) {
        tmp_rec.ea1 = alloc_ea_operand('\a',0xff,0xff,g_aux_record_table[aux_ix].stack_value,
                                       (label_ref *)0x0);
      }
      else {
        lref = pool_alloc(8);
        lref->labno1 = (short)g_aux_record_table[aux_ix].stack_value;
        tmp_rec.ea1 = alloc_ea_operand('\a',0xff,0xff,0,lref);
      }
      tmp_rec.ea2 = alloc_ea_operand('\x01','\0',0xff,0,(label_ref *)0x0);
      expand_movi_record(&tmp_rec);
      if (((byte)(g_aux_record_table[aux_ix].flags >> 8) & 0x18) == 0x10) {
        set_psd_record(g_expanded_records + g_expanded_record_count,'@','\x02','\0','\0',0,
                       rec->expno,rec->filno,rec->linno);
        operand = alloc_ea_operand('\x02','\0',0xff,0,(label_ref *)0x0);
        g_expanded_records[g_expanded_record_count].ea1 = operand;
        operand = alloc_ea_operand('\x01','\0',0xff,0,(label_ref *)0x0);
        g_expanded_records[g_expanded_record_count].ea2 = operand;
        g_expanded_record_count = g_expanded_record_count + 1;
      }
    }
    set_psd_record(g_expanded_records + g_expanded_record_count,'@','\x02','\0','\0',0,rec->expno,
                   rec->filno,rec->linno);
    operand = alloc_ea_operand('\x01','\x0f',0xff,0,(label_ref *)0x0);
    g_expanded_records[g_expanded_record_count].ea1 = operand;
    operand = alloc_ea_operand('\x03','\0',0xff,0,(label_ref *)0x0);
    g_expanded_records[g_expanded_record_count].ea2 = operand;
    g_expanded_record_count = g_expanded_record_count + 1;
    set_psd_record(g_expanded_records + g_expanded_record_count,'@','\x02','\0','\0',0,rec->expno,
                   rec->filno,rec->linno);
    operand = alloc_ea_operand('\x01','\0',0xff,0,(label_ref *)0x0);
    g_expanded_records[g_expanded_record_count].ea1 = operand;
    operand = alloc_ea_operand('\x01','\x0f',0xff,0,(label_ref *)0x0);
    g_expanded_records[g_expanded_record_count].ea2 = operand;
    g_expanded_record_count = g_expanded_record_count + 1;
  }
  if (((g_aux_record_table[aux_ix].flags & 0x4000) == 0) ||
     ((g_aux_record_table[aux_ix].flags & 0x1800) == 0)) {
    reg_no = 0xf;
    low_reg = 0;
    reg_bit = 0x8000;
  }
  else {
    reg_no = 0xe;
    low_reg = 1;
    reg_bit = 0x4000;
  }
  for (; low_reg <= reg_no; reg_no = reg_no + -1) {
    if ((reg_bit & g_aux_record_table[aux_ix].saved_regs) != 0) {
      set_psd_record(g_expanded_records + g_expanded_record_count,'@','\x02','\0','\0',0,rec->expno,
                     rec->filno,rec->linno);
      operand = alloc_ea_operand('\x01',(uchar)reg_no,0xff,0,(label_ref *)0x0);
      g_expanded_records[g_expanded_record_count].ea1 = operand;
      operand = alloc_ea_operand('\x03','\x0f',0xff,0,(label_ref *)0x0);
      g_expanded_records[g_expanded_record_count].ea2 = operand;
      g_expanded_record_count = g_expanded_record_count + 1;
    }
    reg_bit = reg_bit >> 1;
  }
  reg_bit = 0x8000;
  for (reg_no = 0xf; -1 < reg_no; reg_no = reg_no + -1) {
    if ((reg_bit & g_aux_record_table[aux_ix].saved_regs2) != 0) {
      set_psd_record(g_expanded_records + g_expanded_record_count,0xb0,'\x02','\0','\0',0,rec->expno
                     ,rec->filno,rec->linno);
      operand = alloc_ea_operand('\x01',(char)reg_no + '\x10',0xff,0,(label_ref *)0x0);
      g_expanded_records[g_expanded_record_count].ea1 = operand;
      operand = alloc_ea_operand('\x03','\x0f',0xff,0,(label_ref *)0x0);
      g_expanded_records[g_expanded_record_count].ea2 = operand;
      g_expanded_record_count = g_expanded_record_count + 1;
    }
    reg_bit = reg_bit >> 1;
  }
  if (((int)(short)g_aux_record_table[aux_ix].flags & 0x8000U) == 0) {
    set_psd_record(g_expanded_records + g_expanded_record_count,0x9d,'\x02','\0','\0',0,rec->expno,
                   rec->filno,rec->linno);
    operand = alloc_ea_operand('\x06','f',0xff,0,(label_ref *)0x0);
    g_expanded_records[g_expanded_record_count].ea1 = operand;
    operand = alloc_ea_operand('\x03','\x0f',0xff,0,(label_ref *)0x0);
    g_expanded_records[g_expanded_record_count].ea2 = operand;
    g_expanded_record_count = g_expanded_record_count + 1;
  }
  if ((g_aux_record_table[aux_ix].saved_mac & 2) != 0) {
    set_psd_record(g_expanded_records + g_expanded_record_count,0x9d,'\x02','\0','\0',0,rec->expno,
                   rec->filno,rec->linno);
    operand = alloc_ea_operand('\x06','d',0xff,0,(label_ref *)0x0);
    g_expanded_records[g_expanded_record_count].ea1 = operand;
    operand = alloc_ea_operand('\x03','\x0f',0xff,0,(label_ref *)0x0);
    g_expanded_records[g_expanded_record_count].ea2 = operand;
    g_expanded_record_count = g_expanded_record_count + 1;
  }
  if ((g_aux_record_table[aux_ix].saved_mac & 1) != 0) {
    set_psd_record(g_expanded_records + g_expanded_record_count,0x9d,'\x02','\0','\0',0,rec->expno,
                   rec->filno,rec->linno);
    operand = alloc_ea_operand('\x06','e',0xff,0,(label_ref *)0x0);
    g_expanded_records[g_expanded_record_count].ea1 = operand;
    operand = alloc_ea_operand('\x03','\x0f',0xff,0,(label_ref *)0x0);
    g_expanded_records[g_expanded_record_count].ea2 = operand;
    g_expanded_record_count = g_expanded_record_count + 1;
  }
  if ((g_aux_record_table[aux_ix].saved_sys & 1) != 0) {
    set_psd_record(g_expanded_records + g_expanded_record_count,0x9d,'\x02','\0','\0',0,rec->expno,
                   rec->filno,rec->linno);
    operand = alloc_ea_operand('\x0f','g',0xff,0,(label_ref *)0x0);
    g_expanded_records[g_expanded_record_count].ea1 = operand;
    operand = alloc_ea_operand('\x03','\x0f',0xff,0,(label_ref *)0x0);
    g_expanded_records[g_expanded_record_count].ea2 = operand;
    g_expanded_record_count = g_expanded_record_count + 1;
  }
  if ((g_aux_record_table[aux_ix].saved_sys & 2) != 0) {
    set_psd_record(g_expanded_records + g_expanded_record_count,0x9d,'\x02','\0','\0',0,rec->expno,
                   rec->filno,rec->linno);
    operand = alloc_ea_operand('\x10','h',0xff,0,(label_ref *)0x0);
    g_expanded_records[g_expanded_record_count].ea1 = operand;
    operand = alloc_ea_operand('\x03','\x0f',0xff,0,(label_ref *)0x0);
    g_expanded_records[g_expanded_record_count].ea2 = operand;
    g_expanded_record_count = g_expanded_record_count + 1;
  }
  psVar1 = g_stack_adjust_list;
  if (g_aux_record_table[aux_ix].frame_size != 0) {
    if (g_aux_record_table[aux_ix].frame_size < 0x81) {
      set_psd_record(g_expanded_records + g_expanded_record_count,'`','\x02','\0','\0',0,rec->expno,
                     rec->filno,rec->linno);
      operand = alloc_ea_operand('\a',0xff,0xff,-g_aux_record_table[aux_ix].frame_size,
                                 (label_ref *)0x0);
      g_expanded_records[g_expanded_record_count].ea1 = operand;
      operand = alloc_ea_operand('\x01','\x0f',0xff,0,(label_ref *)0x0);
      g_expanded_records[g_expanded_record_count].ea2 = operand;
      g_expanded_record_count = g_expanded_record_count + 1;
      psVar1 = g_stack_adjust_list;
    }
    else {
      set_psd_record(&tmp_rec,'*','\x02','\0','\0',0,rec->expno,rec->filno,rec->linno);
      tmp_rec.ea1 = alloc_ea_operand('\a',0xff,0xff,-g_aux_record_table[aux_ix].frame_size,
                                     (label_ref *)0x0);
      tmp_rec.ea2 = alloc_ea_operand('\x01','\0',0xff,0,(label_ref *)0x0);
      expand_movi_record(&tmp_rec);
      set_psd_record(g_expanded_records + g_expanded_record_count,'`','\x02','\0','\0',0,rec->expno,
                     rec->filno,rec->linno);
      operand = alloc_ea_operand('\x01','\0',0xff,0,(label_ref *)0x0);
      g_expanded_records[g_expanded_record_count].ea1 = operand;
      operand = alloc_ea_operand('\x01','\x0f',0xff,0,(label_ref *)0x0);
      g_expanded_records[g_expanded_record_count].ea2 = operand;
      g_expanded_record_count = g_expanded_record_count + 1;
      psVar1 = g_stack_adjust_list;
      if (g_current_request->debug != 0) {
        psVar1 = pool_alloc(8);
        psVar1->amount = -g_aux_record_table[aux_ix].frame_size;
        if (g_stack_adjust_list != (stack_adjust_node *)0x0) {
          for (tail_node = g_stack_adjust_list; tail_node->next != (stack_adjust_node *)0x0;
              tail_node = tail_node->next) {
          }
          tail_node->next = psVar1;
          psVar1 = g_stack_adjust_list;
        }
      }
    }
  }
  g_stack_adjust_list = psVar1;
  return;
#undef low_reg
#undef reg_no
#undef tmp_rec
#undef tail_node
#undef lref
}
