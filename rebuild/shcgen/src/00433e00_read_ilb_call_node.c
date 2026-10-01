#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_ilb_record_buffer
#define g_ilb_record_buffer (*(char *)(g_sd + 0x1e640))


// entry: 00433e00
// name : read_ilb_call_node
// size : 132
// sig  : void read_ilb_call_node(gen_node * node, FILE * in)


int __cdecl read_ilb_call_node(gen_node *node,FILE *in)

{
  uint got;
  
  got = read_file_bytes(in,&g_ilb_record_buffer,8);
  if (got == 8) {
    node->call_06 = (short)g_ilb_record_buffer;
    *(undefined1 *)&node->val3 = DAT_0045e641;
    *(undefined1 *)&node->filn = DAT_0045e642;
    *(undefined1 *)((int)&node->filn + 1) = DAT_0045e643;
    *(undefined1 *)&node->line = DAT_0045e644;
    *(undefined1 *)((int)&node->line + 1) = DAT_0045e645;
    *(undefined1 *)&node->listno = DAT_0045e646;
    *(undefined1 *)((int)&node->listno + 1) = DAT_0045e647;
    return;
  }
  report_message_by_code((char *)0x0,0,0xce6,(char *)0x0);
  stock_exit(9);
  return;
}



