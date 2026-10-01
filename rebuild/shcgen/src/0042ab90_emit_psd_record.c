#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_section
#define g_current_section (*(request_section * *)(g_sd + 0x1f9b8))
#undef g_lit_file
#define g_lit_file (*(FILE * *)(g_sd + 0x1fa08))
#undef g_ofa_file
#define g_ofa_file (*(FILE * *)(g_sd + 0x1f9ec))
#undef g_pool_label_sptravel
#define g_pool_label_sptravel (*(int *)(g_sd + 0x1b620))
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))
#undef g_sua_file
#define g_sua_file (*(FILE * *)(g_sd + 0x1fa30))


// entry: 0042ab90
// name : emit_psd_record
// size : 984
// sig  : void emit_psd_record(psd * rec, int pool_size)


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl emit_psd_record(psd *rec,int pool_size)

{
  unsigned char _frec_18[24];
#define branch_rec (*(psd *)(_frec_18 + 0))
  byte bVar1;
  short labno;
  ushort linno;
  uint placement;
  label_ref *ref;
  ea *operand;
  int iVar2;
  short sVar3;
  int new_pool_size;
  psd_op rec_op;
  request_section *section;
  
  rec_op = rec->op;
  delete_unreachable_record(rec);
  if (rec->op == OP_DUMMY) {
    if (rec_op == OP_EXIT) {
      g_exit_record_dropped = '\x01';
      return;
    }
    if (rec_op != OP_RETURN) {
      return;
    }
    g_return_record_dropped = '\x01';
    return;
  }
  if (*(short *)g_request->unknown_004 == 0) {
    if (pool_size == 0) {
      placement = decide_literal_pool_placement(rec,g_lit_file);
      new_pool_size = (int)(short)placement;
      iVar2 = pool_size;
      if (((((new_pool_size != 0) && (rec_op = rec->op, iVar2 = new_pool_size, rec_op != OP_EXIT))
           && (rec_op != OP_RETURN)) &&
          (((rec_op != OP_CASEJMP && (rec_op != OP_JUMP)) &&
           ((rec_op != OP_RTE && ((rec_op != OP_BRA && (rec_op != OP_JMP)))))))) &&
         (rec_op != OP_RTS)) {
        ref = alloc_zeroed(8);
        if (ref == (label_ref *)0x0) {
          report_codegen_message(0xbcd,1,0,0,(char *)0x0);
        }
        labno = make_new_label_number();
        fill_label_ref(ref,labno,0);
        operand = alloc_zeroed(0xc);
        if (operand == (ea *)0x0) {
          report_codegen_message(0xbcd,1,0,0,(char *)0x0);
        }
        fill_ea(operand,'\a',-1,-1,'\0',0,ref);
        rec_op = rec->op;
        if ((((rec_op == OP_CENT) || (rec_op == OP_CTBL)) || (rec_op == OP_BBGN)) ||
           ((rec_op == OP_BEND || (rec_op == OP_CASEJMP)))) {
          linno = 0;
          sVar3 = 0;
        }
        else {
          sVar3 = rec->filno;
          linno = rec->linno;
        }
        fill_psd_record(&branch_rec,OP_BRA,'\x02','\0',rec->expno,sVar3,linno,operand,(ea *)0x0,0,-1
                       );
        emit_psd_record(&branch_rec,new_pool_size);
        fill_label_record(&branch_rec,OP_LABEL,labno,g_pool_label_sptravel);
        emit_psd_record(&branch_rec,0);
        iVar2 = pool_size;
      }
      pool_size = iVar2;
      _g_pool_label_sptravel = g_sptravel;
    }
    write_ofa_record(g_ofa_file,rec,g_current_section->location,(int)(short)pool_size);
  }
  rec_op = rec->op;
  if (((rec_op == OP_MULS) || (rec_op == OP_MULU)) || (rec_op == OP_MUL)) {
    g_mac_regs_used = g_mac_regs_used | 1;
  }
  if ((rec->op == OP_MAC) || (rec->op == OP_CLRMAC)) {
    g_mac_regs_used = g_mac_regs_used | 3;
  }
  if ((g_request->macsave == '\0') && ((rec->op == OP_CALL || (rec->op == OP_JSR)))) {
    g_mac_regs_used = g_mac_regs_used | 3;
  }
  if ((rec->op == OP_NON_DF) || (rec->op == OP_NON_DD)) {
    g_saved_sys_mask = g_saved_sys_mask | 1;
  }
  if (rec->op == OP_LDS) {
    bVar1 = rec->ea2->type & 0x1f;
    if (bVar1 == 0xf) {
      g_saved_sys_mask = g_saved_sys_mask | 1;
    }
    else if (bVar1 == 0x10) {
      g_saved_sys_mask = g_saved_sys_mask | 2;
    }
  }
  if ((rec->op == OP_NON_2C) && (rec->tmp != '\0')) {
    g_saved_sys_mask = g_saved_sys_mask | 1;
  }
  if ((g_request->cpu == 2) && (g_request->fpu_mode == '\x03')) {
    bVar1 = 1;
  }
  else {
    bVar1 = -(g_request->cpu == 4) & 2;
  }
  if ((bVar1 != 0) && (rec->op == OP_CALL)) {
    g_saved_sys_mask = g_saved_sys_mask | 3;
  }
  rec_op = rec->op;
  if (((((((rec_op == OP_NON_D2) || (rec_op == OP_NON_B8)) || (rec_op == OP_NON_C0)) ||
        ((rec_op == OP_NON_C1 || (rec_op == OP_NON_BE)))) || (rec_op == OP_NON_DC)) ||
      (((rec_op == OP_NON_CC || (rec_op == OP_NON_BC)) ||
       ((rec_op == OP_NON_D0 ||
        (((rec_op == OP_NON_D4 || (rec_op == OP_NON_BA)) || (rec_op == OP_NON_DD)))))))) ||
     (rec_op == OP_NON_C7)) {
    g_saved_sys_mask = g_saved_sys_mask | 2;
  }
  write_sua_record(g_sua_file,rec);
  switch(rec->op) {
  case OP_LABEL:
    labno = *(short *)&rec->ea1;
    sVar3 = 2;
    if ((int)labno <= *(int *)g_request->unknown_0b0 + 0xb6) {
      sVar3 = 5;
    }
    break;
  case OP_CLABEL:
    labno = *(short *)&rec->ea1;
    sVar3 = 3;
    break;
  case OP_DLABEL:
    labno = *(short *)&rec->ea1;
    sVar3 = 4;
    break;
  case OP_FLABEL:
    labno = *(short *)&rec->ea1;
    sVar3 = 1;
    break;
  default:
    goto switchD_0042ae89_default;
  }
  write_asa_record(sVar3,labno);
switchD_0042ae89_default:
  section = g_current_section;
  iVar2 = compute_record_code_size(rec);
  section->location = section->location + (short)iVar2 + pool_size;
  rec_op = rec->op;
  if ((((rec_op != OP_CASEJMP) && (rec_op != OP_CTBL)) &&
      (((rec_op != OP_CENT && ((rec_op != OP_LABEL && (rec_op != OP_FLABEL)))) &&
       (rec_op != OP_CLABEL)))) &&
     (((rec_op != OP_DLABEL && (rec_op != OP_LINE)) && (rec_op != OP_NON_10)))) {
    if (rec->ea1 != (ea *)0x0) {
      free_ea(rec->ea1);
    }
    if (rec->ea2 != (ea *)0x0) {
      free_ea(rec->ea2);
      return;
    }
  }
  return;
#undef branch_rec
}



