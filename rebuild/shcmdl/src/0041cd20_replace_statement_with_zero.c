#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 0041cd20
// name : replace_statement_with_zero
// size : 125
// sig  : void replace_statement_with_zero(il_node * stmt)


int __cdecl replace_statement_with_zero(il_node *stmt)

{
  int left;
  char *name_p;
  char *builtin_p;
  bool equal;
  il_node *child;
  short symx;
  
  if ((stmt != (il_node *)0x0) && (stmt->op != IL_NULL)) {
    child = stmt->child;
    if (child != (il_node *)0x0) {
      if ((stmt->op == IL_CALL) && (child->op == IL_ID)) {
        symx = child->symx;
        equal = symx == 0;
        if (-1 < symx) {
          left = 0xd;
          name_p = g_symtab[symx].name;
          builtin_p = s__builtin_asm_00434050;
          do {
            if (left == 0) break;
            left = left + -1;
            equal = *name_p == *builtin_p;
            name_p = name_p + 1;
            builtin_p = builtin_p + 1;
          } while (equal);
          if (equal) {
            return;
          }
        }
      }
      free_tree(stmt->child);
      stmt->child = (il_node *)0x0;
    }
    stmt->op = IL_CONST;
    stmt->val = 0;
    stmt->val2 = 0;
    stmt->type = '\x10';
    stmt->val3 = 0;
  }
  return;
}



