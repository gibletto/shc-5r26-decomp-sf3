#include "decls.h"
#include "imports.h"

// entry: 0041a1a0
// name : argument_register_index_sh4
// size : 250
// sig  : uint argument_register_index_sh4(il_node * arg)


uint __cdecl argument_register_index_sh4(il_node *arg)

{
  byte kind;
  il_node *operand;
  int index;
  uint sign;
  uint uVar1;
  byte used_fregs;
  
  uVar1 = 0;
  used_fregs = 0;
  operand = last_operand(arg->parent);
  index = operand_index(operand);
  index = index + -1;
  operand = nth_operand(index,operand->parent);
  if (index < 1) {
    return (uint)operand;
  }
  do {
    kind = arg->type & 0xe0;
    if ((kind == 0) || ((arg->type & 0xf8) == 0x40)) {
      if (((operand->type & 0xe0) == 0) || ((operand->type & 0xf8) == 0x40)) goto LAB_0041a26a;
    }
    else {
      if (kind == 0x20) {
        if ((operand->type & 0xe0) != 0x20) goto LAB_0041a26b;
        uVar1 = 0;
        do {
          kind = (byte)uVar1;
          if ((((uint)used_fregs & 1 << (kind & 0x1f)) == 0) &&
             ((sign = (int)uVar1 >> 0x1f, ((uVar1 ^ sign) - sign & 1 ^ sign) == sign ||
              ((operand->type & 0xf8) != 0x30)))) {
            if ((operand->type & 0xf8) == 0x30) {
              used_fregs = used_fregs | '\x01' << (kind + 1 & 0x1f);
            }
            used_fregs = used_fregs | '\x01' << (kind & 0x1f);
            break;
          }
          uVar1 = uVar1 + 1;
        } while ((int)uVar1 < 8);
      }
LAB_0041a26a:
      uVar1 = uVar1 + 1;
    }
LAB_0041a26b:
    if (operand == arg) {
      return uVar1;
    }
    index = index + -1;
    operand = nth_operand(index,operand->parent);
    if (index < 1) {
      return (uint)operand;
    }
  } while( true );
}



