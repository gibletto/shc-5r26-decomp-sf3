#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))


// entry: 0040ecf4
// name : emit_trapa_imm8_operand
// size : 220
// sig  : ushort emit_trapa_imm8_operand(ea * op, int field_shift, int unused_3, int unused_4, short filno, uint linno)


ushort __cdecl emit_trapa_imm8_operand(ea *op,int field_shift,int unused_3,int unused_4,short filno,uint linno)

{
  short out_stream;
  ushort field_bits;
  
  field_bits = 0;
  if ((op->disp & 0xffffff00U) != 0) {
    report_message_at_source_line(filno,linno & 0xffff,0x133a,(char *)0x0);
  }
  if (field_shift != -1) {
    field_bits = (ushort)((op->disp & 0xffU) << ((byte)field_shift & 0x1f));
  }
  if (((g_current_request->show & 2) != 0) || (g_current_request->code != 1)) {
    if ((g_current_request->show & 2) == 0) {
      out_stream = 2;
    }
    else {
      out_stream = 3;
    }
    put_char_at_column(out_stream,'#',2);
    write_operand_offset(out_stream,op->disp,0);
  }
  return field_bits;
}



