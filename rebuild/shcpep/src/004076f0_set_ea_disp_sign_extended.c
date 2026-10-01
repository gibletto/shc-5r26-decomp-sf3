#include "decls.h"
#include "imports.h"

// entry: 004076f0
// name : set_ea_disp_sign_extended
// size : 169
// sig  : void set_ea_disp_sign_extended(short * value, ea * op, int size)


int __cdecl set_ea_disp_sign_extended(short *value,ea *op,int size)

{
  char cStack_3;
  char sign;
  short half;
  
  if (size == 1) {
    cStack_3 = (char)*value >> 7;
    *(char *)&op->disp = (char)*value;
    *(char *)((int)&op->disp + 1) = cStack_3;
    *(char *)((int)&op->disp + 2) = cStack_3;
    *(char *)((int)&op->disp + 3) = cStack_3;
    return;
  }
  if (size != 2) {
    if (size != 4) {
      report_compiler_message(0,0,0x1322,(char *)0x0);
      return;
    }
    *(char *)&op->disp = (char)*value;
    *(undefined1 *)((int)&op->disp + 1) = *(undefined1 *)((int)value + 1);
    *(char *)((int)&op->disp + 2) = (char)value[1];
    *(undefined1 *)((int)&op->disp + 3) = *(undefined1 *)((int)value + 3);
    return;
  }
  half = *value;
  cStack_3 = (char)((ushort)half >> 8);
  *(char *)&op->disp = (char)half;
  *(char *)((int)&op->disp + 1) = cStack_3;
  sign = (char)(half >> 0xf);
  *(char *)((int)&op->disp + 2) = sign;
  *(char *)((int)&op->disp + 3) = sign;
  return;
}



