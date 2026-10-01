#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 00407a10
// name : subtree_has_symbol_attr_2e
// size : 92
// sig  : int subtree_has_symbol_attr_2e(il_node * node)


int __cdecl subtree_has_symbol_attr_2e(il_node *node)

{
  int found;
  il_node *child;
  
  for (child = node->child; child != (il_node *)0x0; child = child->next) {
    found = subtree_has_symbol_attr_2e(child);
    if (found != 0) {
      return 1;
    }
  }
  if (((node->op == IL_ID) && (0 < node->symx)) && ((g_symtab[node->symx].attr & 3) != 0)) {
    return 1;
  }
  return 0;
}



