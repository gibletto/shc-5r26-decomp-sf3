#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 004208b0
// name : warn_uninlined_calls
// size : 122
// sig  : void warn_uninlined_calls(il_node * tree)


int __cdecl warn_uninlined_calls(il_node *tree)

{
  il_node *child;
  
  for (child = tree->child; child != (il_node *)0x0; child = child->next) {
    warn_uninlined_calls(child);
  }
  if ((((tree->op == IL_CALL) && (child = tree->child, child->op == IL_ID)) &&
      (g_symtab[child->symx].no_inline != '\0')) && ((tree->flag2 & 0x40) == 0)) {
    tree->flag2 = tree->flag2 | 0x40;
    report_message(0x578,tree,g_symtab[child->symx].name);
  }
  return;
}



