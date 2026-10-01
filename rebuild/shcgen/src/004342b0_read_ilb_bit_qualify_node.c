#include "decls.h"
#include "imports.h"

// entry: 004342b0
// name : read_ilb_bit_qualify_node
// size : 170
// sig  : void read_ilb_bit_qualify_node(gen_node * node, FILE * in)


int __cdecl read_ilb_bit_qualify_node(gen_node *node,FILE *in)

{
  uint got;
  
  got = read_file_bytes(in,(char *)&g_ilb_record_buffer,0xd);
  if (got == 0xd) {
    node->type = g_ilb_record_buffer;
    *(undefined1 *)&node->val2 = DAT_0045e641;
    *(undefined1 *)((int)&node->val2 + 1) = DAT_0045e642;
    *(undefined1 *)((int)&node->val2 + 2) = DAT_0045e643;
    *(undefined1 *)((int)&node->val2 + 3) = DAT_0045e644;
    node->bit_offset = DAT_0045e645;
    node->bit_width = DAT_0045e646;
    *(undefined1 *)&node->filn = DAT_0045e647;
    *(undefined1 *)((int)&node->filn + 1) = DAT_0045e648;
    *(undefined1 *)&node->line = DAT_0045e649;
    *(undefined1 *)((int)&node->line + 1) = DAT_0045e64a;
    *(undefined1 *)&node->listno = DAT_0045e64b;
    *(undefined1 *)((int)&node->listno + 1) = DAT_0045e64c;
    return;
  }
  report_message_by_code((char *)0x0,0,0xce6,(char *)0x0);
  stock_exit(9);
  return;
}



