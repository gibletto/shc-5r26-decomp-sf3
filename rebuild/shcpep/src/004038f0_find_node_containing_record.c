#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_stage_flags
#define g_stage_flags (*(unsigned char *)(g_sd + 0x6d64))


// entry: 004038f0
// name : find_node_containing_record
// size : 82
// sig  : code_node * find_node_containing_record(code_node * node, psd * rec)


code_node * __cdecl find_node_containing_record(code_node *node,psd *rec)

{
  psd *slot;
  short i;
  
  if (((byte)g_stage_flags & 2) != 0) {
    _printf(s_cnode_start__psdtbl___08lx__node_004250ec,rec,node);
  }
  do {
    if (node == (code_node *)0x0) {
      return (code_node *)0x0;
    }
    i = 0;
    slot = node->psd;
    do {
      if (rec == slot) {
        return node;
      }
      i = i + 1;
      slot = slot + 1;
    } while (i < 0xf);
    node = node->next;
  } while( true );
}



