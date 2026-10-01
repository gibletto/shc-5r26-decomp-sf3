#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_node_alloc_hook
#define g_node_alloc_hook (*(int (**)())(g_sd + 0x1e4ec))
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 00404830
// name : read_il_node
// size : 417
// sig  : il_node * read_il_node(void)


il_node * read_il_node(void)

{
  short sVar1;
  il_node *node;
  uint size;
  int *buf;
  short extra;
  
  if (g_node_alloc_hook == 0) {
    fatal_error(0x109b);
  }
  node = (il_node *)(*g_node_alloc_hook)();
  if (node == (il_node *)0x0) {
    return (il_node *)0x0;
  }
  read_ila_bytes(1,(char *)node);
  switch(node->op) {
  case IL_FILE:
  case IL_E_FILE:
  case IL_E_BLOCK:
  case IL_EMPTY:
  case IL_IF:
  case IL_FOR:
  case IL_WHILE:
  case IL_DO:
  case IL_BREAK:
  case IL_CONTINUE:
  case IL_NULL:
  case IL_ARG:
  case IL_E_ARG:
    goto switchD_00404876_caseD_0;
  default:
    read_node_type(node);
    goto switchD_00404876_caseD_0;
  case IL_FUNC:
  case IL_BLOCK:
  case IL_SWITCH:
  case IL_GOTO:
  case IL_GLABEL:
  case IL_CLABEL:
  case IL_DLABEL:
    buf = (int *)&node->symx;
    size = 2;
    break;
  case IL_ASM:
    read_ila_bytes(4,(char *)&node->val);
    buf = &node->val2;
    size = 4;
    break;
  case IL_CALL:
    read_node_type(node);
    read_ila_bytes(1,(char *)node->unknown_06);
    read_ila_bytes(1,(char *)&node->unknown_08);
    (*(unsigned char *)((char *)&sVar1 + 0)) = node->unknown_08;
    (*(unsigned char *)((char *)&sVar1 + 1)) = node->call_flags;
    node->unknown_08 = (char)(sVar1 << 8);
    node->call_flags = (char)((ushort)(sVar1 << 8) >> 8);
    goto switchD_00404876_caseD_0;
  case IL_QUALIFY:
    read_node_type(node);
    buf = &node->val2;
    size = 4;
    break;
  case IL_B_QUALIFY:
    read_node_type(node);
    read_ila_bytes(4,(char *)&node->val2);
    read_ila_bytes(1,(char *)&node->boff);
    buf = (int *)&node->bsiz;
    size = 1;
    break;
  case IL_PRI:
  case IL_PRD:
  case IL_POI:
  case IL_POD:
    read_node_type(node);
    buf = &node->val;
    size = 4;
    break;
  case IL_ID:
    read_ila_bytes(2,(char *)&node->symx);
    node->type = g_symtab[node->symx].type;
    goto switchD_00404876_caseD_0;
  case IL_CONST:
    read_node_type(node);
    if ((node->type & 0xfc) == 0x40) {
      read_ila_bytes(2,(char *)&extra);
      node->val2 = (int)extra;
    }
    buf = &node->val;
    size = const_value_size((int)(char)(node->type & 0xfc));
  }
  read_ila_bytes(size,(char *)buf);
switchD_00404876_caseD_0:
  read_ila_bytes(2,(char *)&node->filn);
  read_ila_bytes(2,(char *)&node->line);
  read_ila_bytes(2,(char *)&node->listno);
  return node;
}



