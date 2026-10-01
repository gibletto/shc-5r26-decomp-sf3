#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_cur_loop
#define g_cur_loop (*(loop * *)(g_sd + 0x26ac8))


// entry: 00412460
// name : step_def_unusable
// size : 245
// sig  : int step_def_unusable(il_node * def)


int __cdecl step_def_unusable(il_node *def)

{
  il_node *piVar1;
  il_node *var;
  node_list *link;
  short blkno;
  
  piVar1 = get_increment_target(def);
  if (piVar1 == (il_node *)0x0) {
    return 1;
  }
  var = def->child;
  if (def->op == IL_ASSIGN) {
    var = var->next;
    if (var->op == IL_ADD) {
      var = var->child;
      if (piVar1->nleaf != var->nleaf) {
        var = var->next;
      }
    }
    else {
      if (var->op != IL_SUB) {
        return 1;
      }
      var = var->child;
    }
  }
  piVar1 = var->cmnexp;
  if (((piVar1 != (il_node *)0x0) && (piVar1->duptr != (dutbl *)0x0)) &&
     ((piVar1 == (il_node *)0x0 ||
      ((piVar1->duptr == (dutbl *)0x0 || (piVar1->duptr->links != (node_list *)0x0)))))) {
    link = piVar1->duptr->links;
    if (link != (node_list *)0x0) {
      do {
        piVar1 = link->node;
        blkno = piVar1->duptr->block->number;
        if (((((g_cur_loop->start->number <= blkno) && (blkno <= g_cur_loop->exit->number)) &&
             ((piVar1->flag & 0x1000) == 0)) &&
            (((piVar1->op & IL_NON_F8) == IL_PRI || ((piVar1->op & IL_NON_F0) == IL_A_ADD)))) &&
           (piVar1 != def)) {
          return 1;
        }
        link = link->next;
      } while (link != (node_list *)0x0);
    }
    return 0;
  }
  return 1;
}



