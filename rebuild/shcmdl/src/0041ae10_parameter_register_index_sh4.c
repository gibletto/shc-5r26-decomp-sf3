#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_func_node
#define g_func_node (*(il_node * *)(g_sd + 0x1e738))
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 0041ae10
// name : parameter_register_index_sh4
// size : 348
// sig  : uint parameter_register_index_sh4(il_node * id)


uint __cdecl parameter_register_index_sh4(il_node *id)

{
  unsigned char _frec_91[145];
#define used_fregs (*(byte *)(_frec_91 + 0))
#define param_list (*(short (*)[64])(_frec_91 + 17))
  byte kind;
  uint sign;
  uint regno;
  int last;
  short *param;
  byte bit;
  byte param_type;
  
  regno = 0;
  used_fregs = 0;
  last = *(char *)((int)g_symtab[g_func_node->symx].info + 6) + -1;
  order_params_stack_then_register((int)g_func_node->symx,param_list);
  if (-1 < last) {
    param = param_list + last;
    kind = id->type & 0xe0;
    do {
      if ((kind == 0) || ((id->type & 0xf8) == 0x40)) {
        if (((g_symtab[*param].type & 0xe0) == 0) || ((g_symtab[*param].type & 0xf8) == 0x40))
        goto LAB_0041af4a;
      }
      else {
        if (kind == 0x20) {
          param_type = g_symtab[*param].type;
          if ((param_type & 0xe0) != 0x20) goto LAB_0041af4b;
          regno = 0;
          do {
            bit = (byte)regno;
            if ((((uint)used_fregs & 1 << (bit & 0x1f)) == 0) &&
               ((sign = (int)regno >> 0x1f, ((regno ^ sign) - sign & 1 ^ sign) == sign ||
                ((param_type & 0x18) != 0x10)))) {
              if ((param_type & 0x18) == 0x10) {
                used_fregs = used_fregs | '\x01' << (bit + 1 & 0x1f);
              }
              used_fregs = used_fregs | '\x01' << (bit & 0x1f);
              break;
            }
            regno = regno + 1;
          } while ((int)regno < 8);
        }
LAB_0041af4a:
        regno = regno + 1;
      }
LAB_0041af4b: ;
    } while ((*param != id->symx) && (param = param + -1, param_list <= param));
  }
  return regno;
#undef used_fregs
#undef param_list
}



