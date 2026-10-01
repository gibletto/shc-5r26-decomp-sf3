#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 0041e580
// name : stmt_clobbers_memory
// size : 170
// sig  : int stmt_clobbers_memory(il_node * stmt, int memory_kind)


int __cdecl stmt_clobbers_memory(il_node *stmt,int memory_kind)

{
  byte kind;
  int is_safe;
  ushort leaf_flags;
  il_node *lhs;
  short symx;
  
  if (stmt->op == IL_CALL) {
    if ((stmt->child->op == IL_ID) && (symx = stmt->child->symx, -1 < symx)) {
      is_safe = is_memory_safe_builtin(g_symtab[symx].name);
      if (is_safe != 0) {
        return 0;
      }
    }
    return 1;
  }
  if (((&g_op_class)[(char)stmt->op] & 0x20) != 0) {
    lhs = stmt->child;
    if (memory_kind != 0) {
      if (((&g_op_class)[(char)lhs->op] & 0x10) != 0) {
        return 1;
      }
      if (((memory_kind != 0) && (lhs->op == IL_ID)) &&
         (((kind = lhs->type & 0xf0, kind == 0x60 ||
           (((kind == 0x70 || (kind == 0x80)) || (kind == 0x90)))) ||
          ((*(unsigned char *)((char *)&leaf_flags + 0)) = g_leaf_table[lhs->nleaf].flag,
          (*(unsigned char *)((char *)&leaf_flags + 1)) = g_leaf_table[lhs->nleaf].unknown_0f, (leaf_flags & 5) != 0)))) {
        return 1;
      }
    }
  }
  return 0;
}



