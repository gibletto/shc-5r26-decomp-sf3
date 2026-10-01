#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 00409af0
// name : mark_referenced_functions_in_tree
// size : 180
// sig  : void mark_referenced_functions_in_tree(il_node * node)


int __cdecl mark_referenced_functions_in_tree(il_node *node)

{
  il_node *child;
  short symx;
  
  for (child = node->child; child != (il_node *)0x0; child = child->next) {
    mark_referenced_functions_in_tree(child);
  }
  if (node->op == IL_ID) {
    if (((node->type & 0xf8) == 0x48) && (symx = node->symx, 0 < symx)) {
      if (((g_symtab[symx].attr & 0x80) != 0) && ((g_symtab[symx].flags & 0x40) == 0)) {
        g_symtab[symx].attr = g_symtab[symx].attr & 0x7f;
        g_symbol_table_modified = '\x01';
      }
    }
    if ((((node->op == IL_ID) && (node->parent->op != IL_CALL)) && ((node->type & 0xf8) == 0x48)) &&
       (symx = node->symx, 0 < symx)) {
      if (((g_symtab[symx].attr & 0x80) != 0) && ((g_symtab[symx].flags & 0x40) != 0)) {
        g_symtab[symx].attr = g_symtab[symx].attr & 0x7f;
        g_symbol_table_modified = '\x01';
      }
    }
  }
  return;
}



