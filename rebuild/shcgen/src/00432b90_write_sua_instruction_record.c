#include "decls.h"
#include "imports.h"

// entry: 00432b90
// name : write_sua_instruction_record
// size : 1338
// sig  : void write_sua_instruction_record(FILE * out, psd * rec)


int __cdecl write_sua_instruction_record(FILE *out,psd *rec)

{
  unsigned char _frec_2[2];
#define tmp_byte (*(char *)(_frec_2 + 0))
#define reg_byte (*(byte *)(_frec_2 + 1))
  byte kind2;
  byte bVar1;
  short msgno;
  ea **ea1_slot;
  psd_op op;
  ea *opnd1;
  ea *opnd2;
  
  g_sua_filno = rec->filno;
  g_sua_linno = rec->linno;
  write_sua_bytes(out,(char *)&rec->filno,2);
  write_sua_bytes(out,(char *)&rec->linno,2);
  if (rec->op == OP_ENTER) {
    return;
  }
  if (rec->op == OP_EXIT) {
    return;
  }
  write_sua_bytes(out,(char *)&rec->expno,4);
  op = rec->op;
  switch(op) {
  case OP_RETURN:
  case OP_CALL:
  case OP_JUMP:
  case OP_JUMPT:
  case OP_JUMPF:
    if (op == OP_CALL) {
      write_sua_bytes(out,&rec->misc,1);
    }
    opnd1 = rec->ea1;
    if (((opnd1 == (ea *)0x0) || ((opnd1->type & 0x1f) != 7)) || (opnd1->labels == (label_ref *)0x0)
       ) {
      report_compiler_message(g_sua_filno,(uint)g_sua_linno,0x1313,(char *)0x0);
      return;
    }
    write_sua_bytes(out,(char *)&opnd1->labels->labno1,2);
    if (rec->op == OP_RETURN) {
      return;
    }
    if (rec->tmp != -1) {
      write_sua_bytes(out,&rec->tmp,1);
      return;
    }
    report_compiler_message(g_sua_filno,(uint)g_sua_linno,0x1314,(char *)0x0);
    return;
  case OP_MOV_LOC:
  case OP_MOVA_LC:
    break;
  case OP_MOVA_PC:
  case OP_MOVI:
  case OP_MOVA_FC:
    if (((rec->ea1 == (ea *)0x0) || (rec->ea2 == (ea *)0x0)) ||
       (((rec->ea1->type & 0x1f) != 7 || ((rec->ea2->type & 0x1f) != 1)))) {
      report_compiler_message(g_sua_filno,(uint)g_sua_linno,0x1317,(char *)0x0);
    }
    if ((rec->op == OP_MOVI) || (rec->op == OP_MOVA_FC)) {
      write_sua_bytes(out,&rec->flg,1);
    }
    if (rec->op == OP_MOVI) {
      write_sua_bytes(out,&rec->misc,1);
    }
    reg_byte = rec->ea2->base;
    if (rec->op == OP_MOVA_FC) {
      reg_byte = reg_byte << 4 | rec->tmp & 0xfU;
    }
    write_sua_bytes(out,(char *)&reg_byte,1);
    bVar1 = 2;
    if (rec->op == OP_MOVI) {
      bVar1 = rec->flg & 3;
    }
    write_sua_operand(out,rec->ea1,bVar1);
    return;
  case OP_NON_2C:
    if (((((rec->ea1 == (ea *)0x0) || (opnd1 = rec->ea2, opnd1 == (ea *)0x0)) ||
         ((rec->ea1->type & 0x1f) != 7)) || (((opnd1->type & 0x1f) != 1 || (opnd1->base < '\x10'))))
       || (('\x1f' < opnd1->base || (rec->tmp == -1)))) {
      report_compiler_message(g_sua_filno,(uint)g_sua_linno,0x1317,(char *)0x0);
    }
    write_sua_bytes(out,&rec->flg,1);
    write_sua_bytes(out,&rec->misc,1);
    write_sua_bytes(out,&rec->ea2->base,1);
    write_sua_bytes(out,&rec->tmp,1);
    write_sua_operand(out,rec->ea1,'\x02');
    return;
  default:
    report_compiler_message(g_sua_filno,(uint)g_sua_linno,0x1318,(char *)0x0);
    return;
  case OP_NON_2E:
    opnd1 = rec->ea1;
    if ((((opnd1 == (ea *)0x0) || (opnd2 = rec->ea2, opnd2 == (ea *)0x0)) ||
        (((opnd1->type & 0x1f) != 1 || (('\x0e' < opnd1->base || ((opnd2->type & 0x1f) != 1)))))) ||
       ('\x0e' < opnd2->base)) {
      report_compiler_message(g_sua_filno,(uint)g_sua_linno,0x1317,(char *)0x0);
    }
    write_sua_bytes(out,&rec->flg,1);
    write_sua_bytes(out,&rec->ea1->base,1);
    write_sua_bytes(out,&rec->ea2->base,1);
    return;
  case OP_NON_30:
  case OP_NON_31:
    ea1_slot = &rec->ea1;
    if (op == OP_NON_30) {
      if (((*ea1_slot != (ea *)0x0) && (rec->ea2 != (ea *)0x0)) && (((*ea1_slot)->type & 0x1f) == 4)
         ) goto LAB_00433098;
    }
    else if (((*ea1_slot != (ea *)0x0) && (rec->ea2 != (ea *)0x0)) &&
            ((bVar1 = rec->ea2->type & 0x1f, bVar1 == 8 || (bVar1 == 2)))) goto LAB_00433098;
    report_compiler_message(g_sua_filno,(uint)g_sua_linno,0x1317,(char *)0x0);
LAB_00433098:
    if (rec->op != OP_NON_30) {
      write_sua_bytes(out,&rec->ea2->base,1);
      return;
    }
    write_sua_bytes(out,&(*ea1_slot)->base,1);
    return;
  }
  write_sua_bytes(out,&rec->flg,1);
  if (rec->op == OP_MOV_LOC) {
    write_sua_bytes(out,&rec->misc,1);
  }
  opnd1 = rec->ea1;
  if (((opnd1 == (ea *)0x0) || (opnd2 = rec->ea2, opnd2 == (ea *)0x0)) ||
     ((rec->op == OP_MOV_LOC && (((rec->misc & 0x80U) == 0 && (rec->tmp == -1)))))) {
    msgno = 0x1315;
  }
  else {
    bVar1 = opnd1->type & 0x1f;
    if ((bVar1 == 1) &&
       (((kind2 = opnd2->type & 0x1f, kind2 == 2 || (kind2 == 8)) && (opnd2->base == 'l')))) {
      reg_byte = opnd1->base;
      tmp_byte = rec->tmp;
      g_sua_frame_disp_operand.disp = opnd2->disp;
      goto LAB_00432dec;
    }
    if ((((opnd2->type & 0x1f) == 1) && ((bVar1 == 2 || (bVar1 == 8)))) && (opnd1->base == 'l')) {
      reg_byte = opnd2->base;
      if (rec->op != OP_MOVA_LC) {
        tmp_byte = rec->tmp;
      }
      g_sua_frame_disp_operand.disp = opnd1->disp;
      goto LAB_00432dec;
    }
    msgno = 0x1316;
  }
  report_compiler_message(g_sua_filno,(uint)g_sua_linno,msgno,(char *)0x0);
LAB_00432dec:
  write_sua_bytes(out,(char *)&reg_byte,1);
  if (rec->op == OP_MOV_LOC) {
    write_sua_bytes(out,&tmp_byte,1);
  }
  write_sua_operand(out,&g_sua_frame_disp_operand,'\x02');
  write_sua_bytes(out,(char *)&rec->sptravel,4);
  return;
#undef tmp_byte
#undef reg_byte
}



