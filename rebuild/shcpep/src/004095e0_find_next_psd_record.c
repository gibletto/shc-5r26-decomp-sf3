#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_stage_flags
#define g_stage_flags (*(unsigned char *)(g_sd + 0x6d64))


// entry: 004095e0
// name : find_next_psd_record
// size : 376
// sig  : psd * find_next_psd_record(code_node * node, psd * rec)


psd * __cdecl find_next_psd_record(code_node *node,psd *rec)

{
  short i;
  psd *next_rec;
  psd *cur;
  code_node *next_node;
  psd_op op;
  
  if (((byte)g_stage_flags & 2) != 0) {
    _printf(s_cnext_start__psdtbl___08lx__node_00425bac,rec,node);
  }
  if (node == (code_node *)0x0) {
    i = (short)cur;
  }
  else {
    do {
      i = 0;
      cur = node->psd;
      do {
        if (cur == rec) {
          cur = cur + 1;
          goto joined_r0x00409633;
        }
        i = i + 1;
        cur = cur + 1;
      } while (i < 0xf);
      node = node->next;
    } while (node != (code_node *)0x0);
  }
  if (node == (code_node *)0x0) {
    if (((byte)g_stage_flags & 2) != 0) {
      _printf(s_cnext_end_not_find___00425b94);
    }
    return (psd *)0x0;
  }
  while (i = i + 1, i < 0xf) {
    do {
      op = cur->op;
      if (((op != OP_DUMMY) && (op != OP_LINE)) && ((op != OP_BBGN && (op != OP_BEND)))) {
        if (((byte)g_stage_flags & 2) != 0) {
          _printf(s_cnext_end__psdtbl___08lx__00425b78,cur);
          _printf(s_nodetbl___08lx_00425b68,node);
        }
        return cur;
      }
      i = i + 1;
      cur = cur + 1;
    } while (i < 0xf);
    i = -1;
    node = node->next;
    cur = node->psd;
joined_r0x00409633:
    if (node == (code_node *)0x0) goto LAB_004096dd;
  }
  for (next_node = node->next; next_node != (code_node *)0x0; next_node = next_node->next) {
    i = 0;
    next_rec = next_node->psd;
    do {
      op = next_rec->op;
      if ((((op != OP_DUMMY) && (op != OP_LINE)) && (op != OP_BBGN)) && (op != OP_BEND)) {
        if (((byte)g_stage_flags & 2) != 0) {
          _printf(s_cnext_end__psdtbl___08lx__00425b78,next_rec);
          _printf(s_nodetbl___08lx_00425b68,next_node);
        }
        return next_rec;
      }
      i = i + 1;
      next_rec = next_rec + 1;
    } while (i < 0xf);
  }
LAB_004096dd:
  if (((byte)g_stage_flags & 2) != 0) {
    _printf(s_cnext_end_not_find___00425b94);
  }
  return (psd *)0x0;
}



