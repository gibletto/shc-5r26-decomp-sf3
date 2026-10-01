#include "decls.h"
#include "imports.h"

// entry: 00415830
// name : merge_identical_blocks
// size : 339
// sig  : void merge_identical_blocks(void)


int __cdecl merge_identical_blocks(void)

{
  char not_ctrl;
  uint labno;
  il_node *label_stmt;
  il_node *goto_stmt;
  undefined3 extraout_var = 0;
  undefined3 extraout_var_00 = 0;
  undefined4 *first_item;
  il_node *target_stmt;
  il_node *stmt;
  undefined4 *bucket;
  short *blk_a;
  short *blk_b;
  undefined4 *group;
  undefined4 *pair;
  
  bucket = &g_identical_block_buckets;
  do {
    for (group = (undefined4 *)*bucket; pair = group, group != (undefined4 *)0x0;
        group = (undefined4 *)*group) {
      for (; pair != (undefined4 *)0x0; pair = (undefined4 *)pair[1]) {
        blk_a = (short *)pair[2];
        blk_b = (short *)pair[3];
        if (*blk_b < *blk_a) {
          first_item = *(undefined4 **)(blk_b + 2);
          target_stmt = (il_node *)**(undefined4 **)(blk_a + 2);
        }
        else {
          first_item = *(undefined4 **)(blk_a + 2);
          target_stmt = (il_node *)**(undefined4 **)(blk_b + 2);
        }
        stmt = (il_node *)*first_item;
        labno = new_symbol(0,'\v');
        label_stmt = new_glabel_stmt((short)labno);
        goto_stmt = make_goto_entry_label();
        goto_stmt->symx = (short)labno;
        not_ctrl = is_not_control_condition(target_stmt);
        if (CONCAT31(extraout_var,not_ctrl) == 0) {
          not_ctrl = is_not_control_condition(target_stmt->parent);
          if (CONCAT31(extraout_var_00,not_ctrl) != 0) {
            if (target_stmt->parent->parent->op != IL_BLOCK) {
              wrap_in_block_pair(target_stmt->parent);
            }
            if (stmt->parent->parent->op != IL_BLOCK) {
              wrap_in_block_pair(stmt->parent);
            }
          }
          insert_before(target_stmt->parent,label_stmt);
          stmt = stmt->parent;
        }
        else {
          if (target_stmt->parent->op != IL_BLOCK) {
            wrap_in_block_pair(target_stmt);
          }
          insert_before(target_stmt,label_stmt);
          if (stmt->parent->op != IL_BLOCK) {
            wrap_in_block_pair(stmt);
          }
        }
        insert_before(stmt,goto_stmt);
        g_code_merged = '\x01';
      }
    }
    bucket = bucket + 1;
  } while (bucket < &g_successor_groups);
  return;
}



