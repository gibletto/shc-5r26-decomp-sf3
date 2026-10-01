#include "decls.h"
#include "imports.h"

// entry: 004114e0
// name : emit_shift_by_constant
// size : 419
// sig  : void emit_shift_by_constant(ea * reg, char kind, int count)


int __cdecl emit_shift_by_constant(ea *reg,char kind,int count)

{
  ea *copy;
  int steps;
  uint uVar1;
  uint uVar2;
  short i;
  
  if ((kind == '\x01') || (kind == '\x02')) {
    i = 0;
    uVar1 = count >> 0x1f;
    steps = (int)(count + (uVar1 & 0xf)) >> 4;
    if (0 < steps) {
      do {
        copy = copy_ea(reg);
        i = i + 1;
        emit_psd_for_node((ushort)(byte)((-(kind == '\x02') & 0xf0U) + 0x5d),-1,'\0','\x02',copy,
                          (ea *)0x0,(gen_node *)0x0);
      } while (i < steps);
    }
    i = 0;
    uVar1 = ((count ^ uVar1) - uVar1 & 0xf ^ uVar1) - uVar1;
    uVar2 = (int)uVar1 >> 0x1f;
    steps = (int)(uVar1 + (uVar2 & 7)) >> 3;
    if (0 < steps) {
      do {
        copy = copy_ea(reg);
        i = i + 1;
        emit_psd_for_node((ushort)(byte)((-(kind == '\x02') & 0xf0U) + 0x5c),-1,'\0','\x02',copy,
                          (ea *)0x0,(gen_node *)0x0);
      } while (i < steps);
    }
    i = 0;
    uVar2 = ((uVar1 ^ uVar2) - uVar2 & 7 ^ uVar2) - uVar2;
    if (0 < (int)uVar2 / 2) {
      do {
        copy = copy_ea(reg);
        i = i + 1;
        emit_psd_for_node((ushort)(byte)((-(kind == '\x02') & 0xf0U) + 0x5b),-1,'\0','\x02',copy,
                          (ea *)0x0,(gen_node *)0x0);
      } while ((int)i < (int)uVar2 / 2);
    }
    uVar1 = (int)uVar2 >> 0x1f;
    if (((uVar2 ^ uVar1) - uVar1 & 1 ^ uVar1) != uVar1) {
      copy = copy_ea(reg);
      emit_psd_for_node((ushort)(byte)((-(kind == '\x02') & 0xf0U) + 0x5a),-1,'\0','\x02',copy,
                        (ea *)0x0,(gen_node *)0x0);
    }
  }
  else {
    i = 0;
    if (0 < count) {
      do {
        i = i + 1;
        copy = copy_ea(reg);
        emit_psd_for_node(0x59,-1,'\0','\x02',copy,(ea *)0x0,(gen_node *)0x0);
      } while (i < count);
      return;
    }
  }
  return;
}



