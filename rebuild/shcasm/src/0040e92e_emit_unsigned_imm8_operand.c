#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))


// entry: 0040e92e
// name : emit_unsigned_imm8_operand
// size : 349
// sig  : ushort emit_unsigned_imm8_operand(ea * op, int field_shift, int unused_3, int unused_4, short filno, uint linno)


ushort __cdecl emit_unsigned_imm8_operand(ea *op,int field_shift,int unused_3,int unused_4,short filno,uint linno)

{
  uint imm;
  bool has_labels;
  short out_stream;
  ushort labels_printed;
  ushort field_bits;
  
  field_bits = 0;
  imm = evaluate_label_expression(op->disp,op->labels);
  if ((imm & 0xffffff00) != 0) {
    report_message_at_source_line(filno,linno & 0xffff,0x133a,(char *)0x0);
  }
  if (field_shift != -1) {
    field_bits = (ushort)((imm & 0xff) << ((byte)field_shift & 0x1f));
  }
  if (((g_current_request->show & 2) != 0) || (g_current_request->code != 1)) {
    if ((g_current_request->show & 2) == 0) {
      out_stream = 2;
    }
    else {
      out_stream = 3;
    }
    put_char_at_column(out_stream,'#',2);
    labels_printed = 0;
    if ((g_current_request->show & 2) == 0) {
      if (op->labels != (label_ref *)0x0) {
        print_label_ref_expression(out_stream,op->labels,0);
        labels_printed = 1;
      }
    }
    else {
      has_labels = op->labels != (label_ref *)0x0;
      if (has_labels) {
        print_label_ref_expression_to_listing(op->labels,0);
      }
      labels_printed = (ushort)has_labels;
    }
    write_operand_offset(out_stream,op->disp,labels_printed);
  }
  return field_bits;
}



