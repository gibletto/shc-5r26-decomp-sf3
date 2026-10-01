#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_loaded_request
#define g_loaded_request (*(request * *)(g_sd + 0x1ff84))


// entry: 00433c20
// name : read_ilb_typed_node
// size : 219
// sig  : void read_ilb_typed_node(gen_node * node, FILE * in)


int __cdecl read_ilb_typed_node(gen_node *node,FILE *in)

{
  uint got;
  il_op op;
  
  got = read_file_bytes(in,&g_ilb_record_buffer,6);
  if (got != 6) {
    report_message_by_code((char *)0x0,0,0xce6,(char *)0x0);
    stock_exit(9);
    return;
  }
  *(undefined1 *)&node->filn = g_ilb_record_buffer;
  *(undefined1 *)((int)&node->filn + 1) = DAT_0045e641;
  *(undefined1 *)&node->line = DAT_0045e642;
  *(undefined1 *)((int)&node->line + 1) = DAT_0045e643;
  *(undefined1 *)&node->listno = DAT_0045e644;
  *(undefined1 *)((int)&node->listno + 1) = DAT_0045e645;
  if ((g_loaded_request->stage == 2) &&
     ((((op = node->op, op == IL_COMMA || (op == IL_ASSIGN)) || (op == IL_A_ADD)) ||
      (((op == IL_A_SUB || (op == IL_A_MUL)) || (op == IL_A_DIV)))))) {
    got = read_file_bytes(in,&g_ilb_record_buffer,1);
    if (got == 1) {
      *(undefined1 *)&node->val3 = g_ilb_record_buffer;
      return;
    }
    report_message_by_code((char *)0x0,0,0xce6,(char *)0x0);
    stock_exit(9);
  }
  return;
}



