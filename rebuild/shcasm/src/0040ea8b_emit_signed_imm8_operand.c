#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))


// entry: 0040ea8b
// name : emit_signed_imm8_operand
// size : 617
// sig  : ushort emit_signed_imm8_operand(ea * op, int field_shift, int unused_3, int unused_4, short filno, uint linno)


ushort __cdecl emit_signed_imm8_operand(ea *op,int field_shift,int unused_3,int unused_4,short filno,uint linno)

{
  int reloc_location;
  short out_stream;
  bool labels_printed;
  uint encoded_imm;
  uint imm_value;
  ushort field_bits;
  
  field_bits = 0;
  if (((op->labels == (label_ref *)0x0) || (op->labels->labno2 != -0x8000)) ||
     (op->labels->next != (label_ref *)0x0)) {
    encoded_imm = evaluate_label_expression(op->disp,op->labels);
    imm_value = encoded_imm;
  }
  else {
    imm_value = op->disp;
    if (g_current_request->code == 1) {
      if (g_current_request->endian == '\0') {
        reloc_location = g_location_counter + 1;
      }
      else {
        reloc_location = g_location_counter;
      }
      encoded_imm = emit_relocation_expression(op->labels,op->disp,reloc_location,8,0,1);
    }
  }
  if (((int)imm_value < -0x80) || (0x7f < (int)imm_value)) {
    if ((op->labels == (label_ref *)0x0) ||
       ((op->labels->labno2 != -0x8000 || (op->labels->next != (label_ref *)0x0)))) {
      report_message_at_source_line(filno,linno & 0xffff,0x133a,(char *)0x0);
    }
    else {
      report_message_at_source_line(filno,linno & 0xffff,0xa98,(char *)0x0);
      if (g_max_error_severity < 3) {
        g_max_error_severity = 3;
      }
    }
  }
  if (field_shift != -1) {
    field_bits = (ushort)((encoded_imm & 0xff) << ((byte)field_shift & 0x1f));
  }
  if (((g_current_request->show & 2) != 0) || (g_current_request->code != 1)) {
    if ((g_current_request->show & 2) == 0) {
      out_stream = 2;
    }
    else {
      out_stream = 3;
    }
    put_char_at_column(out_stream,'#',2);
    labels_printed = false;
    if ((g_current_request->show & 2) == 0) {
      if (op->labels != (label_ref *)0x0) {
        print_label_ref_expression(out_stream,op->labels,0);
        labels_printed = true;
      }
    }
    else {
      labels_printed = op->labels != (label_ref *)0x0;
      if (labels_printed) {
        print_label_ref_expression_to_listing(op->labels,0);
      }
    }
    write_operand_offset(out_stream,op->disp,(short)labels_printed);
  }
  return field_bits;
}



