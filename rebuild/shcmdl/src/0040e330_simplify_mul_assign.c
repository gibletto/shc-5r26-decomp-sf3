#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_debug_flags
#define g_debug_flags (*(unsigned char *)(g_sd + 0x267c0))


// entry: 0040e330
// name : simplify_mul_assign
// size : 365
// sig  : il_node * simplify_mul_assign(il_node * node)


il_node * __cdecl simplify_mul_assign(il_node *node)

{
  byte type;
  uint is_const;
  il_node *piVar1;
  
  if (((byte)g_debug_flags & 8) != 0) {
    return node;
  }
  if ((node->child->flag & 0x40) == 0) {
    piVar1 = node->child->next;
    is_const = is_const_value(piVar1,0,piVar1->type);
    if (is_const != 0) {
      piVar1 = new_const_node(node->type & 0xfc,0);
      replace_and_free_node(node->child->next,piVar1);
      node->op = IL_ASSIGN;
      return node;
    }
  }
  if ((node->child->flag & 0x40) == 0) {
    piVar1 = node->child->next;
    is_const = is_const_value(piVar1,1,piVar1->type);
    if (is_const != 0) {
      piVar1 = copy_tree(0,node->child);
      replace_and_free_node(node,piVar1);
      return piVar1;
    }
  }
  piVar1 = node->child;
  if ((piVar1->op == IL_ID) && ((piVar1->type & 2) == 0)) {
    is_const = is_const_value(piVar1->next,2,piVar1->next->type);
    if (is_const != 0) {
      piVar1 = copy_tree(0,node->child);
      replace_and_free_node(node->child->next,piVar1);
      node->op = IL_A_ADD;
      return node;
    }
  }
  piVar1 = node->child;
  if ((((piVar1->flag & 2) == 0) && (((node->type & 0xe0) != 0 || ((node->type & 4) == 0)))) &&
     (((piVar1->type & 0xe0) != 0 || ((piVar1->type & 4) == 0)))) {
    type = piVar1->next->type;
    if (((type & 0xe0) != 0) || ((type & 4) == 0)) {
      is_const = is_const_value(piVar1->next,0xffffffff,type);
      if (is_const != 0) {
        piVar1 = copy_tree(0,node->child);
        piVar1 = make_node(IL_MINUS,node->type,piVar1,(il_node *)0x0,(il_node *)0x0);
        replace_and_free_node(node->child->next,piVar1);
        node->op = IL_ASSIGN;
      }
    }
  }
  return node;
}



