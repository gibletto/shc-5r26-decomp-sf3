#include "decls.h"
#include "imports.h"

// entry: 00404ae0
// name : write_il_node
// size : 432
// sig  : void write_il_node(il_node * node)


int __cdecl write_il_node(il_node *node)

{
  unsigned char _frec_2[2];
#define extra (*(undefined2 *)(_frec_2 + 0))
  short sVar1;
  uint size;
  int *buf;
  bool has_fr0set;
  bool is_block;
  bool is_id;
  
  has_fr0set = false;
  is_id = false;
  is_block = false;
  write_ilb_bytes(1,(char *)node);
  switch(node->op) {
  case IL_FILE:
  case IL_E_FILE:
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
    goto switchD_00404b10_caseD_0;
  default:
    goto switchD_00404b10_caseD_2;
  case IL_FUNC:
  case IL_SWITCH:
  case IL_GOTO:
  case IL_GLABEL:
  case IL_CLABEL:
  case IL_DLABEL:
    goto switchD_00404b10_caseD_4;
  case IL_ASM:
    write_ilb_bytes(4,(char *)&node->val);
    buf = &node->val2;
    size = 4;
    break;
  case IL_BLOCK:
    is_block = true;
    goto switchD_00404b10_caseD_4;
  case IL_E_BLOCK:
    is_block = true;
    goto switchD_00404b10_caseD_0;
  case IL_CALL:
    write_node_type(node);
    write_ilb_bytes(1,(char *)node->unknown_06);
    buf = (int *)&node->unknown_08;
    (*(unsigned char *)((char *)&sVar1 + 0)) = node->unknown_08;
    (*(unsigned char *)((char *)&sVar1 + 1)) = node->call_flags;
    node->unknown_08 = (char)(sVar1 >> 8);
    node->call_flags = (char)((ushort)(sVar1 >> 8) >> 8);
    size = 1;
    break;
  case IL_QUALIFY:
    write_node_type(node);
    buf = &node->val2;
    size = 4;
    break;
  case IL_B_QUALIFY:
    write_node_type(node);
    write_ilb_bytes(4,(char *)&node->val2);
    write_ilb_bytes(1,(char *)&node->boff);
    buf = (int *)&node->bsiz;
    size = 1;
    break;
  case IL_PRI:
  case IL_PRD:
  case IL_POI:
  case IL_POD:
    write_node_type(node);
    buf = &node->val;
    size = 4;
    break;
  case IL_A_ADD:
  case IL_A_SUB:
  case IL_A_MUL:
  case IL_A_DIV:
  case IL_ASSIGN:
  case IL_COMMA:
    has_fr0set = true;
    goto switchD_00404b10_caseD_2;
  case IL_ID:
    is_id = true;
switchD_00404b10_caseD_4:
    buf = (int *)&node->symx;
    size = 2;
    break;
  case IL_CONST:
    write_node_type(node);
    if ((node->type & 0xfc) == 0x40) {
      extra = (undefined2)node->val2;
      write_ilb_bytes(2,(char *)&extra);
    }
    buf = &node->val;
    size = const_value_size((int)(char)(node->type & 0xfc));
  }
  write_ilb_bytes(size,(char *)buf);
  has_fr0set = is_id;
switchD_00404b10_caseD_0:
  write_ilb_bytes(2,(char *)&node->filn);
  write_ilb_bytes(2,(char *)&node->line);
  write_ilb_bytes(2,(char *)&node->listno);
  if (is_id) {
    write_ilb_bytes(2,(char *)&node->lreg);
  }
  if (is_block) {
    write_ilb_bytes(1,(char *)&node->val);
  }
  if (has_fr0set) {
    write_ilb_bytes(1,&node->fr0set);
  }
  return;
switchD_00404b10_caseD_2:
  write_node_type(node);
  goto switchD_00404b10_caseD_0;
#undef extra
}



