#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_term_list
#define g_term_list (*(term * *)(g_sd + 0x1e4c8))


// entry: 00416e00
// name : build_tree_from_terms
// size : 305
// sig  : il_node * build_tree_from_terms(void)


il_node * build_tree_from_terms(void)

{
  term *block;
  byte bVar1;
  il_node *op1;
  il_node *result;
  uint sign;
  term *cur;
  short filn;
  ushort line;
  short listno;
  term *next_term;
  
  op1 = g_term_list->node;
  filn = op1->filn;
  line = op1->line;
  listno = op1->listno;
  op1->next = (il_node *)0x0;
  if (g_term_list->op == 'A') {
    op1 = make_node(IL_MINUS,g_term_list->node->type & 0xfc,g_term_list->node,(il_node *)0x0,
                    (il_node *)0x0);
  }
  next_term = g_term_list->next;
  block = g_term_list;
  do {
    cur = next_term;
    if (cur == (term *)0x0) {
      pool_free(block,0xc);
      result = op1;
      if ((op1->op == IL_MUL) &&
         (sign = g_negation_count >> 0x1f, ((g_negation_count ^ sign) - sign & 1 ^ sign) != sign)) {
        result = make_node(IL_MINUS,op1->type & 0xfc,op1,(il_node *)0x0,(il_node *)0x0);
        apply_pattern_rule(op1);
      }
      result->filn = filn;
      result->line = line;
      result->listno = listno;
      return result;
    }
    pool_free(block,0xc);
    filn = op1->filn;
    line = op1->line;
    listno = op1->listno;
    if (cur->op == IL_ADD) {
      bVar1 = op1->type;
      if (((bVar1 & 0xf0) != 0x80) && ((bVar1 & 0xf0) != 0x90)) goto LAB_00416e92;
    }
    else {
LAB_00416e92:
      bVar1 = cur->node->type;
    }
    op1 = make_node(cur->op,bVar1 & 0xfc,op1,cur->node,(il_node *)0x0);
    op1->filn = filn;
    op1->line = line;
    op1->listno = listno;
    next_term = cur->next;
    block = cur;
  } while( true );
}



