#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_stage_flags
#define g_stage_flags (*(unsigned char *)(g_sd + 0x6d64))


// entry: 00407d80
// name : delete_psd_record
// size : 228
// sig  : void __cdecl delete_psd_record(psd *rec)


int __cdecl delete_psd_record(psd *rec)

{
  psd_op op;
  
  if (((byte)g_stage_flags & 2) != 0) {
    _printf(s_delcode_start__current_code_poin_00425984,rec);
  }
  op = rec->op;
  if (((((op != OP_LINE) && (op != OP_SWBGN)) && (op != OP_SWEND)) &&
      ((op != OP_BBGN && (op != OP_NON_10)))) && ((op != OP_BEND && (op != OP_CASEJMP)))) {
    if ((((op < OP_LABEL) || (OP_FLABEL < op)) && (op != OP_CTBL)) && (op != OP_CENT)) {
      rec->filno = 0;
      rec->linno = 0;
      if (rec->ea1 != (ea *)0x0) {
        free_ea(rec->ea1);
        rec->ea1 = (ea *)0x0;
      }
      if (rec->ea2 != (ea *)0x0) {
        free_ea(rec->ea2);
        rec->ea2 = (ea *)0x0;
      }
    }
    else {
      rec->filno = 0;
      rec->ea2 = (ea *)0x0;
      rec->linno = 0;
      *(undefined2 *)&rec->ea1 = 0;
      *(undefined2 *)((int)&rec->ea1 + 2) = 0;
    }
    rec->tmp = -1;
    rec->op = OP_DUMMY;
    rec->flg = '\0';
    rec->misc = '\0';
    rec->sptravel = 0;
    rec->expno = 0;
    if (((byte)g_stage_flags & 2) != 0) {
      _printf(s_delcode_end__delete_code_pointer_00425958,rec);
    }
  }
  return;
}
