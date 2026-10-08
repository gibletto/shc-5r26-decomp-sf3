#include "decls.h"
#include "imports.h"
#include "castmul.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_debug_flags
#define g_debug_flags (*(unsigned char *)(g_sd + 0x267c0))


// entry: 0040eb60
// name : simplify_mul
// size : 308
// sig  : il_node * simplify_mul(il_node * node)


il_node * __cdecl simplify_mul(il_node *node)

{
  uint is_const;
  il_node *result;
  short filn;
  ushort line;
  short listno;
  il_op parent_op;
  
  filn = node->filn;
  line = node->line;
  listno = node->listno;
  if (((byte)g_debug_flags & 8) != 0) {
    return MUL_ONE_FOLD(node);
  }
  parent_op = node->parent->op;
  if ((parent_op != IL_MUL) && ((parent_op != IL_SL || (node->parent->child->next->op != IL_CONST)))
     ) {
    if (node->child->op == IL_CONST) {
      swap_operands(node);
    }
    is_const = is_const_value(node->child->next,0xffffffff,node->type);
    if (is_const != 0) {
      result = copy_tree(0,node->child);
      result = make_node(IL_MINUS,node->type,result,(il_node *)0x0,(il_node *)0x0);
      result->filn = filn;
      result->line = line;
      result->listno = listno;
      replace_and_free_node(node,result);
      return result;
    }
    is_const = is_const_value(node->child->next,0,node->type);
    if (is_const != 0) {
      node->op = IL_COMMA;
      return node;
    }
    is_const = is_const_value(node->child->next,1,node->type);
    result = node;
    if (is_const != 0) {
      result = copy_tree(0,node->child);
      replace_and_free_node(node,result);
    }
    return result;
  }
  return node;
}



