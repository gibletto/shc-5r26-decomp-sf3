#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_func_node
#define g_func_node (*(il_node * *)(g_sd + 0x1e738))
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 00412760
// name : special_change
// size : 100
// sig  : void special_change(void)


int __cdecl special_change(void)

{
  short i;
  
  if (*(char *)((int)g_symtab[g_func_node->symx].info + 6) == '\x02') {
    i = 0;
    do {
      if ((g_symtab[*(short *)(*(int *)((int)g_symtab[g_func_node->symx].info + 0xc) + i * 2)].type
          & 0xf8) != 0x40) {
        return;
      }
      i = i + 1;
    } while (i < 2);
    special_change_body(g_func_node->child);
  }
  return;
}



