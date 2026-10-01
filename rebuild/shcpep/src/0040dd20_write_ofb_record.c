#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_ofb_record_out
#define g_ofb_record_out (*(FILE * *)(g_sd + 0x5358))


// entry: 0040dd20
// name : write_ofb_record
// size : 234
// sig  : void write_ofb_record(FILE * out, psd * rec, int location, int pool_size)


int __cdecl write_ofb_record(FILE *out,psd *rec,int location,int pool_size)

{
  g_ofb_record_out = out;
  switch(rec->op) {
  case OP_NON_10:
    write_ofb_end_record(rec,location);
    return;
  case OP_CASEJMP:
    write_ofb_casejmp_record(rec,location);
    return;
  case OP_CTBL:
    write_ofb_ctbl_record(rec,location);
    return;
  case OP_LABEL:
  case OP_CLABEL:
  case OP_DLABEL:
  case OP_FLABEL:
    write_ofb_label_record(rec);
    return;
  case OP_ENTER:
    write_ofb_enter_record(rec);
    return;
  case OP_EXIT:
    write_ofb_exit_record(rec,location,(short)pool_size);
    return;
  case OP_RETURN:
  case OP_JUMP:
    write_ofb_jump_record(rec,location,(short)pool_size);
    return;
  case OP_CALL:
  case OP_JUMPT:
  case OP_JUMPF:
  case OP_MOVA_PC:
  case OP_MOVA_FC:
    write_ofb_label_operand_record(rec,location);
    return;
  case OP_MOV_LOC:
    write_ofb_mov_loc_record(rec);
    return;
  case OP_MOVA_LC:
    write_ofb_mova_lc_record(rec);
    return;
  case OP_MOVI:
  case OP_NON_2C:
    write_ofb_immediate_record(rec);
    return;
  case OP_NON_2E:
    write_ofb_op2e_record(rec);
    return;
  case OP_RTE:
  case OP_BRA:
  case OP_JMP:
  case OP_RTS:
    write_ofb_transfer_record(rec,location,(short)pool_size);
  }
  return;
}



