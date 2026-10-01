#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_debug_flags
#define g_debug_flags (*(unsigned char *)(g_sd + 0x267c0))
#undef g_fold_warnings
#define g_fold_warnings (*(unsigned char *)(g_sd + 0x26ef4))


// entry: 004065d0
// name : fold_constants
// size : 392
// sig  : il_node * fold_constants(il_node * node)


il_node * __cdecl fold_constants(il_node *node)

{
  short status;
  il_node *result;
  int arith_class;
  uchar to_type;
  int *src;
  uchar from_type;
  il_op op;
  il_node *opnd;
  
  result = node;
  if ((((*(int *)(&g_fold_op_table + (char)node->op * 4) != 0) || (node->op == IL_CAST)) &&
      (node->child->op == IL_CONST)) &&
     ((opnd = node->child->next, opnd == (il_node *)0x0 || (opnd->op == IL_CONST)))) {
    if (((byte)g_debug_flags & 0x40) != 0) {
      dump_tree(node,1,s_folding_00433ec8);
    }
    if ((node->type & 0xf8) == 0x50) {
      return node;
    }
    if ((node->type & 0xe0) == 0x80) {
      node->type = '\x1c';
    }
    result = new_node(IL_CONST,node->type & 0xfc);
    result->filn = node->filn;
    result->line = node->line;
    result->listno = node->listno;
    op = node->op;
    if (op == IL_CAST) {
      src = &node->child->val;
      from_type = node->child->type;
      to_type = node->type;
    }
    else {
      if (((op & IL_NON_F8) == IL_EQ) || (op == IL_NOT)) {
        from_type = node->child->type;
      }
      else {
        from_type = node->type;
      }
      src = &result->val;
      arith_class = type_arith_class(from_type);
      opnd = node->child;
      if (opnd->next == (il_node *)0x0) {
        (**(code **)(*(int *)(&g_fold_op_table + (char)node->op * 4) + arith_class * 4))
                  (&opnd->val,src);
      }
      else {
        status = (**(code **)(*(int *)(&g_fold_op_table + (char)node->op * 4) + arith_class * 4))
                           (&opnd->val,&opnd->next->val,src);
        if (status == 1) {
          (*(unsigned char *)((char *)&g_fold_warnings + 0)) = (byte)g_fold_warnings | 2;
        }
        else if (status == 4) {
          (*(unsigned char *)((char *)&g_fold_warnings + 0)) = (byte)g_fold_warnings | 4;
        }
        else if (status == 6) {
          (*(unsigned char *)((char *)&g_fold_warnings + 0)) = (byte)g_fold_warnings | 8;
        }
      }
      from_type = node->type;
      to_type = from_type;
    }
    convert_constant(to_type,from_type,(uint *)src,(uint *)&result->val);
    replace_and_free_node(node,result);
    if (((byte)g_debug_flags & 0x40) != 0) {
      dump_tree(result,1,s_folding_change_00433eb8);
    }
  }
  return result;
}



