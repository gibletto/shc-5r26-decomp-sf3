#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef DAT_0045e644
#define DAT_0045e644 (*(char *)(g_sd + 0x1e644))


// entry: 00433e90
// name : read_ilb_aggregate_call_node
// size : 166
// sig  : void read_ilb_aggregate_call_node(gen_node * node, FILE * in)


int __cdecl read_ilb_aggregate_call_node(gen_node *node,FILE *in)

{
  uint got;
  
  got = read_file_bytes(in,&g_ilb_record_buffer,0xc);
  if (got == 0xc) {
    *(undefined1 *)&node->val = g_ilb_record_buffer;
    *(undefined1 *)((int)&node->val + 1) = DAT_0045e641;
    *(undefined1 *)((int)&node->val + 2) = DAT_0045e642;
    *(undefined1 *)((int)&node->val + 3) = DAT_0045e643;
    node->call_06 = (short)DAT_0045e644;
    *(undefined1 *)&node->val3 = DAT_0045e645;
    *(undefined1 *)&node->filn = DAT_0045e646;
    *(undefined1 *)((int)&node->filn + 1) = DAT_0045e647;
    *(undefined1 *)&node->line = DAT_0045e648;
    *(undefined1 *)((int)&node->line + 1) = DAT_0045e649;
    *(undefined1 *)&node->listno = DAT_0045e64a;
    *(undefined1 *)((int)&node->listno + 1) = DAT_0045e64b;
    return;
  }
  report_message_by_code((char *)0x0,0,0xce6,(char *)0x0);
  stock_exit(9);
  return;
}



