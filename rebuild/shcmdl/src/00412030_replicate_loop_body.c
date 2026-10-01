#include "decls.h"
#include "imports.h"

// entry: 00412030
// name : replicate_loop_body
// size : 113
// sig  : il_node * replicate_loop_body(il_node * loop_stmt)


il_node * __cdecl replicate_loop_body(il_node *loop_stmt)

{
  il_node *pos;
  il_node *body;
  int n;
  
  if (loop_stmt->op == IL_FOR) {
    body = loop_stmt->child->next;
  }
  else {
    body = loop_stmt->child;
  }
  if (body->op != IL_BLOCK) {
    wrap_in_block_pair(body);
    body = body->parent;
  }
  pos = last_operand(body);
  n = 2;
  body = copy_tree(0,body);
  do {
    insert_before(pos,body);
    body = copy_tree(0,body);
    n = n + -1;
  } while (n != 0);
  insert_before(pos,body);
  return loop_stmt;
}



