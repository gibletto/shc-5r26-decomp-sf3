#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_cur_loop
#define g_cur_loop (*(loop * *)(g_sd + 0x26ac8))
#undef g_debug_flags
#define g_debug_flags (*(unsigned char *)(g_sd + 0x267c0))
#undef g_iv_update_stmt
#define g_iv_update_stmt (*(il_node * *)(g_sd + 0x26ac4))
#undef g_loop_test
#define g_loop_test (*(il_node * *)(g_sd + 0x26854))


// entry: 00418040
// name : reduce_induction_variable
// size : 1156
// sig  : void reduce_induction_variable(iv_entry * entry)


int __cdecl reduce_induction_variable(iv_entry *entry)

{
  unsigned char _frec_21[33];
#define penalty (*(char *)(_frec_21 + 0))
#define temp_assign (*(il_node * *)(_frec_21 + 1))
#define temp (*(il_node * *)(_frec_21 + 9))
#define use_size (*(uint *)(_frec_21 + 13))
#define test_use (*(iv_use * *)(_frec_21 + 17))
#define test_size (*(int *)(_frec_21 + 21))
#define test_assign (*(il_node * *)(_frec_21 + 29))
  iv_use *use;
  il_node *node;
  char cond;
  int iVar1;
  il_node *ref_root;
  node_list *item;
  bblock *test_blk;
  il_node *piVar2;
  byte ty;
  il_node *piVar3;
  byte *flag_byte;
  short iv_leaf;
  node_list *next_item;
  il_node **parent_link;
  block_list *pred;
  short use_blkno;
  
  g_iv_update_stmt = entry->update;
  test_use = (iv_use *)0x0;
  iv_leaf = g_iv_update_stmt->nleaf;
  ty = g_loop_test->child->type;
  if ((ty & 0x40) == 0) {
    test_size = (int)(char)((ty & 0x1c) >> 2);
  }
  else {
    test_size = 8;
  }
  g_single_iv_use = entry->uses->next == (iv_use *)0x0;
  use = entry->uses;
  do {
    if ((use == (iv_use *)0x0) || (2 < g_iv_reduced_count)) {
      if ((test_use != (iv_use *)0x0) &&
         ((((g_loop_test != (il_node *)0x0 && (use == (iv_use *)0x0)) &&
           (g_loop_test->child->nleaf == iv_leaf)) &&
          ((g_iv_reduced_count < 4 && (g_test_replace_ok != 0)))))) {
        g_loop_test->op = g_loop_test->op + (char)test_use->test_adjust;
        if (use_size != 8) {
          set_loop_step(test_use->incr);
        }
        replace_loop_test(test_assign,test_use);
        clear_induction_numbers(temp_assign);
      }
      return;
    }
    node = use->expr;
    ty = node->type;
    if (((ty & 0xe0) == 0x80) || ((ty & 0xf8) == 0x40)) {
      use_size = 8;
      ty = 0x40;
    }
    else {
      use_size = ((int)(char)ty & 0x1cU) >> 2;
    }
    parent_link = &node->parent;
    penalty = '\0';
    if ((((*parent_link)->op == IL_ASSIGN) && (piVar3 = (*parent_link)->child, piVar3->op == IL_ID))
       && (piVar3->symx < 0)) {
      temp = copy_tree(1,piVar3);
      iVar1 = induction_step(g_iv_update_stmt);
      if (iVar1 != -1) {
        if (iVar1 == 1) {
          piVar3 = (*parent_link)->refchn;
          if ((piVar3 == (il_node *)0x0) ||
             (piVar2 = piVar3->refchn, piVar3->refchn == (il_node *)0x0)) {
            piVar2 = *parent_link;
          }
          if (piVar3 != (il_node *)0x0) {
            piVar2 = expression_root(piVar2);
            ref_root = expression_root(piVar3);
            if (piVar2 != ref_root) goto LAB_00418197;
          }
          penalty = '\x01';
        }
        else {
          penalty = '\x01';
        }
        goto LAB_00418195;
      }
      piVar3 = (*parent_link)->child;
    }
    else {
      temp = new_temp_id(ty);
LAB_00418195:
      piVar3 = (il_node *)0x0;
    }
LAB_00418197:
    if ((char)(*parent_link)->op < ' ') {
      for (item = use->block->ilnode; item != (node_list *)0x0; item = item->next) {
        if (item->node == node) {
          temp->filn = item->node->filn;
          temp->line = item->node->line;
          temp->listno = item->node->listno;
          item->node = temp;
          break;
        }
      }
    }
    item = g_cur_loop->exit->ilnode;
    if (item == (node_list *)0x0) {
LAB_0041821a:
      penalty = penalty + '\x01';
    }
    else {
      do {
        next_item = item->next;
        if (next_item == (node_list *)0x0) break;
        item = next_item;
      } while (next_item != (node_list *)0x0);
      if (item == (node_list *)0x0) goto LAB_0041821a;
      penalty = penalty + ('\x01' - (item->node == g_iv_update_stmt));
    }
    cond = is_conditionally_evaluated(node);
    penalty = penalty + cond + ('\x01' - (use->test_adjust == 0));
    if ((g_cur_loop->flag & 1) == 0) {
      test_blk = g_cur_loop->exit;
    }
    else {
      test_blk = g_cur_loop->start;
    }
    if (((test_blk->prelst != (block_list *)0x0) &&
        (pred = test_blk->prelst->next, pred != (block_list *)0x0)) &&
       (pred->next != (block_list *)0x0)) {
      penalty = penalty + '\x01';
    }
    replace_node(node,temp);
    temp_assign = new_node(IL_ASSIGN,ty);
    temp_assign->filn = node->filn;
    temp_assign->line = node->line;
    temp_assign->listno = node->listno;
    if (piVar3 == (il_node *)0x0) {
      piVar3 = temp;
    }
    piVar2 = copy_tree(1,temp);
    temp_assign->child = piVar2;
    piVar2->parent = temp_assign;
    temp_assign->child->next = node;
    *parent_link = temp_assign;
    piVar2->next = node;
    insert_before(g_cur_loop->node,temp_assign);
    flag_byte = (byte *)((int)&temp_assign->flag + 1);
    *flag_byte = *flag_byte | 0x40;
    clear_induction_numbers(temp_assign);
    append_list_item(&g_cur_loop->pre->ilnode,temp_assign);
    if (((*(unsigned char *)((char *)&g_debug_flags + 2)) & 0x80) != 0) {
      dump_tree(temp_assign,0,s_loop_ind_1_asndp_00435b30);
    }
    build_induction_increment(use,entry->step);
    if (((*(unsigned char *)((char *)&g_debug_flags + 2)) & 0x80) != 0) {
      dump_tree(temp_assign,0,s_loop_ind_2_asndp_00435b1c);
    }
    use_blkno = use->block->number;
    if ((use_size == 8) && (penalty == '\0')) {
      if (entry->block->number != use_blkno) {
        iVar1 = use_blkno + -1;
        ty = (byte)(iVar1 >> 0x1f);
        if ((entry->block->domlst[(int)(iVar1 + (iVar1 >> 0x1f & 0x1fU)) >> 5] &
            1 << ((((byte)iVar1 ^ ty) - ty & 0x1f ^ ty) - ty & 0x1f)) == 0) goto LAB_004183c8;
      }
      iVar1 = try_auto_increment_access(node,piVar3,use);
      if (iVar1 != 0) goto LAB_004183c8;
      free_tree(use->incr);
      use->incr = (il_node *)0x0;
    }
    else {
LAB_004183c8:
      insert_induction_increment(temp_assign,use->incr,entry);
    }
    temp_assign->filn = 0;
    temp_assign->line = 0;
    temp_assign->listno = 0;
    clear_induction_numbers(temp_assign);
    if (((*(unsigned char *)((char *)&g_debug_flags + 2)) & 0x80) != 0) {
      dump_tree(temp_assign,0,s_loop_ind_3_asndp_00435b08);
    }
    if (((&g_iv_test_type_table)[test_size + use_size * 0xb] != '\0') &&
       ((use->expr->flag2 & 4) == 0)) {
      test_use = use;
      test_assign = temp_assign;
    }
    g_iv_reduced_count = g_iv_reduced_count + 1;
    use = use->next;
  } while( true );
#undef penalty
#undef temp_assign
#undef temp
#undef use_size
#undef test_use
#undef test_size
#undef test_assign
}



