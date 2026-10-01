#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_iv_update_stmt
#define g_iv_update_stmt (*(il_node * *)(g_sd + 0x26ac4))


// entry: 004189c0
// name : insert_induction_increment
// size : 216
// sig  : void insert_induction_increment(il_node * temp_assign, il_node * incr, iv_entry * entry)


int __cdecl insert_induction_increment(il_node *temp_assign,il_node *incr,iv_entry *entry)

{
  uchar type;
  il_node *incr_assign;
  il_node *piVar1;
  il_node *op2;
  il_node *op3;
  node_list *item;
  
  incr_assign = copy_tree(0,temp_assign);
  *(byte *)&incr_assign->flag = (byte)incr_assign->flag | 0xf0;
  piVar1 = copy_tree(1,incr_assign->child);
  free_tree(incr_assign->child->next);
  type = piVar1->type;
  op3 = (il_node *)0x0;
  op2 = make_node(IL_CAST,type,incr,(il_node *)0x0,(il_node *)0x0);
  piVar1 = make_node(IL_ADD,type,piVar1,op2,op3);
  piVar1->parent = incr_assign;
  incr_assign->child->next = piVar1;
  item = entry->block->ilnode;
  do {
    piVar1 = incr_assign;
    if (item == (node_list *)0x0) {
LAB_00418a8a:
      g_iv_update_stmt = piVar1;
      *(byte *)&piVar1->flag = (byte)piVar1->flag | 0xf0;
      return;
    }
    if (item->node == g_iv_update_stmt) {
      piVar1 = copy_tree(1,g_iv_update_stmt);
      piVar1->op = IL_COMMA;
      replace_node(g_iv_update_stmt,piVar1);
      piVar1->child = g_iv_update_stmt;
      g_iv_update_stmt->parent = piVar1;
      g_iv_update_stmt->next = incr_assign;
      incr_assign->parent = piVar1;
      item->node = piVar1;
      goto LAB_00418a8a;
    }
    item = item->next;
  } while( true );
}



