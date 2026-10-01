#include "decls.h"
#include "imports.h"
#include "pep_rules.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_stage_flags
#define g_stage_flags (*(unsigned char *)(g_sd + 0x6d64))


// entry: 00413850
// name : count_common_tail_records
// size : 812
// sig  : int count_common_tail_records(code_node * block_a, code_node * block_b, psd * * tail_a, psd * * tail_b, short mode)


int __cdecl
count_common_tail_records
          (code_node *block_a,code_node *block_b,psd **tail_a,psd **tail_b,short mode)

{
  char cVar1;
  short sVar2;
  psd *rec;
  psd *rec_b;
  psd *rec_a;
  int count;
  int new_count;
  uchar jump_tmp_reg;
  psd *local_c;
  psd *local_8;
  
  count = 0;
#if SHC_REBUILD_UPDATED
  xjump_tail[0] = 0;
#endif
  local_8 = (psd *)0x0;
  local_c = (psd *)0x0;
  if (((byte)g_stage_flags & 0x10) != 0) {
    _printf(s_dc_cmp_start__004277e0);
  }
  rec = find_block_final_record(block_a);
  rec_b = find_block_final_record(block_b);
  if ((rec == (psd *)0x0) ||
     (((rec->op != OP_JUMP && (rec->op != OP_RETURN)) || (rec->ea1->labels == (label_ref *)0x0)))) {
    return 0;
  }
  rec_a = find_previous_psd_record(block_a,rec);
  if (mode == 1) {
    if (((rec_b == (psd *)0x0) || (rec_b->op == OP_JUMP)) || (rec_b->op == OP_RETURN)) {
      return 0;
    }
    jump_tmp_reg = rec->tmp;
  }
  else {
    if (mode != 2) {
      return 0;
    }
    if (((rec_b == (psd *)0x0) || ((rec_b->op != OP_JUMP && (rec_b->op != OP_RETURN)))) ||
       (rec_b->ea1->labels == (label_ref *)0x0)) {
      return 0;
    }
    jump_tmp_reg = rec_b->tmp;
    rec_b = find_previous_psd_record(block_b,rec_b);
  }
  while ((((((new_count = count, rec_b != (psd *)0x0 && (rec_a != (psd *)0x0)) &&
            (rec_a->op == rec_b->op)) &&
           ((rec_b->flg == rec_a->flg && (rec_b->misc == rec_a->misc)))) &&
          (rec_b->tmp == rec_a->tmp)) && (rec_b->sptravel == rec_a->sptravel))) {
    switch(rec_b->op) {
    case OP_NON_10:
      if (((rec_b->filno == rec_a->filno) && (rec_b->linno == rec_a->linno)) &&
         ((rec_b->ea1 == rec_a->ea1 && (rec_b->ea2 == rec_a->ea2)))) {
LAB_00413ae9:
        new_count = count + 1;
        XJ_TAIL((unsigned char *)rec_b);
        local_c = rec_a;
        local_8 = rec_b;
      }
      break;
    case OP_CASEJMP:
      if ((((rec_b->filno == rec_a->filno) && (rec_b->linno == rec_a->linno)) &&
          (rec_b->ea1 == rec_a->ea1)) && (rec_b->ea2 == rec_a->ea2)) goto LAB_00413ae9;
      break;
    default:
      sVar2 = common_code_ea_equal(rec_b->ea1,rec_a->ea1);
      if ((sVar2 == 1) &&
         (((sVar2 = common_code_ea_equal(rec_b->ea2,rec_a->ea2), sVar2 == 1 &&
           (cVar1 = operand_uses_register(rec_a,jump_tmp_reg,'\x01'), cVar1 == '\0')) &&
          (cVar1 = operand_uses_register(rec_a,jump_tmp_reg,'\x02'), cVar1 == '\0'))))
      goto LAB_00413ae9;
      break;
    case OP_CTBL:
    case OP_CENT:
      if (((rec_b->filno == rec_a->filno) && (rec_b->linno == rec_a->linno)) &&
         ((*(short *)&rec_b->ea1 == *(short *)&rec_a->ea1 &&
          ((*(short *)((int)&rec_b->ea1 + 2) == *(short *)((int)&rec_a->ea1 + 2) &&
           (rec_b->ea2 == rec_a->ea2)))))) goto LAB_00413ae9;
      break;
    case OP_LABEL:
    case OP_CLABEL:
    case OP_DLABEL:
    case OP_FLABEL:
      if (((*(short *)&rec_b->ea1 == *(short *)&rec_a->ea1) &&
          (*(short *)((int)&rec_b->ea1 + 2) == *(short *)((int)&rec_a->ea1 + 2))) &&
         (rec_b->ea2 == rec_a->ea2)) goto LAB_00413ae9;
      break;
    case OP_LINE:
      if (((*(char *)&rec_b->ea1 == *(char *)&rec_a->ea1) &&
          (*(char *)((int)&rec_b->ea1 + 1) == *(char *)((int)&rec_a->ea1 + 1))) &&
         ((*(short *)((int)&rec_b->ea1 + 2) == *(short *)((int)&rec_a->ea1 + 2) &&
          (rec_b->ea2 == rec_a->ea2)))) goto LAB_00413ae9;
      break;
    case OP_SWBGN:
    case OP_SWEND:
      break;
    }
    if (count == new_count) break;
    rec_a = find_previous_psd_record(block_a,rec_a);
    rec_b = find_previous_psd_record(block_b,rec_b);
    count = new_count;
  }
  *tail_a = local_c;
  *tail_b = local_8;
  if (((byte)g_stage_flags & 0x10) != 0) {
    _printf(s_rp___08lx__r1___08lx_004277c8,tail_a,tail_b);
    _printf(s_dc_cmp_end__common_code_number___004277a0,new_count);
  }
  return new_count;
}



