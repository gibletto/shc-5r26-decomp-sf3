#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_cfg_next_block
#define g_cfg_next_block (*(bblock * *)(g_sd + 0x26a70))


// entry: 00403f20
// name : cse_check_common_expression
// size : 109
// sig  : il_node * cse_check_common_expression(il_node * node, node_list * stmt, bblock * block)


il_node * __cdecl cse_check_common_expression(il_node *node,node_list *stmt,bblock *block)

{
  short status;
  il_node *head;
  node_list **bucket;
  bblock *cell;
  il_node *member;
  il_node *next;
  il_node *next_member;
  
  bucket = g_expr_hash;
  do {
    for (cell = (bblock *)*bucket; cell != (bblock *)0x0; cell = (bblock *)cell->ilnode) {
      head = *(il_node **)cell;
      if (node == head) {
        status = cse_single_definition_status(head);
        if (status != 1) {
          next_member = head->cse_next;
          member = head;
          while (next_member != (il_node *)0x0) {
            next = member->cse_next;
            member->cse_next = (il_node *)0x0;
            member = next;
            next_member = next->cse_next;
          }
          return head;
        }
        head = cse_replace_with_temporary(head,stmt,block);
        return head;
      }
    }
    bucket = bucket + 1;
  } while (bucket < &g_cfg_next_block);
  return node;
}



