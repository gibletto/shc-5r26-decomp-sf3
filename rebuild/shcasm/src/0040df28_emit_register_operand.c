#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))


// entry: 0040df28
// name : emit_register_operand
// size : 297
// sig  : ushort emit_register_operand(ea * op, int field_shift)


ushort __cdecl emit_register_operand(ea *op,int field_shift)

{
  uint sign;
  ushort bits;
  
  bits = 0;
  if (field_shift != -1) {
    switch(op->base) {
    case REG_FV0:
      bits = (ushort)(0 << ((byte)field_shift & 0x1f));
      break;
    default:
      sign = (int)(char)op->base >> 0x1f;
      bits = (ushort)((((int)(char)op->base ^ sign) - sign & 0xf ^ sign) - sign <<
                     ((byte)field_shift & 0x1f));
      break;
    case REG_FV4:
      bits = (ushort)(1 << ((byte)field_shift & 0x1f));
      break;
    case REG_FV8:
      bits = (ushort)(2 << ((byte)field_shift & 0x1f));
      break;
    case REG_FV12:
      bits = (ushort)(3 << ((byte)field_shift & 0x1f));
    }
  }
  if (g_current_request->code == 1) {
    if ((g_current_request->show & 2) != 0) {
      write_register_name(3,(short)(char)op->base);
    }
  }
  else {
    write_register_name(2,(short)(char)op->base);
  }
  return bits;
}



