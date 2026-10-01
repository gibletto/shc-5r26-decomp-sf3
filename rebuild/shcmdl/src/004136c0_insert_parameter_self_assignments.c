#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_f_chain
#define g_f_chain (*(bblock * *)(g_sd + 0x26ad0))
#undef g_func_node
#define g_func_node (*(il_node * *)(g_sd + 0x1e738))
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 004136c0
// name : insert_parameter_self_assignments
// size : 387
// sig  : void insert_parameter_self_assignments(void)


int __cdecl insert_parameter_self_assignments(void)

{
  il_node *parent;
  byte kind;
  node_list *item;
  il_node *assign;
  il_node *lhs;
  il_node *rhs;
  short *param;
  int n;
  
  parent = g_func_node->child;
  n = (int)*(char *)((int)g_symtab[g_func_node->symx].info + 6);
  param = *(short **)((int)g_symtab[g_func_node->symx].info + 0xc);
  if (0 < n) {
    do {
      kind = g_symtab[*param].type & 0xe0;
      if (((kind == 0) || ((g_symtab[*param].type & 0xf8) == 0x40)) || (kind == 0x20)) {
        item = regalloc_alloc(8);
        assign = alloc_node();
        lhs = alloc_node();
        rhs = alloc_node();
        item->node = assign;
        insert_operands(assign,lhs,1);
        insert_operands(assign,rhs,1);
        item->next = g_f_chain->ilnode;
        g_f_chain->ilnode = item;
        insert_operands(parent,assign,1);
        assign->op = IL_ASSIGN;
        assign->type = g_symtab[*param].type;
        *(byte *)&assign->flag = (byte)assign->flag | 0x10;
        rhs->op = IL_ID;
        rhs->type = g_symtab[*param].type;
        rhs->symx = *param;
        rhs->nleaf = g_symtab[*param].ms_leaf;
        lhs->op = IL_ID;
        lhs->type = g_symtab[*param].type;
        lhs->symx = *param;
        lhs->nleaf = g_symtab[*param].ms_leaf;
      }
      param = param + 1;
      n = n + -1;
    } while (n != 0);
  }
  return;
}



