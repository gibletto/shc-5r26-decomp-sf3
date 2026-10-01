#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_ilb_cursor
#define g_ilb_cursor (*(gen_node * *)(g_sd + 0x1ff90))


// entry: 004347a0
// name : attach_ilb_node
// size : 310
// sig  : gen_node * attach_ilb_node(gen_node * node)


gen_node * __cdecl attach_ilb_node(gen_node *node)

{
  int level;
  int iVar1;
  gen_node *ancestor;
  int new_depth;
  gen_node *walk;
  
  if (g_ilb_cursor == (gen_node *)0x0) {
    iVar1 = 0;
    g_ilb_cursor = node;
    g_ilb_depth = 0;
    do {
      iVar1 = iVar1 + 4;
      *(undefined4 *)(g_ilb_operand_counts + -4 + iVar1) = 0;
    } while (iVar1 < 0x2000);
  }
  else {
    iVar1 = 0;
    ancestor = g_ilb_cursor->parent;
    walk = g_ilb_cursor;
    while (ancestor != (gen_node *)0x0) {
      iVar1 = iVar1 + 1;
      walk = walk->parent;
      ancestor = walk->parent;
    }
    new_depth = g_ilb_depth;
    if ((iVar1 < g_ilb_depth) && (level = iVar1 + 1, new_depth = iVar1, level <= g_ilb_depth)) {
      iVar1 = level * 4;
      do {
        iVar1 = iVar1 + 4;
        level = level + 1;
        *(undefined4 *)(g_ilb_operand_counts + -4 + iVar1) = 0;
      } while (level <= g_ilb_depth);
    }
    g_ilb_depth = new_depth;
    switch(node->op) {
    case IL_FILE:
      node = begin_ilb_file(node);
      break;
    case IL_E_FILE:
      node = attach_ilb_file_end(node);
      break;
    default:
      node = attach_ilb_operator(node);
      break;
    case IL_FUNC:
    case IL_ASM:
      node = attach_ilb_function(node);
      break;
    case IL_BLOCK:
      node = attach_ilb_block(node);
      break;
    case IL_E_BLOCK:
      node = attach_ilb_block_end(node);
      break;
    case IL_EMPTY:
    case IL_BREAK:
    case IL_CONTINUE:
    case IL_GOTO:
      node = attach_ilb_jump_statement(node);
      break;
    case IL_SWITCH:
    case IL_IF:
    case IL_FOR:
    case IL_WHILE:
    case IL_DO:
    case IL_RETURN:
    case IL_GLABEL:
    case IL_CLABEL:
    case IL_DLABEL:
      node = attach_ilb_statement(node);
      break;
    case IL_ID:
    case IL_CONST:
      node = attach_ilb_leaf_operand(node);
      break;
    case IL_ARG:
      node = attach_ilb_argument(node);
      break;
    case IL_E_ARG:
      node = attach_ilb_argument_end(node);
    }
  }
  return (gen_node *)((node == (gen_node *)0x0) - 1 & (uint)node);
}



