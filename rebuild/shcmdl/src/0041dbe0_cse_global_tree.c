#include "decls.h"
#include "imports.h"
#include "tempexpr.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_f_chain
#define g_f_chain (*(bblock * *)(g_sd + 0x26ad0))
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 0041dbe0
// name : cse_global_tree
// size : 158
// sig  : il_node * cse_global_tree(il_node * node, bblock * block)


il_node * __cdecl cse_global_tree(il_node *node,bblock *block)

{
  il_node *child;
  int has_temp;
  bblock *blk;
  char op_class;
  
  for (child = node->child; child != (il_node *)0x0; child = child->next) {
    child = cse_global_tree(child,block);
  }
  if (((((node->op == IL_ID) && (0 < node->symx)) && ('\0' < g_symtab[node->symx].sclass)) &&
      (g_symtab[node->symx].sclass < '\x05')) ||
     (((op_class = (&g_op_class)[(char)node->op], op_class == '\x04' || (op_class == '\b')) ||
      (op_class == '\x10')))) {
    has_temp = tree_has_temp_id(node);
    if (has_temp != 0 && TEMP_EXPR_SKIP(node)) {
      return node;
    }
    node = cse_eliminate_node(node);
    for (blk = g_f_chain->f_next; blk != (bblock *)0x0; blk = blk->f_next) {
      *(byte *)&blk->flag = (byte)blk->flag & 0x3f;
    }
  }
  return node;
}



