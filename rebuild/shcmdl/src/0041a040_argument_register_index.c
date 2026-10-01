#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_options
#define g_options (*(option_record * *)(g_sd + 0x1e714))
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 0041a040
// name : argument_register_index
// size : 352
// sig  : uint argument_register_index(il_node * arg)


uint __cdecl argument_register_index(il_node *arg)

{
  uint regno;
  il_node *operand;
  int last_index;
  byte kind;
  int left;
  int n;
  char *name_p;
  char *builtin_p;
  bool equal;
  short symx;
  
  if (g_options->cpu == 4) {
    regno = argument_register_index_sh4(arg);
    return regno;
  }
  operand = last_operand(arg->parent);
  last_index = operand_index(operand);
  last_index = last_index + -1;
  regno = 0;
  operand = nth_operand(last_index,operand->parent);
  n = last_index;
  if (last_index < 1) {
    return (uint)operand;
  }
  do {
    if ((g_options->cpu == 2) && (g_options->fpu_mode == '\x03')) {
      if (((arg->type & 0xe0) == 0) || (kind = arg->type & 0xf8, kind == 0x40)) {
        if (((operand->type & 0xe0) != 0) && ((operand->type & 0xf8) != 0x40)) goto LAB_0041a114;
      }
      else if (kind == 0x28) {
        kind = operand->type & 0xf8;
        goto joined_r0x0041a111;
      }
LAB_0041a113:
      regno = regno + 1;
    }
    else {
      if (((((arg->type & 0xe0) != 0) && ((kind = arg->type & 0xf8, kind != 0x40 && (kind != 0x28)))
           ) || ((operand->type & 0xe0) == 0)) || (kind = operand->type & 0xf8, kind == 0x40))
      goto LAB_0041a113;
joined_r0x0041a111:
      if (kind == 0x28) goto LAB_0041a113;
    }
LAB_0041a114:
    if (operand == arg) {
      operand = arg->parent->parent->child;
      if (operand->op != IL_ID) {
        return regno;
      }
      symx = operand->symx;
      equal = symx == 0;
      if (symx < 0) {
        return regno;
      }
      left = 0x13;
      name_p = g_symtab[symx].name;
      builtin_p = s__builtin_trapa_svc_004340a0;
      break;
    }
    n = n + -1;
    operand = nth_operand(n,operand->parent);
    if (n < 1) {
      return (uint)operand;
    }
  } while( true );
  while( true ) {
    left = left + -1;
    equal = *name_p == *builtin_p;
    name_p = name_p + 1;
    builtin_p = builtin_p + 1;
    if (!equal) break;
    if (left == 0) break;
  }
  if (equal) {
    if ((last_index != n) && (last_index - n != 1)) {
      return regno - 2;
    }
    regno = 0;
  }
  return regno;
}



