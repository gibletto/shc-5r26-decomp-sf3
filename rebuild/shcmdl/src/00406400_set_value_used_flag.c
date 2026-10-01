#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_debug_flags
#define g_debug_flags (*(unsigned char *)(g_sd + 0x267c0))


// entry: 00406400
// name : set_value_used_flag
// size : 301
// sig  : void set_value_used_flag(il_node * node)


int __cdecl set_value_used_flag(il_node *node)

{
  int pos;
  ushort flag;
  undefined *op_name;
  il_node *parent;
  il_op parent_op;
  uint used;
  
  pos = operand_index(node);
  flag = node->flag & 0xffdf;
  parent = node->parent;
  node->flag = flag;
  parent_op = parent->op;
  switch(parent_op) {
  case IL_BLOCK:
  case IL_GLABEL:
  case IL_CLABEL:
  case IL_DLABEL:
    break;
  default:
    if (((('/' < (char)parent_op) && ((char)parent_op < '>')) ||
        (('O' < (char)parent_op && ((char)parent_op < '`')))) || ((char)parent_op < ' ')) {
      node->flag = flag | 0x20;
      break;
    }
    if ((parent->type & 2) != 0) {
      node->flag = flag | 0x20;
      break;
    }
    goto LAB_004064ba;
  case IL_SWITCH:
    if (pos == 1) {
      node->flag = flag | 0x20;
    }
    break;
  case IL_IF:
    if (pos == 1) {
      node->flag = flag | 0x20;
    }
    break;
  case IL_FOR:
    if (pos == 4) {
      node->flag = flag | 0x20;
    }
    break;
  case IL_WHILE:
  case IL_DO:
    if (pos != 1) {
      node->flag = flag | 0x20;
    }
    break;
  case IL_AND:
  case IL_OR:
  case IL_COND:
    node->flag = flag | 0x20;
    break;
  case IL_COMMA:
    if (pos == 1) break;
LAB_004064ba:
    node->flag = (byte)parent->flag & 0x20 | flag;
  }
  if ((((byte)g_debug_flags & 0x20) != 0) && (g_opt_exp_pass == 0)) {
    op_name = (&g_op_names_upper)[(char)node->op];
    used = (uint)((node->flag & 0x20) != 0);
    pos = operand_index(node);
    FID_conflict__wprintf
              (s_str_00433e84,(&g_op_names_upper)[(char)parent->op],
               (uint)((parent->flag & 0x20) != 0),pos,op_name,used);
  }
  return;
}



