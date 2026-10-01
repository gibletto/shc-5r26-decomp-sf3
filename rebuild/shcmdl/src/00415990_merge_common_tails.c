#include "decls.h"
#include "imports.h"

// entry: 00415990
// name : merge_common_tails
// size : 412
// sig  : void merge_common_tails(void)


int __cdecl merge_common_tails(void)

{
  il_node *stmt;
  short label;
  char not_ctrl;
  uint labno;
  il_node *new_stmt;
  undefined3 extraout_var = 0;
  undefined3 extraout_var_00 = 0;
  undefined3 extraout_var_01 = 0;
  undefined3 extraout_var_02 = 0;
  undefined3 extraout_var_03 = 0;
  undefined3 extraout_var_04 = 0;
  undefined4 *bucket;
  int other;
  il_op parent_op;
  undefined4 *tail;
  il_node *target;
  
  bucket = &g_common_tail_buckets;
  do {
    for (tail = (undefined4 *)*bucket; tail != (undefined4 *)0x0; tail = (undefined4 *)*tail) {
      labno = new_symbol(0,'\v');
      label = (short)labno;
      target = (il_node *)tail[3];
      if ((*(byte *)((int)tail + 0x16) & 1) != 0) {
        new_stmt = new_glabel_stmt(label);
        not_ctrl = is_not_control_condition(target);
        if (CONCAT31(extraout_var,not_ctrl) == 0) {
          not_ctrl = is_not_control_condition(target->parent);
          if ((CONCAT31(extraout_var_00,not_ctrl) != 0) && (target->parent->parent->op != IL_BLOCK))
          {
            wrap_in_block_pair(target->parent);
          }
          target = target->parent;
        }
        else if (target->parent->op != IL_BLOCK) {
          wrap_in_block_pair(target);
        }
        insert_before(target,new_stmt);
      }
      for (other = tail[1]; other != 0; other = *(int *)(other + 4)) {
        target = *(il_node **)(other + 0xc);
        if ((*(byte *)(other + 0x16) & 1) == 0) {
          if ((*(byte *)(other + 0x16) & 2) != 0) {
            new_stmt = make_goto_entry_label();
            new_stmt->symx = label;
            not_ctrl = is_not_control_condition(target);
            if (CONCAT31(extraout_var_03,not_ctrl) == 0) {
              not_ctrl = is_not_control_condition(target->parent);
              if (CONCAT31(extraout_var_04,not_ctrl) != 0) {
                stmt = target->parent;
                parent_op = stmt->parent->op;
                goto joined_r0x00415ad5;
              }
              goto LAB_00415ae0;
            }
            if (target->parent->op != IL_BLOCK) {
              wrap_in_block_pair(target);
            }
            goto LAB_00415ae5;
          }
        }
        else {
          new_stmt = new_glabel_stmt(label);
          not_ctrl = is_not_control_condition(target);
          if (CONCAT31(extraout_var_01,not_ctrl) == 0) {
            not_ctrl = is_not_control_condition(target->parent);
            if (CONCAT31(extraout_var_02,not_ctrl) != 0) {
              stmt = target->parent;
              parent_op = stmt->parent->op;
joined_r0x00415ad5:
              if (parent_op != IL_BLOCK) {
                wrap_in_block_pair(stmt);
              }
            }
LAB_00415ae0:
            target = target->parent;
          }
          else if (target->parent->op != IL_BLOCK) {
            wrap_in_block_pair(target);
          }
LAB_00415ae5:
          insert_before(target,new_stmt);
        }
        g_code_merged = '\x01';
      }
    }
    bucket = bucket + 1;
    if ((undefined4 *)SD(0x0044004f) < bucket) {
      return;
    }
  } while( true );
}



