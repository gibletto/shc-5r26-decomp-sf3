#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_sub_linno
#define g_sub_linno (*(unsigned short *)(g_sd + 0x5360))


// entry: 0041b9b0
// name : write_sub_instruction_record
// size : 1338
// sig  : void write_sub_instruction_record(FILE * out, psd * rec)


int __cdecl write_sub_instruction_record(FILE *out,psd *rec)

{
  unsigned char _frec_2[2];
#define tmp_reg (*(char *)(_frec_2 + 0))
#define reg (*(byte *)(_frec_2 + 1))
  byte kind2;
  byte bVar1;
  short msgno;
  ea **ea1_slot;
  psd_op op;
  ea *operand1;
  ea *operand2;
  
  g_sub_filno = rec->filno;
  g_sub_linno = rec->linno;
  write_sub_bytes(out,(char *)&rec->filno,2);
  write_sub_bytes(out,(char *)&rec->linno,2);
  if (rec->op == OP_ENTER) {
    return;
  }
  if (rec->op == OP_EXIT) {
    return;
  }
  write_sub_bytes(out,(char *)&rec->expno,4);
  op = rec->op;
  switch(op) {
  case OP_RETURN:
  case OP_CALL:
  case OP_JUMP:
  case OP_JUMPT:
  case OP_JUMPF:
    if (op == OP_CALL) {
      write_sub_bytes(out,&rec->misc,1);
    }
    operand1 = rec->ea1;
    if (((operand1 == (ea *)0x0) || ((operand1->type & 0x1f) != 7)) ||
       (operand1->labels == (label_ref *)0x0)) {
      report_compiler_message(g_sub_filno,(uint)g_sub_linno,0x1313,(char *)0x0);
      return;
    }
    write_sub_bytes(out,(char *)&operand1->labels->labno1,2);
    if (rec->op == OP_RETURN) {
      return;
    }
    if (rec->tmp != -1) {
      write_sub_bytes(out,&rec->tmp,1);
      return;
    }
    report_compiler_message(g_sub_filno,(uint)g_sub_linno,0x1314,(char *)0x0);
    return;
  case OP_MOV_LOC:
  case OP_MOVA_LC:
    break;
  case OP_MOVA_PC:
  case OP_MOVI:
  case OP_MOVA_FC:
    if (((rec->ea1 == (ea *)0x0) || (rec->ea2 == (ea *)0x0)) ||
       (((rec->ea1->type & 0x1f) != 7 || ((rec->ea2->type & 0x1f) != 1)))) {
      report_compiler_message(g_sub_filno,(uint)g_sub_linno,0x1317,(char *)0x0);
    }
    if ((rec->op == OP_MOVI) || (rec->op == OP_MOVA_FC)) {
      write_sub_bytes(out,&rec->flg,1);
    }
    if (rec->op == OP_MOVI) {
      write_sub_bytes(out,&rec->misc,1);
    }
    reg = rec->ea2->base;
    if (rec->op == OP_MOVA_FC) {
      reg = reg << 4 | rec->tmp & 0xfU;
    }
    write_sub_bytes(out,(char *)&reg,1);
    bVar1 = 2;
    if (rec->op == OP_MOVI) {
      bVar1 = rec->flg & 3;
    }
    write_sub_operand(out,rec->ea1,bVar1);
    return;
  case OP_NON_2C:
    if (((((rec->ea1 == (ea *)0x0) || (operand1 = rec->ea2, operand1 == (ea *)0x0)) ||
         ((rec->ea1->type & 0x1f) != 7)) ||
        (((operand1->type & 0x1f) != 1 || (operand1->base < '\x10')))) ||
       (('\x1f' < operand1->base || (rec->tmp == -1)))) {
      report_compiler_message(g_sub_filno,(uint)g_sub_linno,0x1317,(char *)0x0);
    }
    write_sub_bytes(out,&rec->flg,1);
    write_sub_bytes(out,&rec->misc,1);
    write_sub_bytes(out,&rec->ea2->base,1);
    write_sub_bytes(out,&rec->tmp,1);
    write_sub_operand(out,rec->ea1,'\x02');
    return;
  default:
    report_compiler_message(g_sub_filno,(uint)g_sub_linno,0x1318,(char *)0x0);
    return;
  case OP_NON_2E:
    operand1 = rec->ea1;
    if ((((operand1 == (ea *)0x0) || (operand2 = rec->ea2, operand2 == (ea *)0x0)) ||
        (((operand1->type & 0x1f) != 1 ||
         (('\x0e' < operand1->base || ((operand2->type & 0x1f) != 1)))))) ||
       ('\x0e' < operand2->base)) {
      report_compiler_message(g_sub_filno,(uint)g_sub_linno,0x1317,(char *)0x0);
    }
    write_sub_bytes(out,&rec->flg,1);
    write_sub_bytes(out,&rec->ea1->base,1);
    write_sub_bytes(out,&rec->ea2->base,1);
    return;
  case OP_NON_30:
  case OP_NON_31:
    ea1_slot = &rec->ea1;
    if (op == OP_NON_30) {
      if (((*ea1_slot != (ea *)0x0) && (rec->ea2 != (ea *)0x0)) && (((*ea1_slot)->type & 0x1f) == 4)
         ) goto LAB_0041beb8;
    }
    else if (((*ea1_slot != (ea *)0x0) && (rec->ea2 != (ea *)0x0)) &&
            ((bVar1 = rec->ea2->type & 0x1f, bVar1 == 8 || (bVar1 == 2)))) goto LAB_0041beb8;
    report_compiler_message(g_sub_filno,(uint)g_sub_linno,0x1317,(char *)0x0);
LAB_0041beb8:
    if (rec->op != OP_NON_30) {
      write_sub_bytes(out,&rec->ea2->base,1);
      return;
    }
    write_sub_bytes(out,&(*ea1_slot)->base,1);
    return;
  }
  write_sub_bytes(out,&rec->flg,1);
  if (rec->op == OP_MOV_LOC) {
    write_sub_bytes(out,&rec->misc,1);
  }
  operand1 = rec->ea1;
  if (((operand1 == (ea *)0x0) || (operand2 = rec->ea2, operand2 == (ea *)0x0)) ||
     ((rec->op == OP_MOV_LOC && (((rec->misc & 0x80U) == 0 && (rec->tmp == -1)))))) {
    msgno = 0x1315;
  }
  else {
    bVar1 = operand1->type & 0x1f;
    if ((bVar1 == 1) &&
       (((kind2 = operand2->type & 0x1f, kind2 == 2 || (kind2 == 8)) && (operand2->base == 'l')))) {
      reg = operand1->base;
      tmp_reg = rec->tmp;
      g_scratch_ea.disp = operand2->disp;
      goto LAB_0041bc0c;
    }
    if ((((operand2->type & 0x1f) == 1) && ((bVar1 == 2 || (bVar1 == 8)))) &&
       (operand1->base == 'l')) {
      reg = operand2->base;
      if (rec->op != OP_MOVA_LC) {
        tmp_reg = rec->tmp;
      }
      g_scratch_ea.disp = operand1->disp;
      goto LAB_0041bc0c;
    }
    msgno = 0x1316;
  }
  report_compiler_message(g_sub_filno,(uint)g_sub_linno,msgno,(char *)0x0);
LAB_0041bc0c:
  write_sub_bytes(out,(char *)&reg,1);
  if (rec->op == OP_MOV_LOC) {
    write_sub_bytes(out,&tmp_reg,1);
  }
  write_sub_operand(out,&g_scratch_ea,'\x02');
  write_sub_bytes(out,(char *)&rec->sptravel,4);
  return;
#undef tmp_reg
#undef reg
}



