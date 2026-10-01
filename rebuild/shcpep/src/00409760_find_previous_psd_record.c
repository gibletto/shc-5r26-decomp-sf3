#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_stage_flags
#define g_stage_flags (*(unsigned char *)(g_sd + 0x6d64))


// entry: 00409760
// name : find_previous_psd_record
// size : 185
// sig  : psd * find_previous_psd_record(code_node * node, psd * rec)


psd * __cdecl find_previous_psd_record(code_node *node,psd *rec)

{
  psd *cur;
  short i;
  psd *prev;
  psd_op op;
  
  prev = (psd *)0x0;
  if (((byte)g_stage_flags & 2) != 0) {
    _printf(s_prefind_start__nodetbl__08lx__ps_00425c34,node,rec);
  }
  do {
    if (node == (code_node *)0x0) {
      if (((byte)g_stage_flags & 2) != 0) {
        _printf(s_prefind_end__nodetbl__08lx__00425be8,0);
        _printf(s_psdtbl__08lx_00425bd8,prev);
      }
      return prev;
    }
    i = 0;
    cur = node->psd;
    do {
      if (cur == rec) {
        if (((byte)g_stage_flags & 2) != 0) {
          _printf(s_prefind_end__psdtbl__08lx_00425c18,prev);
          _printf(s_nodetbl__08lx_00425c08,node);
        }
        return prev;
      }
      op = cur->op;
      if ((((op != OP_DUMMY) && (op != OP_LINE)) && (op != OP_BBGN)) && (op != OP_BEND)) {
        prev = cur;
      }
      i = i + 1;
      cur = cur + 1;
    } while (i < 0xf);
    node = node->next;
  } while( true );
}



