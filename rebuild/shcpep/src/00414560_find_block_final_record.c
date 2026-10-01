#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_stage_flags
#define g_stage_flags (*(unsigned char *)(g_sd + 0x6d64))


// entry: 00414560
// name : find_block_final_record
// size : 166
// sig  : psd * find_block_final_record(code_node * block)


psd * __cdecl find_block_final_record(code_node *block)

{
  psd *rec;
  short i;
  psd *last_rec;
  psd_op op;
  
  if (((byte)g_stage_flags & 0x10) != 0) {
    _printf(s_dc_bcode_start__bp__08lx_004279d8,block);
  }
  last_rec = (psd *)0x0;
  do {
    if (block == (code_node *)0x0) {
      if (((byte)g_stage_flags & 0x10) != 0) {
        _printf(s_dc_bcode_end__np__08lx_scp__08lx_004279b4,0,last_rec);
      }
      return last_rec;
    }
    i = 0;
    rec = block->psd;
    do {
      op = rec->op;
      if (((((op != OP_DUMMY) && (op != OP_BBGN)) && (op != OP_BEND)) && (op != OP_LINE)) &&
         ((((last_rec = rec, OP_CALL < op && (op < OP_MOV_LOC)) ||
           ((op == OP_EXIT || (op == OP_RETURN)))) ||
          ((((OP_SETT < op && (op < OP_BSR)) ||
            ((op == OP_JMP || (((OP_JSR < op && (op < OP_BSRF)) || (op == OP_BRAF)))))) ||
           (op == OP_RTE)))))) break;
      i = i + 1;
      rec = rec + 1;
    } while (i < 0xf);
    block = block->next;
  } while( true );
}



