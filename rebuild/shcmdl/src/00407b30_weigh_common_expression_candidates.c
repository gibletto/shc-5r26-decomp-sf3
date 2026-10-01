#include "decls.h"
#include "imports.h"
#include "argconst.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_f_chain
#define g_f_chain (*(bblock * *)(g_sd + 0x26ad0))
#undef g_options
#define g_options (*(option_record * *)(g_sd + 0x1e714))
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 00407b30
// name : weigh_common_expression_candidates
// size : 562
// sig  : void weigh_common_expression_candidates(void)


int __cdecl weigh_common_expression_candidates(void)

{
  bblock *block;
  il_node *node;
  int iVar1;
  lreg *reg;
  int weight;
  uint value;
  int priority;
  const_data **bucket;
  int nrefs;
  const_data *cdata;
  node_list *cell;
  loop *lp;
  const_data **next_bucket;
  loop *outer;
  il_op parent_op;
  short symx;
  const_use *use;
  
  for (block = g_f_chain; block != (bblock *)0x0; block = block->f_next) {
    for (cell = block->statics; cell != (node_list *)0x0; cell = cell->next) {
      hash_common_expression_candidate(block,cell->node);
    }
  }
  bucket = g_cmnexp_hash;
  do {
    for (cdata = *bucket; cdata != (const_data *)0x0; cdata = cdata->hash_next) {
      priority = 0;
      for (use = cdata->uses; use != (const_use *)0x0; use = use->next) {
        lp = use->block->lptbl;
        if (lp == (loop *)0x0) {
          iVar1 = count_enclosing_loops(use->node);
          if (iVar1 == 0) {
            weight = 1;
          }
          else {
            weight = iVar1 + 1;
            if (use->node->op == IL_CONST) {
              weight = iVar1 + 2;
            }
            weight = weight + 1;
          }
        }
        else {
          weight = 2;
          outer = lp->fath;
          while (outer != (loop *)0x0) {
            weight = weight + 1;
            lp = lp->fath;
            outer = lp->fath;
          }
          if (use->node->op == IL_CONST) {
            weight = weight + 1;
          }
          weight = weight + 1;
        }
        node = use->node;
        if (node->cmnexp == (il_node *)0x0) {
          nrefs = 1;
        }
        else {
          nrefs = 0;
          for (; node != (il_node *)0x0; node = node->refchn) {
            if (node->op == IL_CONST) {
              value = node->val;
              iVar1 = operand_index(node);
              iVar1 = ARGCONST_FIT(1,node->parent,iVar1,value,use);
              if ((iVar1 == 0) &&
                 ((node->op != IL_CONST ||
                  ((((node->parent == (il_node *)0x0 || (iVar1 = operand_index(node), iVar1 != 2))
                    || ((parent_op = node->parent->op, parent_op != IL_SL &&
                        (((parent_op != IL_SR && (parent_op != IL_A_SL)) && (parent_op != IL_A_SR)))
                        ))) &&
                   (((node->op != IL_CONST || (node->parent == (il_node *)0x0)) ||
                    ((iVar1 = operand_index(node), iVar1 != 2 ||
                     ((node->parent->op != IL_ASSIGN || (node->parent->child->op != IL_B_QUALIFY))))
                    )))))))) goto LAB_00407c7d;
            }
            else {
LAB_00407c7d:
              nrefs = nrefs + 1;
            }
          }
        }
        priority = priority + weight * nrefs;
      }
      if (1 < priority) {
        reg = new_register_candidate(cdata,0);
        if ((g_options->cpu == 4) &&
           ((*(byte *)(*(int *)(*(int *)((int)reg->chain + 8) + 8) + 3) & 0xf8) == 0x30)) {
          priority = priority / 2;
        }
        reg->priori = priority;
        iVar1 = *(int *)(*(int *)((int)reg->chain + 8) + 8);
        if ((((*(byte *)(iVar1 + 3) & 0xf8) == 0x48) && (symx = *(short *)(iVar1 + 4), symx != 0))
           && (g_symtab[symx].sclass == '\x01')) {
          reg->priori = priority + 1;
        }
      }
    }
    next_bucket = bucket + 1;
    *bucket = (const_data *)0x0;
    bucket = next_bucket;
    if ((const_data **)((int)g_cmnexp_hash + 0x1ff) < next_bucket) {
      return;
    }
  } while( true );
}



