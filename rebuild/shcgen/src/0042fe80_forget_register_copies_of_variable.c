#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))


// entry: 0042fe80
// name : forget_register_copies_of_variable
// size : 212
// sig  : void forget_register_copies_of_variable(gen_node * node)


int __cdecl forget_register_copies_of_variable(gen_node *node)

{
  byte fpu_mode;
  reg_content *contents;
  short i;
  ushort lreg;
  reg_content *slot;
  
  if ((node->type & 0xf8) == 0x28) {
    if ((g_request->cpu == 2) && (g_request->fpu_mode == '\x03')) {
      fpu_mode = 1;
    }
    else {
      fpu_mode = -(g_request->cpu == 4) & 2;
    }
    contents = g_fpr_contents;
    if (fpu_mode != 0) goto LAB_0042fece;
  }
  contents = g_gpr_contents;
LAB_0042fece:
  lreg = node->lreg;
  i = 0;
  if (lreg != 0) {
    i = 0;
    do {
      slot = contents + i;
      if (((contents[i].u.lreg == (ushort)((lreg ^ (short)lreg >> 0xf) - ((short)lreg >> 0xf))) &&
          ((slot->flags & 0x40) == 0)) &&
         (((int)node->symx == slot->value && (slot->type == node->type)))) {
        slot->value = 0;
      }
      i = i + 1;
    } while (i < 4);
    return;
  }
  do {
    slot = contents + i;
    if (((contents[i].u.lreg == 0) && ((slot->flags & 0x40) == 0)) &&
       ((int)node->symx == slot->value)) {
      slot->value = 0;
    }
    i = i + 1;
  } while (i < 4);
  return;
}



