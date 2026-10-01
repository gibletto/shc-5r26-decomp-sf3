#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))


// entry: 0040e072
// name : emit_memory_operand
// size : 1024
// sig  : ushort emit_memory_operand(ea * op, int reg_shift, int disp_shift, int size_code, short filno, uint linno)


ushort __cdecl emit_memory_operand(ea *op,int reg_shift,int disp_shift,int size_code,short filno,uint linno)

{
  bool has_labels;
  int reloc_addr;
  short channel;
  ushort has_label_text;
  int field_value;
  short disp_mask;
  int disp_value;
  ushort bits;
  
  bits = 0;
  if (reg_shift != -1) {
    bits = (ushort)((int)(char)op->base << ((byte)reg_shift & 0x1f));
  }
  if (disp_shift != -1) {
    if (((op->labels == (label_ref *)0x0) || (op->labels->labno2 != -0x8000)) ||
       (op->labels->next != (label_ref *)0x0)) {
      disp_value = evaluate_label_expression(op->disp,op->labels);
      if ((op->type & 0x1f) == 10) {
        if (size_code == 2) {
          disp_value = disp_value - (g_location_counter + 4U & 0xfffffffc);
        }
        else {
          disp_value = disp_value - (g_location_counter + 4U & 0xfffffffe);
        }
      }
      field_value = disp_value;
    }
    else {
      disp_value = op->disp;
      if (g_current_request->code == 1) {
        if (g_current_request->endian == '\0') {
          reloc_addr = g_location_counter + 1;
        }
        else {
          reloc_addr = g_location_counter;
        }
        field_value = emit_relocation_expression(op->labels,op->disp,reloc_addr,8,size_code,0);
      }
    }
    if ((op->type & 0x1f) == 2) {
      disp_mask = 0xf;
    }
    else {
      disp_mask = 0xff;
    }
    if (disp_value % (1 << ((byte)size_code & 0x1f)) != 0) {
      report_message_at_source_line(filno,linno & 0xffff,0xc1c,(char *)0x0);
    }
    if ((~(int)disp_mask & disp_value >> ((byte)size_code & 0x1f)) != 0) {
      if (((op->labels == (label_ref *)0x0) || (op->labels->labno2 != -0x8000)) ||
         (op->labels->next != (label_ref *)0x0)) {
        report_message_at_source_line(filno,linno & 0xffff,0x133a,(char *)0x0);
      }
      else {
        report_message_at_source_line(filno,linno & 0xffff,0xa98,(char *)0x0);
        if (g_max_error_severity < 3) {
          g_max_error_severity = 3;
        }
      }
    }
    bits = (ushort)((field_value >> ((byte)size_code & 0x1f) & (int)disp_mask) <<
                   ((byte)disp_shift & 0x1f)) | bits;
  }
  if (((g_current_request->show & 2) != 0) || (g_current_request->code != 1)) {
    if ((g_current_request->show & 2) == 0) {
      channel = 2;
    }
    else {
      channel = 3;
    }
    if ((op->type & 0x1f) != 10) {
      put_char_at_column(channel,'@',2);
    }
    if ((op->type & 0x1f) == 2) {
      write_register_name(channel,(short)(char)op->base);
    }
    else {
      if ((op->type & 0x1f) != 10) {
        put_char_at_column(channel,'(',2);
      }
      if (disp_shift == -1) {
        write_register_name(channel,(short)(char)op->index);
      }
      else {
        has_label_text = 0;
        if ((g_current_request->show & 2) == 0) {
          if (op->labels != (label_ref *)0x0) {
            print_label_ref_expression(channel,op->labels,0);
            has_label_text = 1;
          }
        }
        else {
          has_labels = op->labels != (label_ref *)0x0;
          if (has_labels) {
            print_label_ref_expression_to_listing(op->labels,0);
          }
          has_label_text = (ushort)has_labels;
        }
        write_operand_offset(channel,op->disp,has_label_text);
      }
      if ((op->type & 0x1f) != 10) {
        put_char_at_column(channel,',',2);
        write_register_name(channel,(short)(char)op->base);
        put_char_at_column(channel,')',2);
      }
    }
  }
  return bits;
}



