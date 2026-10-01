#include "decls.h"
#include "imports.h"

// entry: 00435480
// name : read_ilb_tree
// size : 152
// sig  : gen_node * read_ilb_tree(gen_node * node, FILE * in)


gen_node * __cdecl read_ilb_tree(gen_node *node,FILE *in)

{
  short full;
  gen_node *pgVar1;
  gen_node *pgVar2;
  int depth;
  
  if (node == (gen_node *)0x0) {
    node = read_ilb_node(in);
  }
  depth = 0;
  pgVar2 = node->parent;
  pgVar1 = node;
  while (pgVar2 != (gen_node *)0x0) {
    pgVar1 = pgVar1->parent;
    depth = depth + 1;
    pgVar2 = pgVar1->parent;
  }
  pgVar2 = node;
  pgVar1 = node;
  if (depth <= g_ilb_depth) {
    do {
      if (pgVar2 == (gen_node *)0x0) break;
      if (pgVar1 == (gen_node *)0x0) {
        return (gen_node *)0x0;
      }
      if (pgVar1 == (gen_node *)0xffffffff) break;
      full = ilb_node_operands_full(pgVar2,depth);
      if (full == 0) {
        pgVar1 = read_ilb_node(in);
      }
      else {
        depth = depth + 1;
        pgVar2 = last_operand(pgVar2);
      }
    } while (depth <= g_ilb_depth);
  }
  if (pgVar1 == (gen_node *)0x0) {
    return (gen_node *)0x0;
  }
  pgVar2 = (gen_node *)0xffffffff;
  if (pgVar1 != (gen_node *)0xffffffff) {
    pgVar2 = node;
  }
  return pgVar2;
}



