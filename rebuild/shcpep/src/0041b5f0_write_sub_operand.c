#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_sub_linno
#define g_sub_linno (*(unsigned short *)(g_sd + 0x5360))


// entry: 0041b5f0
// name : write_sub_operand
// size : 699
// sig  : void write_sub_operand(FILE * out, ea * op, char size)


int __cdecl write_sub_operand(FILE *out,ea *op,char size)

{
  unsigned char _frec_8[8];
#define reg_code (*(char *)(_frec_8 + 0))
#define out_byte (*(byte *)(_frec_8 + 1))
#define out_word (*(undefined2 *)(_frec_8 + 2))
#define local_4 (*(int *)(_frec_8 + 4))
  byte kind;
  short sVar1;
  char *buf;
  int disp_limit;
  byte *imm_buf;
  byte shift;
  uint uVar2;
  
  write_sub_bytes(out,(char *)op,1);
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
    goto switchD_0041b61f_caseD_7;
  }
  write_sub_bytes(out,buf,1);
switchD_0041b61f_caseD_7:
  kind = op->type & 0x1f;
  if ((kind == 8) || (kind == 10)) {
    if (size == '\0') {
      shift = 0;
    }
    else if (size == '\x01') {
      shift = 1;
    }
    else {
      shift = (byte)local_4;
      if (size == '\x02') {
        shift = 2;
      }
    }
    if ((kind == 2) || (kind == 8)) {
      disp_limit = 0xf;
    }
    else {
      disp_limit = 0xff;
    }
    uVar2 = op->disp;
    if ((((int)uVar2 < 0) || (disp_limit << (shift & 0x1f) < (int)uVar2)) ||
       (op->labels != (label_ref *)0x0)) {
      report_compiler_message(g_sub_filno,(uint)g_sub_linno,0x1311,(char *)0x0);
    }
    else if (((1 << (shift & 0x1f)) - 1U & uVar2) == 0) {
      out_word = (undefined2)uVar2;
      write_sub_bytes(out,(char *)&out_word,2);
    }
    else {
      report_compiler_message(g_sub_filno,(uint)g_sub_linno,0xc1c,(char *)0x0);
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
      uVar2 = op->disp;
      if (((int)uVar2 < 0) || (0xff << ((byte)local_4 & 0x1f) < (int)uVar2)) goto LAB_0041b7b6;
      if (((1 << ((byte)local_4 & 0x1f)) - 1U & uVar2) == 0) goto LAB_0041b7de;
      sVar1 = 0xc1c;
LAB_0041b7c5:
      report_compiler_message(g_sub_filno,(uint)g_sub_linno,sVar1,(char *)0x0);
    }
    else {
      sVar1 = count_label_ref_markers(op->labels);
      if (sVar1 != 1) {
LAB_0041b7b6:
        sVar1 = 0x1311;
        goto LAB_0041b7c5;
      }
    }
LAB_0041b7de:
    local_4 = op->disp;
    write_sub_bytes(out,(char *)&local_4,4);
    write_sub_label_list(out,op->labels);
  }
  kind = op->type & 0x1f;
  if (kind != 7) {
    if (kind == 9) {
      out_byte = op->base << 4 | op->index;
      write_sub_bytes(out,(char *)&out_byte,1);
      return;
    }
    if (kind == 0xc) {
      write_sub_bytes(out,&op->index,1);
    }
    return;
  }
  if (size == '\0') {
    out_byte = (byte)op->disp;
    uVar2 = 1;
    imm_buf = &out_byte;
  }
  else if (size == '\x01') {
    uVar2 = 2;
    out_word = (undefined2)op->disp;
    imm_buf = (byte *)&out_word;
  }
  else {
    if (size != '\x02') goto LAB_0041b855;
    local_4 = op->disp;
    uVar2 = 4;
    imm_buf = (byte *)&local_4;
  }
  write_sub_bytes(out,(char *)imm_buf,uVar2);
LAB_0041b855:
  write_sub_label_list(out,op->labels);
  return;
#undef reg_code
#undef out_byte
#undef out_word
#undef local_4
}



