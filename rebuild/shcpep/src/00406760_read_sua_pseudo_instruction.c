#include "decls.h"
#include "imports.h"
#include "pep_rules.h"

// entry: 00406760
// name : read_sua_pseudo_instruction
// size : 2680
// sig  : uint read_sua_pseudo_instruction(psd * rec)


uint __cdecl read_sua_pseudo_instruction(psd *rec)

{
  unsigned char _frec_14[20];
#define local_14 (*(byte *)(_frec_14 + 0))
#define local_13 (*(byte *)(_frec_14 + 1))
#define local_12 (*(char *)(_frec_14 + 2))
#define local_11 (*(char *)(_frec_14 + 3))
#define local_10 (*(undefined2 *)(_frec_14 + 4))
#define local_e (*(undefined1 *)(_frec_14 + 6))
#define local_d (*(undefined1 *)(_frec_14 + 7))
#define local_9 (*(undefined1 *)(_frec_14 + 11))
#define local_8 (*(undefined1 *)(_frec_14 + 12))
#define local_7 (*(undefined1 *)(_frec_14 + 13))
#define local_6 (*(undefined1 *)(_frec_14 + 14))
#define n_labels (*(int *)(_frec_14 + 16))
  uint result;
  ea *operand;
  psd_op op;
  
  result = read_sua_bytes((char *)&local_14,8);
  if (result == 0) {
    return 0xffffffff;
  }
  *(byte *)&rec->filno = local_14;
  *(byte *)((int)&rec->filno + 1) = local_13;
  *(char *)&rec->linno = local_12;
  *(char *)((int)&rec->linno + 1) = local_11;
  *(char *)&rec->expno = (char)local_10;
  *(undefined1 *)((int)&rec->expno + 1) = (*(unsigned char *)((char *)&local_10 + 1));
  op = rec->op;
  *(undefined1 *)((int)&rec->expno + 2) = local_e;
  *(undefined1 *)((int)&rec->expno + 3) = local_d;
  switch(op) {
  case OP_RETURN:
    result = read_sua_label_operand(rec);
    if (result != 0xffffffff) {
      rec->flg = '\0';
      rec->tmp = PEP_RET_TMP('\x01');
      return result;
    }
    break;
  case OP_CALL:
    result = read_sua_bytes((char *)&local_14,1);
    if (result == 0) {
      return 0xffffffff;
    }
    rec->misc = local_14 & 0x80;
  case OP_JUMP:
  case OP_JUMPT:
  case OP_JUMPF:
    result = read_sua_label_operand(rec);
    if (result != 0xffffffff) {
      result = read_sua_bytes((char *)&local_14,1);
      if (result == 0) {
        return 0xffffffff;
      }
      rec->flg = '\0';
      rec->tmp = local_14;
    }
    break;
  case OP_MOV_LOC:
    result = read_sua_bytes((char *)&local_14,4);
    if (result == 0) {
      return 0xffffffff;
    }
    rec->flg = local_14 & 0xe3;
    rec->misc = local_13 & 0xc0;
    operand = alloc_zeroed(0xc);
    rec->ea1 = operand;
    if (operand == (ea *)0x0) {
      report_compiler_message(0,0,0xbcd,(char *)0x0);
    }
    operand = alloc_zeroed(0xc);
    rec->ea2 = operand;
    if (operand == (ea *)0x0) {
      report_compiler_message(0,0,0xbcd,(char *)0x0);
    }
    rec->tmp = local_11;
    if ((rec->misc & 0x80U) == 0) {
      rec->ea2->type = '\x01';
      rec->ea2->base = local_12;
      rec->ea1->base = 'l';
      result = read_sua_bytes(&local_11,1);
      if (result == 0) {
        return 0xffffffff;
      }
      result = read_sua_bytes((char *)&local_10,4);
      if (result == 0) {
        return 0xffffffff;
      }
      set_ea_disp_sign_extended(&local_10,rec->ea1,4);
      operand = rec->ea1;
      operand->type = '\x02';
      if (operand->disp == 0) goto LAB_004069f0;
    }
    else {
      rec->ea1->type = '\x01';
      rec->ea1->base = local_12;
      rec->ea2->base = 'l';
      result = read_sua_bytes(&local_11,1);
      if (result == 0) {
        return 0xffffffff;
      }
      result = read_sua_bytes((char *)&local_10,4);
      if (result == 0) {
        return 0xffffffff;
      }
      set_ea_disp_sign_extended(&local_10,rec->ea2,4);
      operand = rec->ea2;
      if (operand->disp == 0) {
        operand->type = '\x02';
        goto LAB_004069f0;
      }
    }
    operand->type = '\b';
LAB_004069f0:
    result = read_sua_bytes((char *)&local_14,4);
    if (result == 0) {
      return 0xffffffff;
    }
    result = read_sua_bytes((char *)&local_14,4);
    if (result == 0) {
      return 0xffffffff;
    }
    *(byte *)&rec->sptravel = local_14;
    *(byte *)((int)&rec->sptravel + 1) = local_13;
    *(char *)((int)&rec->sptravel + 2) = local_12;
    *(char *)((int)&rec->sptravel + 3) = local_11;
    return result;
  case OP_MOVA_LC:
    result = read_sua_bytes((char *)&local_14,0xf);
    if (result == 0) {
      return 0xffffffff;
    }
    rec->flg = local_14 & 0xe3;
    operand = alloc_zeroed(0xc);
    rec->ea1 = operand;
    if (operand == (ea *)0x0) {
      report_compiler_message(0,0,0xbcd,(char *)0x0);
    }
    operand = alloc_zeroed(0xc);
    rec->ea2 = operand;
    if (operand == (ea *)0x0) {
      report_compiler_message(0,0,0xbcd,(char *)0x0);
    }
    rec->ea2->base = local_13;
    rec->ea2->type = '\x01';
    rec->ea1->base = 'l';
    *(char *)&rec->ea1->disp = local_11;
    *(char *)((int)&rec->ea1->disp + 1) = (char)local_10;
    *(undefined1 *)((int)&rec->ea1->disp + 2) = (*(unsigned char *)((char *)&local_10 + 1));
    *(undefined1 *)((int)&rec->ea1->disp + 3) = local_e;
    operand = rec->ea1;
    operand->type = '\x02';
    if (operand->disp != 0) {
      operand->type = '\b';
    }
    *(undefined1 *)&rec->sptravel = local_9;
    *(undefined1 *)((int)&rec->sptravel + 1) = local_8;
    *(undefined1 *)((int)&rec->sptravel + 2) = local_7;
    *(undefined1 *)((int)&rec->sptravel + 3) = local_6;
    return result;
  case OP_MOVA_PC:
    result = read_sua_bytes((char *)&local_14,2);
    if (result == 0) {
      return 0xffffffff;
    }
    rec->flg = '\0';
    operand = alloc_zeroed(0xc);
    rec->ea1 = operand;
    if (operand == (ea *)0x0) {
      report_compiler_message(0,0,0xbcd,(char *)0x0);
    }
    operand = alloc_zeroed(0xc);
    rec->ea2 = operand;
    if (operand == (ea *)0x0) {
      report_compiler_message(0,0,0xbcd,(char *)0x0);
    }
    rec->ea2->base = local_14;
    rec->ea2->type = '\x01';
    rec->ea1->type = '\a';
    result = read_sua_bytes((char *)&local_14,4);
    if (result == 0) {
      return 0xffffffff;
    }
    *(byte *)&rec->ea1->disp = local_14;
    *(byte *)((int)&rec->ea1->disp + 1) = local_13;
    *(char *)((int)&rec->ea1->disp + 2) = local_12;
    *(char *)((int)&rec->ea1->disp + 3) = local_11;
    result = read_sua_bytes((char *)&n_labels,4);
    if (result == 0) {
      return 0xffffffff;
    }
    read_sua_label_refs(n_labels,rec->ea1);
    return result;
  case OP_MOVI:
    result = read_sua_bytes((char *)&local_14,3);
    if (result == 0) {
      return 0xffffffff;
    }
    rec->flg = local_14 & 0xe3;
    rec->misc = local_13 & 0x20;
    operand = alloc_zeroed(0xc);
    rec->ea1 = operand;
    if (operand == (ea *)0x0) {
      report_compiler_message(0,0,0xbcd,(char *)0x0);
    }
    operand = alloc_zeroed(0xc);
    rec->ea2 = operand;
    if (operand == (ea *)0x0) {
      report_compiler_message(0,0,0xbcd,(char *)0x0);
    }
    rec->ea2->base = local_12;
    rec->ea2->type = '\x01';
    result = read_sua_bytes(&local_11,1);
    if (result == 0) {
      return 0xffffffff;
    }
    rec->ea1->type = '\a';
    result = read_sua_bytes((char *)&local_10,4);
    if (result == 0) {
      return 0xffffffff;
    }
    *(char *)&rec->ea1->disp = (char)local_10;
    *(undefined1 *)((int)&rec->ea1->disp + 1) = (*(unsigned char *)((char *)&local_10 + 1));
    *(undefined1 *)((int)&rec->ea1->disp + 2) = local_e;
    *(undefined1 *)((int)&rec->ea1->disp + 3) = local_d;
    result = read_sua_bytes((char *)&n_labels,4);
    if (result == 0) {
      return 0xffffffff;
    }
    read_sua_label_refs(n_labels,rec->ea1);
    return result;
  case OP_MOVA_FC:
    result = read_sua_bytes((char *)&local_14,2);
    if (result == 0) {
      return 0xffffffff;
    }
    rec->flg = local_14 & 0xe3;
    operand = alloc_zeroed(0xc);
    rec->ea1 = operand;
    if (operand == (ea *)0x0) {
      report_compiler_message(0,0,0xbcd,(char *)0x0);
    }
    operand = alloc_zeroed(0xc);
    rec->ea2 = operand;
    if (operand == (ea *)0x0) {
      report_compiler_message(0,0,0xbcd,(char *)0x0);
    }
    rec->tmp = local_13 & 0xf;
    rec->ea2->type = '\x01';
    rec->ea2->base = local_13 >> 4;
    result = read_sua_bytes(&local_12,1);
    if (result == 0) {
      return 0xffffffff;
    }
    rec->ea1->type = '\a';
    result = read_sua_bytes(&local_11,4);
    if (result == 0) {
      return 0xffffffff;
    }
    *(char *)&rec->ea1->disp = local_11;
    *(char *)((int)&rec->ea1->disp + 1) = (char)local_10;
    *(undefined1 *)((int)&rec->ea1->disp + 2) = (*(unsigned char *)((char *)&local_10 + 1));
    *(undefined1 *)((int)&rec->ea1->disp + 3) = local_e;
    result = read_sua_bytes((char *)&n_labels,4);
    if (result == 0) {
      return 0xffffffff;
    }
    read_sua_label_refs(n_labels,rec->ea1);
    return result;
  case OP_NON_2C:
    result = read_sua_bytes((char *)&local_14,4);
    if (result == 0) {
      return 0xffffffff;
    }
    rec->flg = local_14 & 0xe3;
    rec->misc = local_13;
    operand = alloc_zeroed(0xc);
    rec->ea1 = operand;
    if (operand == (ea *)0x0) {
      report_compiler_message(0,0,0xbcd,(char *)0x0);
    }
    operand = alloc_zeroed(0xc);
    rec->ea2 = operand;
    if (operand == (ea *)0x0) {
      report_compiler_message(0,0,0xbcd,(char *)0x0);
    }
    rec->ea2->base = local_12;
    rec->tmp = local_11;
    rec->ea2->type = '\x01';
    result = read_sua_bytes(&local_11,1);
    if (result == 0) {
      return 0xffffffff;
    }
    rec->ea1->type = '\a';
    result = read_sua_bytes((char *)&local_10,4);
    if (result == 0) {
      return 0xffffffff;
    }
    *(char *)&rec->ea1->disp = (char)local_10;
    *(undefined1 *)((int)&rec->ea1->disp + 1) = (*(unsigned char *)((char *)&local_10 + 1));
    *(undefined1 *)((int)&rec->ea1->disp + 2) = local_e;
    *(undefined1 *)((int)&rec->ea1->disp + 3) = local_d;
    result = read_sua_bytes((char *)&n_labels,4);
    if (result == 0) {
      return 0xffffffff;
    }
    read_sua_label_refs(n_labels,rec->ea1);
    return result;
  default:
    report_compiler_message(0,0,0x131f,(char *)0x0);
    return result;
  case OP_NON_2E:
    result = read_sua_bytes((char *)&local_14,3);
    if (result == 0) {
      return 0xffffffff;
    }
    rec->flg = local_14 & 0xe3;
    operand = alloc_zeroed(0xc);
    rec->ea1 = operand;
    if (operand == (ea *)0x0) {
      report_compiler_message(0,0,0xbcd,(char *)0x0);
    }
    rec->ea1->base = local_13;
    rec->ea1->type = '\x01';
    operand = alloc_zeroed(0xc);
    rec->ea2 = operand;
    if (operand == (ea *)0x0) {
      report_compiler_message(0,0,0xbcd,(char *)0x0);
    }
    rec->ea2->base = local_12;
    rec->ea2->type = '\x01';
    return result;
  case OP_NON_30:
    result = read_sua_bytes((char *)&local_14,1);
    if (result == 0) {
      return 0xffffffff;
    }
    rec->flg = '\0';
    operand = alloc_zeroed(0xc);
    rec->ea1 = operand;
    if (operand == (ea *)0x0) {
      report_compiler_message(0,0,0xbcd,(char *)0x0);
    }
    rec->ea1->base = local_14;
    rec->ea1->type = '\x04';
    operand = alloc_zeroed(0xc);
    rec->ea2 = operand;
    if (operand == (ea *)0x0) {
      report_compiler_message(0,0,0xbcd,(char *)0x0);
    }
    rec->ea2->base = '`';
    rec->ea2->type = '\x01';
    return result;
  case OP_NON_31:
    result = read_sua_bytes((char *)&local_14,1);
    if (result == 0) {
      return 0xffffffff;
    }
    rec->flg = '\0';
    operand = alloc_zeroed(0xc);
    rec->ea1 = operand;
    if (operand == (ea *)0x0) {
      report_compiler_message(0,0,0xbcd,(char *)0x0);
    }
    rec->ea1->base = '`';
    rec->ea1->type = '\x01';
    operand = alloc_zeroed(0xc);
    rec->ea2 = operand;
    if (operand == (ea *)0x0) {
      report_compiler_message(0,0,0xbcd,(char *)0x0);
    }
    rec->ea2->base = local_14;
    rec->ea2->type = '\x02';
    return result;
  }
  return result;
#undef local_14
#undef local_13
#undef local_12
#undef local_11
#undef local_10
#undef local_e
#undef local_d
#undef local_9
#undef local_8
#undef local_7
#undef local_6
#undef n_labels
}



