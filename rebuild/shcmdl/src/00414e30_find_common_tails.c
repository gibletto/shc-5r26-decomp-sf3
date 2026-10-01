#include "decls.h"
#include "imports.h"

// entry: 00414e30
// name : find_common_tails
// size : 238
// sig  : void find_common_tails(void)


int __cdecl find_common_tails(void)

{
  il_node *node;
  int iVar1;
  il_node *other_stmt;
  int opno;
  uchar *bucket;
  undefined4 *group;
  undefined4 *member;
  
  g_merge_id = 0;
  bucket = (uchar *)&g_successor_groups;
  do {
    for (group = *(undefined4 **)bucket; member = group, group != (undefined4 *)0x0;
        group = (undefined4 *)*group) {
      for (; member != (undefined4 *)0x0; member = (undefined4 *)member[1]) {
        node = last_statement_of_list(*(node_list **)(member[2] + 4));
        if ((node->parent->op != IL_FOR) || (iVar1 = operand_index(node), iVar1 != 3)) {
          for (iVar1 = member[1]; iVar1 != 0; iVar1 = *(int *)(iVar1 + 4)) {
            other_stmt = last_statement_of_list(*(node_list **)(*(int *)(iVar1 + 8) + 4));
            if ((((other_stmt->parent->op != IL_FOR) ||
                 (opno = operand_index(other_stmt), opno != 3)) &&
                (g_merge_match_depth = 0, node != (il_node *)0x0)) && (other_stmt != (il_node *)0x0)
               ) {
              match_statement_tails(node,other_stmt,(bblock *)member[2],*(bblock **)(iVar1 + 8));
            }
          }
        }
      }
    }
    bucket = bucket + 4;
  } while (bucket < &g_merge_whole_blocks);
  return;
}



