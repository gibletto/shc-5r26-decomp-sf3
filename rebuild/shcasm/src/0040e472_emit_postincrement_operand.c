#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))


// entry: 0040e472
// name : emit_postincrement_operand
// size : 190
// sig  : ushort emit_postincrement_operand(ea * op, int field_shift)


ushort __cdecl emit_postincrement_operand(ea *op,int field_shift)

{
  short out_stream;
  ushort field_bits;
  
  field_bits = 0;
  if (field_shift != -1) {
    field_bits = (ushort)op->base << ((byte)field_shift & 0x1f);
  }
  if (((g_current_request->show & 2) != 0) || (g_current_request->code != 1)) {
    if ((g_current_request->show & 2) == 0) {
      out_stream = 2;
    }
    else {
      out_stream = 3;
    }
    put_char_at_column(out_stream,'@',2);
    write_register_name(out_stream,(short)(char)op->base);
    put_char_at_column(out_stream,'+',2);
  }
  return field_bits;
}



