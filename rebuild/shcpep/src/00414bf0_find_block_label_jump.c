#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_stage_flags
#define g_stage_flags (*(unsigned char *)(g_sd + 0x6d64))


// entry: 00414bf0
// name : find_block_label_jump
// size : 334
// sig  : psd * find_block_label_jump(code_node * block)


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

psd * __cdecl find_block_label_jump(code_node *block)

{
  psd_op pVar1;
  psd *rec;
  short i;
  
  _g_brsrchk_switch_marker = 0;
  do {
    if (block == (code_node *)0x0) {
      if (((byte)g_stage_flags & 2) != 0) {
        _printf(s_brsrchk_end__return_0_00427b00);
      }
      return (psd *)0x0;
    }
    i = 0;
    rec = block->psd;
    do {
      if (rec == (psd *)0x0) break;
      pVar1 = rec->op;
      if (pVar1 != OP_DUMMY) {
        if (pVar1 == OP_SWBGN) {
          _g_brsrchk_switch_marker = 1;
          if (((byte)g_stage_flags & 2) != 0) {
            _printf(s_brsrchk_end__return_0_00427b00);
          }
          return (psd *)0x0;
        }
        if (pVar1 == OP_SWEND) {
          _g_brsrchk_switch_marker = 0xffffffff;
          if (((byte)g_stage_flags & 2) != 0) {
            _printf(s_brsrchk_end__return_0_00427b00);
          }
          return (psd *)0x0;
        }
        if ((pVar1 == OP_JUMP) && (rec->ea1->labels != (label_ref *)0x0)) {
          if (((byte)g_stage_flags & 2) != 0) {
            _printf(s_brsrchk_end__cp__08lx_00427ae8,rec);
          }
          return rec;
        }
        if ((((((OP_CALL < pVar1) && (pVar1 < OP_MOV_LOC)) || (pVar1 == OP_EXIT)) ||
             (pVar1 == OP_RETURN)) ||
            ((((OP_SETT < pVar1 && (pVar1 < OP_BSR)) ||
              ((pVar1 == OP_JMP || ((OP_JSR < pVar1 && (pVar1 < OP_BSRF)))))) || (pVar1 == OP_BRAF))
            )) || (pVar1 == OP_RTE)) {
          return (psd *)0x0;
        }
      }
      i = i + 1;
      rec = rec + 1;
    } while (i < 0xf);
    block = block->next;
  } while( true );
}



