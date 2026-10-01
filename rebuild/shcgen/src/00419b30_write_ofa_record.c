#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_ofa_record_out
#define g_ofa_record_out (*(FILE * *)(g_sd + 0x1e5e8))


// entry: 00419b30
// name : write_ofa_record
// size : 234
// sig  : void write_ofa_record(FILE * out, psd * rec, int location, int pool_size)


int __cdecl write_ofa_record(FILE *out,psd *rec,int location,int pool_size)

{
  g_ofa_record_out = out;
  switch(rec->op) {
  case OP_NON_10:
    write_ofa_end_record(rec,location);
    return;
  case OP_CASEJMP:
    write_ofa_casejmp_record(rec,location);
    return;
  case OP_CTBL:
    write_ofa_ctbl_record(rec,location);
    return;
  case OP_LABEL:
  case OP_CLABEL:
  case OP_DLABEL:
  case OP_FLABEL:
    write_ofa_label_record(rec);
    return;
  case OP_ENTER:
    write_ofa_enter_record(rec);
    return;
  case OP_EXIT:
    write_ofa_exit_record(rec,location,(short)pool_size);
    return;
  case OP_RETURN:
  case OP_JUMP:
    write_ofa_jump_record(rec,location,(short)pool_size);
    return;
  case OP_CALL:
  case OP_JUMPT:
  case OP_JUMPF:
  case OP_MOVA_PC:
  case OP_MOVA_FC:
    write_ofa_label_operand_record(rec,location);
    return;
  case OP_MOV_LOC:
    write_ofa_mov_loc_record(rec);
    return;
  case OP_MOVA_LC:
    write_ofa_mova_lc_record(rec);
    return;
  case OP_MOVI:
  case OP_NON_2C:
    write_ofa_immediate_record(rec);
    return;
  case OP_NON_2E:
    write_ofa_op2e_record(rec);
    return;
  case OP_RTE:
  case OP_BRA:
  case OP_JMP:
  case OP_RTS:
    write_ofa_transfer_record(rec,location,(short)pool_size);
  }
  return;
}



