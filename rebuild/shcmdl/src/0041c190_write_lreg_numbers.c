#include "decls.h"
#include "imports.h"
#include "argconst.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 0041c190
// name : write_lreg_numbers
// size : 851
// sig  : void write_lreg_numbers(void)


int __cdecl write_lreg_numbers(void)

{
  il_node *piVar1;
  const_use *item;
  ushort pp;
  ushort ref_pp;
  undefined2 extraout_var = 0;
  undefined2 extraout_var_00 = 0;
  int iVar2;
  uint uVar3;
  il_node *other;
  lreg **slot;
  short lregno;
  int next_lregno;
  int index;
  short *chain;
  lreg *lr;
  il_op parent_op;
  void *ref;
  
  next_lregno = 1;
  index = 1;
  if (0 < g_lreg_count) {
    slot = g_lreg_table;
    do {
      slot = slot + 1;
      lr = *slot;
      lregno = (short)next_lregno;
      if (lr->set == 1) {
        if (lr->pregno != 0) {
          for (ref = lr->chain; ref != (void *)0x0; ref = *(void **)((int)ref + 8)) {
            for (piVar1 = *(il_node **)((int)ref + 0x10); piVar1 != (il_node *)0x0;
                piVar1 = piVar1->refchn) {
              if (piVar1->op == IL_ID) {
                if (((piVar1->flag & 0x100) != 0) && ((*slot)->bind == (lreg *)0x0)) {
                  piVar1->lreg = -lregno;
                  pp = statement_pp(piVar1);
                  other = piVar1->cmnexp;
                  if (other != (il_node *)0x0) {
                    do {
                      if ((other != piVar1) &&
                         (ref_pp = statement_pp(other),
                         CONCAT22(extraout_var_00,ref_pp) == CONCAT22(extraout_var,pp))) {
                        piVar1->lreg = lregno;
                        break;
                      }
                      other = other->refchn;
                    } while (other != (il_node *)0x0);
                    if (other != (il_node *)0x0) goto LAB_0041c263;
                  }
                  iVar2 = lreg_ref_in_statement(piVar1,CONCAT22(extraout_var,pp),*slot);
                  if (iVar2 == 0) goto LAB_0041c263;
                }
                piVar1->lreg = lregno;
              }
              else {
                piVar1->child->lreg = lregno;
              }
LAB_0041c263: ;
            }
          }
          if (0 < (*slot)->pregno) {
            mark_block_register_use(*slot);
          }
          (*slot)->lregno = lregno;
LAB_0041c4bd:
          next_lregno = next_lregno + 1;
        }
      }
      else if ((lr->set != 3) && (lr->pregno != 0)) {
        lr->lregno = lregno;
        if ((0 < (*slot)->pregno) && ((*slot)->set == 0)) {
          materialize_constant_lreg(index,lregno);
        }
        for (item = *(const_use **)((int)(*slot)->chain + 8); item != (const_use *)0x0;
            item = item->next) {
          for (piVar1 = item->node; piVar1 != (il_node *)0x0; piVar1 = piVar1->refchn) {
            if (piVar1->op == IL_CONST) {
              uVar3 = piVar1->val;
              iVar2 = operand_index(piVar1);
              iVar2 = ARGCONST_FIT(2,piVar1->parent,iVar2,uVar3,item);
              if ((iVar2 == 0) &&
                 ((piVar1->op != IL_CONST ||
                  ((((piVar1->parent == (il_node *)0x0 ||
                     (iVar2 = operand_index(piVar1), iVar2 != 2)) ||
                    ((parent_op = piVar1->parent->op, parent_op != IL_SL &&
                     (((parent_op != IL_SR && (parent_op != IL_A_SL)) && (parent_op != IL_A_SR))))))
                   && (((piVar1->op != IL_CONST || (piVar1->parent == (il_node *)0x0)) ||
                       ((iVar2 = operand_index(piVar1), iVar2 != 2 ||
                        ((piVar1->parent->op != IL_ASSIGN ||
                         (piVar1->parent->child->op != IL_B_QUALIFY)))))))))))) goto LAB_0041c387;
            }
            else {
LAB_0041c387:
              lr = *slot;
              chain = lr->chain;
              if ((*chain == 4) && ((piVar1->op != IL_ID && (piVar1->op != IL_CONST)))) {
                other = piVar1->child;
                if (other->op == IL_ASTER) {
                  if ((lr->set == 0) && (chain[1] != 0)) {
                    set_node_lreg_number(lregno,item,piVar1,other->child);
                  }
                  else {
                    other->child->lreg = lregno;
                  }
                }
                else if ((lr->set == 0) && (chain[1] != 0)) {
                  set_node_lreg_number(lregno,item,piVar1,other);
                }
                else {
                  other->lreg = lregno;
                }
              }
              else if ((piVar1->op == IL_ID) || (piVar1->op == IL_CONST)) {
                if ((0 < piVar1->symx) &&
                   (((g_symtab[piVar1->symx].sclass == '\a' ||
                     (g_symtab[piVar1->symx].sclass == '\b')) && (item->block->number == 1)))) {
                  iVar2 = operand_index(piVar1);
                  if (iVar2 == 2) goto LAB_0041c496;
                  if (**(int **)((int)(*slot)->chain + 8) == 0) {
                    piVar1->parent->child->next->lreg = lregno;
                    uVar3 = parameter_register_index(piVar1);
                    (*slot)->pregno = (short)uVar3;
                  }
                }
                if (((*slot)->set == 0) && (*(short *)((int)(*slot)->chain + 2) != 0)) {
                  set_node_lreg_number(lregno,item,piVar1,piVar1);
                }
                else {
                  piVar1->lreg = lregno;
                }
              }
            }
LAB_0041c496: ;
          }
        }
        if (0 < (*slot)->pregno) {
          mark_block_register_use(*slot);
        }
        goto LAB_0041c4bd;
      }
      index = index + 1;
    } while (index <= g_lreg_count);
  }
  g_next_lregno = next_lregno;
  return;
}



