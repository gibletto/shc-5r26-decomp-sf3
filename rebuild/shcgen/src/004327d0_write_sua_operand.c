#include "decls.h"
#include "imports.h"

// entry: 004327d0
// name : write_sua_operand
// size : 699
// sig  : void write_sua_operand(FILE * out, ea * op, char size)


int __cdecl write_sua_operand(FILE *out,ea *op,char size)

{
  unsigned char _frec_8[8];
#define reg_code (*(char *)(_frec_8 + 0))
#define byte_val (*(byte *)(_frec_8 + 1))
#define word_val (*(undefined2 *)(_frec_8 + 2))
#define local_4 (*(int *)(_frec_8 + 4))
  byte kind;
  short msgno;
  char *buf;
  int max_disp;
  byte *bytes;
  byte scale;
  uint uVar1;
  
  write_sua_bytes(out,(char *)op,1);
  switch(op->type & 0x1f) {
  case 1:
  case 2:
  case 3:
  case 4:
  case 8:
  case 0xf:
  case 0x10:
    buf = &op->base;
    break;
  case 5:
    reg_code = op->base + -0x61;
    buf = &reg_code;
    break;
  case 6:
    reg_code = op->base + -100;
    buf = &reg_code;
    break;
  default:
    goto switchD_004327ff_caseD_7;
  }
  write_sua_bytes(out,buf,1);
switchD_004327ff_caseD_7:
  kind = op->type & 0x1f;
  if ((kind == 8) || (kind == 10)) {
    if (size == '\0') {
      scale = 0;
    }
    else if (size == '\x01') {
      scale = 1;
    }
    else {
      scale = (byte)local_4;
      if (size == '\x02') {
        scale = 2;
      }
    }
    if ((kind == 2) || (kind == 8)) {
      max_disp = 0xf;
    }
    else {
      max_disp = 0xff;
    }
    uVar1 = op->disp;
    if ((((int)uVar1 < 0) || (max_disp << (scale & 0x1f) < (int)uVar1)) ||
       (op->labels != (label_ref *)0x0)) {
      report_compiler_message(g_sua_filno,(uint)g_sua_linno,0x1311,(char *)0x0);
    }
    else if (((1 << (scale & 0x1f)) - 1U & uVar1) == 0) {
      word_val = (undefined2)uVar1;
      write_sua_bytes(out,(char *)&word_val,2);
    }
    else {
      report_compiler_message(g_sua_filno,(uint)g_sua_linno,0xc1c,(char *)0x0);
    }
  }
  else if (kind == 0xb) {
    if (size == '\0') {
      (*(unsigned char *)((char *)&local_4 + 0)) = 0;
    }
    else if (size == '\x01') {
      (*(unsigned char *)((char *)&local_4 + 0)) = 1;
    }
    else if (size == '\x02') {
      (*(unsigned char *)((char *)&local_4 + 0)) = 2;
    }
    if (op->labels == (label_ref *)0x0) {
      uVar1 = op->disp;
      if (((int)uVar1 < 0) || (0xff << ((byte)local_4 & 0x1f) < (int)uVar1)) goto LAB_00432996;
      if (((1 << ((byte)local_4 & 0x1f)) - 1U & uVar1) == 0) goto LAB_004329be;
      msgno = 0xc1c;
LAB_004329a5:
      report_compiler_message(g_sua_filno,(uint)g_sua_linno,msgno,(char *)0x0);
    }
    else {
      msgno = count_label_ref_markers(op->labels);
      if (msgno != 1) {
LAB_00432996:
        msgno = 0x1311;
        goto LAB_004329a5;
      }
    }
LAB_004329be:
    local_4 = op->disp;
    write_sua_bytes(out,(char *)&local_4,4);
    write_sua_label_list(out,op->labels);
  }
  kind = op->type & 0x1f;
  if (kind != 7) {
    if (kind == 9) {
      byte_val = op->base << 4 | op->index;
      write_sua_bytes(out,(char *)&byte_val,1);
      return;
    }
    if (kind == 0xc) {
      write_sua_bytes(out,&op->index,1);
    }
    return;
  }
  if (size == '\0') {
    byte_val = (byte)op->disp;
    uVar1 = 1;
    bytes = &byte_val;
  }
  else if (size == '\x01') {
    uVar1 = 2;
    word_val = (undefined2)op->disp;
    bytes = (byte *)&word_val;
  }
  else {
    if (size != '\x02') goto LAB_00432a35;
    local_4 = op->disp;
    uVar1 = 4;
    bytes = (byte *)&local_4;
  }
  write_sua_bytes(out,(char *)bytes,uVar1);
LAB_00432a35:
  write_sua_label_list(out,op->labels);
  return;
#undef reg_code
#undef byte_val
#undef word_val
#undef local_4
}



