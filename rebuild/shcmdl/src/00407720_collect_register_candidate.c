#include "decls.h"
#include "imports.h"
#include "argconst.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_options
#define g_options (*(option_record * *)(g_sd + 0x1e714))
#undef g_regalloc_block
#define g_regalloc_block (*(bblock * *)(g_sd + 0x1648c))
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 00407720
// name : collect_register_candidate
// size : 743
// sig  : void collect_register_candidate(il_node * node)


int __cdecl collect_register_candidate(il_node *node)

{
  byte type_class;
  byte size_class;
  int iVar1;
  node_list *cell;
  il_node *operand;
  uint value;
  il_node *call;
  char sclass;
  short symx;
  
  if (node->cmnexp == (il_node *)0x0) {
    return;
  }
  if (node != node->cmnexp) {
    return;
  }
  if (((node->op & IL_NON_F0) == IL_A_ADD) || (operand = node, (node->op & IL_NON_F8) == IL_PRI)) {
    operand = node->child;
  }
  if (operand->op == IL_ID) {
    if ((0 < operand->symx) && (g_symtab[operand->symx].unknown_38 != -1)) {
      return;
    }
    type_class = operand->type & 0xf0;
    if (((((type_class == 0x80) || (type_class == 0x90)) && (operand->parent->op == IL_ASSIGN)) &&
        ((iVar1 = operand_index(operand), iVar1 == 2 &&
         ((type_class = operand->parent->type & 0xf0, type_class == 0x80 || (type_class == 0x90)))))
        ) && ((-1 < operand->symx && (g_symtab[operand->symx].sclass == '\x04')))) {
      return;
    }
    type_class = operand->type & 0xf0;
    if (((((type_class == 0x60) || (type_class == 0x70)) &&
         ((operand->parent->op == IL_ASSIGN && (iVar1 = operand_index(operand), iVar1 == 2)))) &&
        (((type_class = operand->parent->type & 0xf0, type_class == 0x60 || (type_class == 0x70)) &&
         (-1 < operand->symx)))) && (g_symtab[operand->symx].sclass == '\x04')) {
      return;
    }
    symx = operand->symx;
    if (-1 < symx) {
      sclass = g_symtab[symx].sclass;
      if (('\0' < sclass) && (sclass < '\x05')) {
        if ((g_leaf_table[operand->nleaf].flag & 8) != 0) {
          return;
        }
        if ((g_options->cpu != 4) && ((operand->type & 0xf8) == 0x30)) {
          return;
        }
        if ((0 < symx) && ((g_symtab[symx].attr & 3) != 0)) {
          return;
        }
        goto LAB_004079e3;
      }
    }
    type_class = operand->type;
    if (((((((type_class & 0xe0) != 0) && (size_class = type_class & 0xf8, size_class != 0x40)) &&
          (size_class != 0x28)) && ((g_options->cpu != 4 || (size_class != 0x30)))) &&
        ((type_class = type_class & 0xf0, type_class != 0x60 &&
         ((type_class != 0x70 && (size_class != 0x48)))))) &&
       ((type_class != 0x80 && (type_class != 0x90)))) {
      return;
    }
    if ((g_leaf_table[operand->nleaf].flag & 0xe) != 0) {
      return;
    }
  }
  else {
    if (operand->op != IL_CONST) {
      return;
    }
    type_class = operand->type & 0xe0;
    if (((type_class != 0) && (size_class = operand->type & 0xf8, size_class != 0x40)) &&
       ((g_options->cpu != 4 || (type_class != 0x20)))) {
      if (g_options->cpu != 2) {
        return;
      }
      if (g_options->fpu_mode != '\x03') {
        return;
      }
      if (size_class != 0x28) {
        return;
      }
    }
    if ((operand->flag & 0x200) != 0) {
      return;
    }
    value = operand->val;
    iVar1 = operand_index(operand);
    iVar1 = ARGCONST_FIT(4,operand->parent,iVar1,value,0);
    if (iVar1 != 0) {
      return;
    }
    call = operand->parent->parent;
    if ((((call->op == IL_CALL) && (call = call->child, call->op == IL_ID)) &&
        (symx = call->symx, -1 < symx)) &&
       (iVar1 = is_builtin_name(g_symtab[symx].name), iVar1 != 0)) {
      return;
    }
    if ((operand->flag & 0x200) == 0) {
      do {
        if ((operand->op == IL_ADD) &&
           ((type_class = operand->type & 0xf0, type_class == 0x80 || (type_class == 0x90)))) {
          iVar1 = subtree_has_symbol_attr_2e(operand);
          if (iVar1 != 0) {
            return;
          }
          break;
        }
        operand = operand->parent;
      } while ((operand->flag & 0x200) == 0);
    }
  }
LAB_004079e3:
  cell = regalloc_alloc(8);
  cell->node = node;
  cell->next = g_regalloc_block->statics;
  g_regalloc_block->statics = cell;
  return;
}



