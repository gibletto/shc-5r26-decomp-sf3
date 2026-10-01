#include "decls.h"
#include "imports.h"

// entry: 0040447c
// name : store_immediate_in_operand
// size : 277
// sig  : void __cdecl store_immediate_in_operand(short *value,ea *op,int size)


int __cdecl store_immediate_in_operand(short *value,ea *op,int size)

{
  unsigned char _frec_10[16];
#define auStack_10 (*(undefined1 (*)[4])(_frec_10 + 0))
#define i (*(char *)(_frec_10 + 4))
#define local_8 (*(undefined1 *)(_frec_10 + 8))
#define cStack_7 (*(char *)(_frec_10 + 9))
#define cStack_6 (*(char *)(_frec_10 + 10))
  short imm;
  
  for (i = '\0'; i < '\x04'; i = i + '\x01') {
    auStack_10[i] = 0;
  }
  if (size == 1) {
    imm = *value;
    *(char *)&op->disp = (char)imm;
    cStack_7 = (char)imm >> 7;
    *(char *)((int)&op->disp + 1) = cStack_7;
    *(char *)((int)&op->disp + 2) = cStack_7;
    *(char *)((int)&op->disp + 3) = cStack_7;
  }
  else if (size == 2) {
    imm = *value;
    local_8 = (undefined1)imm;
    *(undefined1 *)&op->disp = local_8;
    cStack_7 = (char)((ushort)imm >> 8);
    *(char *)((int)&op->disp + 1) = cStack_7;
    cStack_6 = (char)(imm >> 0xf);
    *(char *)((int)&op->disp + 2) = cStack_6;
    *(char *)((int)&op->disp + 3) = cStack_6;
  }
  else if (size == 4) {
    *(char *)&op->disp = (char)*value;
    *(undefined1 *)((int)&op->disp + 1) = *(undefined1 *)((int)value + 1);
    *(char *)((int)&op->disp + 2) = (char)value[1];
    *(undefined1 *)((int)&op->disp + 3) = *(undefined1 *)((int)value + 3);
  }
  else {
    report_message_at_source_line(0,0,0x1322,(char *)0x0);
  }
  return;
#undef auStack_10
#undef i
#undef local_8
#undef cStack_7
#undef cStack_6
}
