#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_func_node
#define g_func_node (*(il_node * *)(g_sd + 0x1e738))
#undef g_options
#define g_options (*(option_record * *)(g_sd + 0x1e714))
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 0041aca0
// name : parameter_register_index
// size : 362
// sig  : uint parameter_register_index(il_node * id)


uint __cdecl parameter_register_index(il_node *id)

{
  unsigned char _frec_80[128];
#define param_list (*(short (*)[64])(_frec_80 + 0))
  uint regno;
  byte kind;
  int last;
  short *param;
  
  if (g_options->cpu == 4) {
    regno = parameter_register_index_sh4(id);
    return regno;
  }
  last = *(char *)((int)g_symtab[g_func_node->symx].info + 6) + -1;
  order_params_stack_then_register((int)g_func_node->symx,param_list);
  regno = 0;
  if (-1 < last) {
    param = param_list + last;
    do {
      if ((g_options->cpu == 2) && (g_options->fpu_mode == '\x03')) {
        if (((id->type & 0xe0) == 0) || (kind = id->type & 0xf8, kind == 0x40)) {
          if (((g_symtab[*param].type & 0xe0) == 0) || ((g_symtab[*param].type & 0xf8) == 0x40))
          goto LAB_0041ade6;
        }
        else if ((kind != 0x28) ||
                (((g_symtab[*param].type & 0xe0) == 0x20 && ((g_symtab[*param].type & 0x18) == 8))))
        goto LAB_0041ade6;
      }
      else {
        if (((id->type & 0xe0) == 0) || ((kind = id->type & 0xf8, kind == 0x40 || (kind == 0x28))))
        {
          kind = g_symtab[*param].type;
          if (((kind & 0xe0) != 0) &&
             (((kind & 0xf8) != 0x40 && (((kind & 0xe0) != 0x20 || ((kind & 0x18) != 8))))))
          goto LAB_0041ade7;
        }
LAB_0041ade6:
        regno = regno + 1;
      }
LAB_0041ade7: ;
    } while ((*param != id->symx) && (param = param + -1, param_list <= param));
  }
  return regno;
#undef param_list
}



