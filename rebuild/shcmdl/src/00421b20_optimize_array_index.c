#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_debug_flags
#define g_debug_flags (*(unsigned char *)(g_sd + 0x267c0))


// entry: 00421b20
// name : optimize_array_index
// size : 753
// sig  : il_node * optimize_array_index(il_node * node)


il_node * __cdecl optimize_array_index(il_node *node)

{
  uint value;
  byte ty;
  byte type_class;
  uchar to_type;
  int iVar1;
  uint is_zero;
  il_node *index_expr;
  int *src;
  int min_index;
  il_node *inner;
  int max_index;
  int has_offset;
  int offset;
  il_node *const_node;
  uchar *type_ptr;
  
  if ((node->op == IL_ADD) &&
     (((node->type & 0xf8) == 0x40 ||
      (((ty = node->type & 0xf0, ty == 0x80 || (ty == 0x90)) && (0 < node->val)))))) {
    ty = node->child->type;
    type_class = ty & 0xf0;
    if (((type_class != 0x80) && (type_class != 0x90)) && ((ty & 0xf8) != 0x40)) {
      return node;
    }
    inner = node->child->next;
    if (inner->op != IL_MUL) {
      return node;
    }
    index_expr = inner->child;
    value = index_expr->next->val;
    if ((type_class == 0x80) || (type_class == 0x90)) {
      iVar1 = node->val;
    }
    else {
      iVar1 = 0x7fffffff;
    }
    min_index = 0;
    has_offset = 0;
    if (index_expr->op == IL_CAST) {
      index_expr = index_expr->child;
    }
    max_index = iVar1;
    if (index_expr->op == IL_ADD) {
      if (index_expr->child->op == IL_CONST) {
        swap_operands(index_expr);
      }
      const_node = index_expr->child->next;
      if ((const_node->op == IL_CONST) &&
         (is_zero = is_const_value(const_node,0,const_node->type), is_zero == 0)) {
        has_offset = 1;
        offset = index_expr->child->next->val;
        max_index = iVar1 - value * offset;
        min_index = -(value * offset);
      }
    }
    to_type = select_index_type_for_range(max_index,min_index,offset,value,iVar1,has_offset);
    if (to_type != 0xff) {
      if (has_offset == 1) {
        inner->op = IL_ADD;
        index_expr->op = IL_MUL;
        inner->child->next->val = value * offset;
        index_expr->child->next->val = value;
        inner = index_expr;
      }
      if ((to_type == '\x1c') || (iVar1 = power_of_two_index(value,1), iVar1 != 0)) {
        if ((has_offset == 1) && (inner->parent->op == IL_CAST)) {
          inner->type = inner->parent->type & 0xfc;
          index_expr = new_node(IL_CAST,inner->parent->type & 0xfc);
          insert_parent(inner->child,index_expr);
          index_expr = new_node(IL_CAST,inner->parent->type & 0xfc);
          insert_parent(inner->child->next,index_expr);
          index_expr = inner->parent;
          replace_node(index_expr,inner);
          free_node(index_expr);
        }
      }
      else {
        inner->type = to_type;
        inner->child->next->type = to_type;
        src = &inner->child->next->val;
        convert_constant(to_type,'\x1c',(uint *)src,(uint *)src);
        type_ptr = &inner->child->type;
        if ((*type_ptr & 0xfc) != (short)(char)to_type) {
          if (inner->child->op == IL_CAST) {
            *type_ptr = to_type;
          }
          else {
            index_expr = new_node(IL_CAST,to_type);
            insert_parent(inner->child,index_expr);
          }
        }
        if (inner->parent->op != IL_CAST) {
          index_expr = new_node(IL_CAST,'\x1c');
          insert_parent(inner,index_expr);
        }
      }
    }
    if (((byte)g_debug_flags & 8) == 0) {
      return node;
    }
    dump_tree(node,1,s_opt_array_cahge_00435bf8);
    return node;
  }
  if (node->op != IL_ASTER) {
    return node;
  }
  ty = node->type & 0xf0;
  if ((ty != 0x80) && (ty != 0x90)) {
    return node;
  }
  inner = node->child;
  if (inner->op != IL_ADD) {
    return node;
  }
  index_expr = inner->child;
  const_node = index_expr->next;
  if (const_node->op != IL_CONST) {
    return node;
  }
  node->child = index_expr;
  index_expr->parent = node;
  index_expr->next = (il_node *)0x0;
  inner->child = (il_node *)0x0;
  inner->parent = (il_node *)0x0;
  insert_parent(node,inner);
  node->next = const_node;
  const_node->parent = inner;
  return inner;
}



