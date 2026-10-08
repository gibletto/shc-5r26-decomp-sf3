#include "decls.h"
#include "imports.h"
#include "argconst.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_cur_loop
#define g_cur_loop (*(loop * *)(g_sd + 0x26ac8))
#undef g_loop_tree
#define g_loop_tree (*(loop * *)(g_sd + 0x267f0))
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 004110c0
// name : hoist_invariants_in_tree
// size : 872
// sig  : void hoist_invariants_in_tree(il_node * node)


int __cdecl hoist_invariants_in_tree(il_node *node)

{
  byte ty;
  char inv;
  ushort lpno;
  il_node *temp;
  il_node *assign;
  loop *lp;
  short def_blkno;
  node_list *link;
  il_op op;
  loop *outer;
  char rhs_inv;
  il_node *sub;
  
  for (sub = node->child; sub != (il_node *)0x0; sub = sub->next) {
    hoist_invariants_in_tree(sub);
  }
  switch(node->op) {
  case IL_CAST:
  case IL_PLUS:
  case IL_MINUS:
  case IL_AMPER:
  case IL_NOT:
  case IL_CMPL:
    goto switchD_004110f2_caseD_20;
  default:
    goto switchD_004110f2_caseD_21;
  case IL_ASTER:
    ty = node->type & 0xf0;
    if (((ty != 0x80) && (ty != 0x90)) && ((IV_LICM_PASS(2) != 0 || ((ty != 0x60 && (ty != 0x70)))))) {
      op = node->parent->op;
      if (((('/' < (char)op) && ((char)op < '>')) || (('O' < (char)op && ((char)op < '`')))) &&
         ((node->type & 0xf8) == 0x40)) {
        g_cur_loop->flag = g_cur_loop->flag | 0x2000;
      }
      node->invno = '\0';
      goto LAB_00411315;
    }
    goto switchD_004110f2_caseD_20;
  case IL_CALL:
    g_cur_loop->flag = g_cur_loop->flag | 0x2000;
    goto switchD_004110f2_caseD_21;
  case IL_QUALIFY:
  case IL_B_QUALIFY:
    if ((IV_LICM_PASS(1) != 0) ||
       ((((node->type & 0xf8) != 0x40 && (ty = node->type & 0xf0, ty != 0x80)) && (ty != 0x90)))) {
      node->invno = '\0';
      goto LAB_00411315;
    }
switchD_004110f2_caseD_20:
    inv = node->child->invno;
    break;
  case IL_ADD:
  case IL_SUB:
  case IL_MUL:
  case IL_DIV:
  case IL_MOD:
  case IL_SL:
  case IL_SR:
  case IL_B_AND:
  case IL_B_XOR:
  case IL_B_OR:
    inv = node->child->invno;
    rhs_inv = node->child->next->invno;
    if (rhs_inv < inv) {
      node->invno = rhs_inv;
      goto LAB_00411315;
    }
    break;
  case IL_ID:
    if ((node->duptr != (dutbl *)0x0) && (node->invno == '\0')) {
      for (link = node->duptr->links; link != (node_list *)0x0; link = link->next) {
        def_blkno = link->node->duptr->block->number;
        if ((g_cur_loop->start->number <= def_blkno) &&
           (link->node->cmnexp->duptr->block->number <= g_cur_loop->exit->number)) {
          node->invno = '\0';
          break;
        }
        lp = g_cur_loop;
        if (g_cur_loop != (loop *)0x0) {
          while (outer = lp->fath, outer != (loop *)0x0) {
            if (((outer->start->number <= def_blkno) && (def_blkno <= outer->exit->number)) ||
               (lp = outer, outer == (loop *)0x0)) break;
          }
        }
        if (node->invno == '\0') {
          lpno = (ushort)(byte)lp->lpnumber;
LAB_00411257:
          node->invno = (char)lpno;
        }
        else {
          lpno = lp->lpnumber;
          if ((short)lpno < (short)node->invno) goto LAB_00411257;
        }
      }
      for (sub = node->refchn; sub != (il_node *)0x0; sub = sub->refchn) {
        sub->invno = node->invno;
      }
      goto LAB_00411315;
    }
    ty = node->type & 0xf0;
    lp = g_cur_loop;
    if ((ty != 0x80) && (ty != 0x90)) {
      if (((0 < node->symx) && (g_symtab[node->symx].sclass < '\x05')) &&
         (((op = node->parent->op, '/' < (char)op && ((char)op < '>')) ||
          (('O' < (char)op && ((char)op < '`')))))) {
        g_cur_loop->flag = g_cur_loop->flag | 0x2000;
      }
      goto LAB_00411315;
    }
    do {
      outer = lp;
      if (outer == (loop *)0x0) break;
      lp = outer->fath;
    } while (outer->fath != (loop *)0x0);
    inv = (char)outer->brc;
    break;
  case IL_CONST:
    lp = g_cur_loop;
    do {
      outer = lp;
      if (outer == (loop *)0x0) break;
      lp = outer->fath;
    } while (outer->fath != (loop *)0x0);
    inv = (char)outer->brc;
  }
  node->invno = inv;
LAB_00411315:
  if ((((g_licm_pass & 1) != 0) && (node->invno == '\0')) && (g_cur_loop->repet != 1)) {
    for (sub = node->child; sub != (il_node *)0x0; sub = sub->next) {
      if ((((sub->invno != '\0') && (op = sub->op, op != IL_ID)) && (op != IL_CONST)) &&
         ((((op != IL_CAST || ((op = sub->child->op, op != IL_ID && (op != IL_CONST)))) &&
           (ty = sub->type, (ty & 0xf8) != 0x30)) && (g_cur_loop->lpnumber <= (short)sub->invno))))
      {
        if (((ty & 0xf0) == 0x80) || ((ty & 0xf0) == 0x90)) {
          ty = 0x40;
        }
        temp = new_temp_id(ty);
        temp->filn = sub->filn;
        temp->line = sub->line;
        temp->listno = sub->listno;
        replace_node(sub,temp);
        assign = new_node(IL_ASSIGN,ty);
        temp = copy_tree(1,temp);
        assign->child = temp;
        temp->parent = assign;
        assign->child->next = sub;
        sub->parent = assign;
        temp->next = sub;
        insert_in_loop_preheader(g_loop_tree,sub,assign);
      }
    }
  }
  return;
switchD_004110f2_caseD_21:
  node->invno = '\0';
  goto LAB_00411315;
}



