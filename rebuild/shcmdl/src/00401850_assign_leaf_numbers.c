#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 00401850
// name : assign_leaf_numbers
// size : 394
// sig  : void assign_leaf_numbers(il_node * node)


int __cdecl assign_leaf_numbers(il_node *node)

{
  short symno;
  short nleaf;
  int iVar1;
  int leafno;
  symbol *sym;
  short *leaf_symno;
  il_node *child;
  il_op parent_op;
  char sclass;
  
  for (child = node->child; child != (il_node *)0x0; child = child->next) {
    parent_op = node->op;
    if ((((parent_op == IL_COND) || (parent_op == IL_AND)) || (parent_op == IL_OR)) &&
       (iVar1 = operand_index(child), iVar1 == 2)) {
      g_leaf_cond_depth = g_leaf_cond_depth + 1;
    }
    assign_leaf_numbers(child);
  }
  switch(node->op) {
  case IL_PRI:
  case IL_PRD:
  case IL_POI:
  case IL_POD:
  case IL_A_ADD:
  case IL_A_SUB:
  case IL_A_MUL:
  case IL_A_DIV:
  case IL_A_MOD:
  case IL_A_SL:
  case IL_A_SR:
  case IL_A_AND:
  case IL_A_XOR:
  case IL_A_OR:
  case IL_ASSIGN:
    if ((g_leaf_cond_depth != 0) && (node->child->op == IL_ID)) {
      g_leaf_table[node->child->nleaf].flag = g_leaf_table[node->child->nleaf].flag | 2;
      return;
    }
    break;
  case IL_AND:
  case IL_OR:
  case IL_COND:
    g_leaf_cond_depth = g_leaf_cond_depth + -1;
    return;
  case IL_ID:
    symno = node->symx;
    iVar1 = (int)symno;
    if (0 < iVar1) {
      if (g_symtab[iVar1].ms_leaf == 0) {
        leafno = new_leaf(symno);
        nleaf = (short)leafno;
        remember_leafed_symbol(symno);
        g_symtab[iVar1].ms_leaf = nleaf;
        sym = g_symtab + iVar1;
        sclass = sym->sclass;
        if (((sclass == '\x01') || (sclass == '\x02')) || ((sclass == '\x03' || (sclass == '\x04')))
           ) {
          g_leaf_table[nleaf].flag = g_leaf_table[nleaf].flag | 1;
        }
        if ((sym->type & 2) != 0) {
          g_leaf_table[nleaf].flag = g_leaf_table[nleaf].flag | 8;
        }
        if (sym->impvol != '\0') {
          g_leaf_table[nleaf].flag = g_leaf_table[nleaf].flag | 4;
        }
      }
      node->nleaf = g_symtab[iVar1].ms_leaf;
      return;
    }
    leafno = 1;
    if (0 < g_leaf_count) {
      leaf_symno = &g_leaf_table[1].symno;
      do {
        if (*leaf_symno == iVar1) break;
        leaf_symno = leaf_symno + 8;
        leafno = leafno + 1;
      } while (leafno <= g_leaf_count);
    }
    if (g_leaf_count < leafno) {
      iVar1 = new_leaf(symno);
      node->nleaf = (short)iVar1;
      return;
    }
    node->nleaf = (short)leafno;
  }
  return;
}



