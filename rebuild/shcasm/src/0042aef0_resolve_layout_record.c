#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))


// entry: 0042aef0
// name : resolve_layout_record
// size : 574
// sig  : layout_record * resolve_layout_record(layout_record * rec)


layout_record * __cdecl resolve_layout_record(layout_record *rec)

{
  label_ref *cur_ref;
  layout_record *next_item;
  label_ref *next_ref;
  
  switch(rec->op) {
  case OP_B_ASM:
    relax_inline_asm_record(rec,1);
    break;
  case OP_C_JMP:
    relax_switch_jump_record(rec,1);
    break;
  case OP_DUMMY_12:
  case OP_DUMMY_13:
  case OP_CTBL:
  case OP_CENT:
  case OP_BBGN:
  case OP_BEND:
  case OP_LABEL:
  case OP_CLABEL:
  case OP_DLABEL:
  case OP_FLABEL:
  case OP_DUMMY_1C:
  case OP_LINE:
  case OP_SWBGN:
  case OP_SWEND:
  case OP_DUMMY_2D:
  case OP_DUMMY_2F:
  case OP_EXTLD:
  case OP_EXTST:
  case OP_DUMMY_32:
  case OP_DUMMY_33:
  case OP_DUMMY_34:
  case OP_DUMMY_35:
  case OP_DUMMY_36:
  case OP_DUMMY_37:
  case OP_DUMMY_38:
  case OP_DUMMY_39:
  case OP_DUMMY_3A:
  case OP_DUMMY_3B:
  case OP_DUMMY_3C:
  case OP_DUMMY_3D:
  case OP_DUMMY_3E:
  case OP_DUMMY_3F:
  case OP_MOV:
  case OP_DUMMY_41:
  case OP_MOVT:
  case OP_DUMMY_43:
  case OP_MOVA:
  case OP_DUMMY_45:
  case OP_SWAP:
  case OP_XTRCT:
  case OP_SHAD:
  case OP_SHAL:
  case OP_SHLL:
  case OP_SHLL2:
  case OP_SHLL8:
  case OP_SHLL16:
  case OP_ROTL:
  case OP_ROTCL:
  case OP_CMP_EQ:
  case OP_CMP_HS:
  case OP_CMP_GE:
  case OP_CMP_HI:
  case OP_CMP_GT:
  case OP_CMP_PZ:
  case OP_CMP_PL:
  case OP_CMP_STR:
  case OP_SHLD:
  case OP_SHAR:
  case OP_SHLR:
  case OP_SHLR2:
  case OP_SHLR8:
  case OP_SHLR16:
  case OP_ROTR:
  case OP_ROTCR:
  case OP_ADD:
  case OP_ADDC:
  case OP_ADDV:
  case OP_SUB:
  case OP_SUBC:
  case OP_SUBV:
  case OP_DUMMY_66:
  case OP_DUMMY_67:
  case OP_DUMMY_68:
  case OP_DUMMY_69:
  case OP_DUMMY_6A:
  case OP_DUMMY_6B:
  case OP_DUMMY_6C:
  case OP_DUMMY_6D:
  case OP_DUMMY_6E:
  case OP_MUL:
  case OP_MULS:
  case OP_MULU:
  case OP_MAC:
  case OP_DUMMY_73:
  case OP_DIV1:
  case OP_DIV0S:
  case OP_DIV0U:
  case OP_DUMMY_77:
  case OP_NEG:
  case OP_NEGC:
  case OP_DUMMY_7A:
  case OP_EXTS:
  case OP_EXTU:
  case OP_DUMMY_7D:
  case OP_DUMMY_7E:
  case OP_DUMMY_7F:
  case OP_AND:
  case OP_OR:
  case OP_XOR:
  case OP_NOT:
  case OP_DUMMY_84:
  case OP_TST:
  case OP_TAS:
  case OP_DUMMY_87:
  case OP_NOP:
  case OP_DUMMY_89:
  case OP_DT:
  case OP_CLRT:
  case OP_LDC:
  case OP_LDS:
  case OP_SETT:
  case OP_BF:
  case OP_BT:
  case OP_BSR:
  case OP_JSR:
    break;
  case OP_ENTER:
    compute_enter_expansion_size(rec,1);
    break;
  case OP_EXIT:
    relax_exit_record(rec,1);
    break;
  case OP_RETURN:
    relax_return_record(rec,1);
    break;
  case OP_CALL:
    relax_call_record(rec,1);
    break;
  case OP_JUMP:
    relax_jump_record(rec,1);
    break;
  case OP_JUMPT:
  case OP_JUMPF:
    relax_conditional_jump_record(rec,1);
    break;
  case OP_MV_LOC:
    relax_mv_loc_record(rec,1);
    break;
  case OP_MVA_LC:
    relax_mva_lc_record(rec,1);
    break;
  case OP_MVA_PC:
    relax_mva_pc_record(rec,1);
    break;
  case OP_MOVI:
    relax_movi_record(rec,1);
    break;
  case OP_MVA_FC:
    relax_mva_fc_record(rec,1);
    break;
  case OP_MOVIF:
    relax_movif_record(rec,1);
    break;
  case OP_FPRSET:
    relax_fprset_record(rec,1);
    break;
  case OP_RTE:
  case OP_BRA:
  case OP_JMP:
  case OP_RTS:
    relax_unconditional_branch_record(rec,1);
  }
  if (((g_current_request->flags_13c & 2) != 0) && (rec->location != 0)) {
    _printf(s_CODE__02x_Offset__08x_004420bc,(int)(char)rec->op,rec->location);
  }
  next_item = rec->next;
  if ((((rec->op != OP_MV_LOC) && (rec->op != OP_MVA_LC)) && (rec->op != OP_C_JMP)) &&
     (rec->op != OP_CTBL)) {
    cur_ref = rec->labels;
    while (cur_ref != (label_ref *)0x0) {
      next_ref = cur_ref->next;
      pool_free(cur_ref,8);
      cur_ref = next_ref;
    }
  }
  stock_free(rec);
  return next_item;
}



