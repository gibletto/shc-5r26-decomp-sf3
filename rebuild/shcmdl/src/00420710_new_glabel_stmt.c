#include "decls.h"
#include "imports.h"

// entry: 00420710
// name : new_glabel_stmt
// size : 38
// sig  : il_node * new_glabel_stmt(short label)


il_node * __cdecl new_glabel_stmt(short label)

{
  il_node *label_stmt;
  il_node *empty;
  
  label_stmt = alloc_node();
  label_stmt->op = IL_GLABEL;
  label_stmt->symx = label;
  empty = alloc_node();
  empty->op = IL_EMPTY;
  label_stmt->child = empty;
  empty->parent = label_stmt;
  return label_stmt;
}



