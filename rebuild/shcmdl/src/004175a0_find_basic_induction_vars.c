#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_loop_test
#define g_loop_test (*(il_node * *)(g_sd + 0x26854))


// entry: 004175a0
// name : find_basic_induction_vars
// size : 967
// sig  : void find_basic_induction_vars(bblock * block)


int __cdecl find_basic_induction_vars(bblock *block)

{
  il_node *def;
  byte kind;
  uint value;
  int sole;
  il_node *piVar1;
  int iVar2;
  il_node *piVar3;
  il_node *piVar4;
  il_node *rhs;
  byte *flag_byte;
  node_list *stmt;
  
  stmt = block->ilnode;
  do {
    if ((stmt == (node_list *)0x0) || (3 < g_iv_count)) {
      return;
    }
    def = stmt->node;
    piVar3 = def->child;
    if ((piVar3 != (il_node *)0x0) && (piVar3->next != (il_node *)0x0)) {
      rhs = piVar3->next;
    }
    kind = def->type & 0xf8;
    if ((kind != 0x28) && (kind != 0x30)) {
      switch(def->op) {
      case IL_PRI:
      case IL_PRD:
        if ((((def->cmnexp != (il_node *)0x0) && (def->cmnexp->duptr != (dutbl *)0x0)) &&
            ((def->flag & 0x5000) == 0)) &&
           (sole = is_sole_def_in_loop(piVar3->cmnexp->duptr,def), iVar2 = g_iv_count, sole != 0)) {
          g_iv_table[g_iv_count].update = def;
          g_iv_table[iVar2].block = block;
          flag_byte = (byte *)((int)&(g_iv_table[iVar2].update)->flag + 1);
          *flag_byte = *flag_byte | 0x40;
          value = 1;
          if ((def->type & 0xf8) == 0x40) {
            value = def->val;
          }
          if (def->op == IL_PRI) {
            piVar3 = new_const_node('\x1c',value);
          }
          else {
            piVar3 = new_const_node('\x1c',value);
            piVar3 = make_node(IL_MINUS,piVar3->type,piVar3,(il_node *)0x0,(il_node *)0x0);
          }
          g_iv_table[g_iv_count].step = piVar3;
          mark_induction_variable(def);
          clear_induction_marks(def);
LAB_0041794c:
          clear_induction_marks(g_loop_test);
        }
        break;
      case IL_A_ADD:
      case IL_A_SUB:
        if ((((def->cmnexp != (il_node *)0x0) && (def->cmnexp->duptr != (dutbl *)0x0)) &&
            (rhs->invno != '\0')) &&
           (((def->flag & 0x5000) == 0 &&
            (sole = is_sole_def_in_loop(piVar3->cmnexp->duptr,def), iVar2 = g_iv_count, sole != 0)))
           ) {
          g_iv_table[g_iv_count].update = def;
          g_iv_table[iVar2].block = block;
          flag_byte = (byte *)((int)&(g_iv_table[iVar2].update)->flag + 1);
          *flag_byte = *flag_byte | 0x40;
          if (def->op == IL_A_ADD) {
            piVar3 = copy_tree(0,rhs);
          }
          else {
            piVar3 = copy_tree(0,rhs);
            piVar3 = make_node(IL_MINUS,piVar3->type,piVar3,(il_node *)0x0,(il_node *)0x0);
          }
          g_iv_table[g_iv_count].step = piVar3;
          piVar3 = g_iv_table[g_iv_count].step;
          piVar4 = piVar3;
          if (piVar3->op == IL_MINUS) {
            piVar4 = piVar3->child;
          }
          if (((piVar4->type & 0xf8) == 0) && ((piVar4->type & 4) != 0)) {
            piVar3->type = '\0';
            piVar4->type = '\0';
          }
          if (((piVar4->type & 0xf8) == 8) && ((piVar4->type & 4) != 0)) {
            (g_iv_table[g_iv_count].step)->type = '\b';
            piVar4->type = '\b';
          }
          mark_induction_variable(def);
          clear_induction_marks(def);
          goto LAB_0041794c;
        }
        break;
      case IL_ASSIGN:
        piVar4 = (il_node *)0x0;
        if (((rhs->op == IL_ADD) || (rhs->op == IL_SUB)) &&
           ((piVar1 = rhs->child, piVar1->op == IL_ID ||
            (piVar1 = piVar1->next, piVar1->op == IL_ID)))) {
          piVar4 = piVar1;
        }
        if (((((def->cmnexp != (il_node *)0x0) && (def->cmnexp->duptr != (dutbl *)0x0)) &&
             (piVar4 != (il_node *)0x0)) &&
            ((piVar3->nleaf == piVar4->nleaf && ((def->flag & 0x5000) == 0)))) &&
           (iVar2 = is_sole_def_in_loop(piVar4->cmnexp->duptr,def), iVar2 != 0)) {
          if (rhs->op == IL_ADD) {
            piVar3 = rhs->child;
            if (piVar3->invno == '\0') {
              if (piVar3->next->invno == '\0') goto LAB_00417882;
              if (piVar3->invno == '\0') {
                piVar3 = piVar3->next;
              }
            }
            piVar3 = copy_tree(0,piVar3);
LAB_004178b1:
            g_iv_table[g_iv_count].step = piVar3;
          }
          else {
LAB_00417882:
            if ((rhs->op == IL_SUB) && (piVar3 = rhs->child->next, piVar3->invno != '\0')) {
              piVar3 = copy_tree(0,piVar3);
              piVar3 = make_node(IL_MINUS,piVar3->type,piVar3,(il_node *)0x0,(il_node *)0x0);
              goto LAB_004178b1;
            }
          }
          piVar3 = g_iv_table[g_iv_count].step;
          if (piVar3 != (il_node *)0x0) {
            piVar4 = piVar3;
            if (piVar3->op == IL_MINUS) {
              piVar4 = piVar3->child;
            }
            if (((piVar4->type & 0xf8) == 0) && ((piVar4->type & 4) != 0)) {
              piVar3->type = '\0';
              piVar4->type = '\0';
            }
            if (((piVar4->type & 0xf8) == 8) && ((piVar4->type & 4) != 0)) {
              (g_iv_table[g_iv_count].step)->type = '\b';
              piVar4->type = '\b';
            }
          }
          iVar2 = g_iv_count;
          g_iv_table[g_iv_count].update = def;
          g_iv_table[iVar2].block = block;
          flag_byte = (byte *)((int)&(g_iv_table[iVar2].update)->flag + 1);
          *flag_byte = *flag_byte | 0x40;
          mark_induction_variable(def);
          clear_induction_marks(def);
          goto LAB_0041794c;
        }
      }
    }
    stmt = stmt->next;
  } while( true );
}



