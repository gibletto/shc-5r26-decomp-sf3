#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_sua_read_file
#define g_sua_read_file (*(FILE * *)(g_sd + 0x5238))


// entry: 004062b0
// name : read_sua_record_body
// size : 1076
// sig  : uint read_sua_record_body(FILE * in, psd * rec, uchar op)


uint __cdecl read_sua_record_body(FILE *in,psd *rec,uchar op)

{
  unsigned char _frec_10[16];
#define local_10 (*(char *)(_frec_10 + 0))
#define local_f (*(undefined1 *)(_frec_10 + 1))
#define local_e (*(undefined1 *)(_frec_10 + 2))
#define local_d (*(undefined1 *)(_frec_10 + 3))
#define local_c (*(undefined1 *)(_frec_10 + 4))
#define local_b (*(undefined1 *)(_frec_10 + 5))
#define local_a (*(undefined1 *)(_frec_10 + 6))
#define local_9 (*(undefined1 *)(_frec_10 + 7))
#define local_8 (*(byte *)(_frec_10 + 8))
#define local_7 (*(byte *)(_frec_10 + 9))
#define local_6 (*(char *)(_frec_10 + 10))
#define local_5 (*(undefined1 *)(_frec_10 + 11))
#define local_4 (*(undefined1 *)(_frec_10 + 12))
#define local_3 (*(undefined1 *)(_frec_10 + 13))
#define local_2 (*(undefined1 *)(_frec_10 + 14))
#define local_1 (*(undefined1 *)(_frec_10 + 15))
  uint result;
  
  g_sua_read_file = in;
  result = 0;
  switch(*(undefined2 *)(&g_sua_op_format + (uint)op * 2)) {
  case 1:
  case 7:
    break;
  case 2:
    result = read_sua_bytes(&local_10,0x10);
    if (result != 0) {
      *(char *)&rec->expno = local_10;
      *(undefined1 *)((int)&rec->expno + 1) = local_f;
      *(undefined1 *)((int)&rec->expno + 2) = local_e;
      *(undefined1 *)((int)&rec->expno + 3) = local_d;
      *(undefined1 *)&rec->filno = local_c;
      *(undefined1 *)((int)&rec->filno + 1) = local_b;
      *(undefined1 *)&rec->linno = local_a;
      *(undefined1 *)((int)&rec->linno + 1) = local_9;
      *(byte *)&rec->ea1 = local_8;
      *(byte *)((int)&rec->ea1 + 1) = local_7;
      *(char *)((int)&rec->ea1 + 2) = local_6;
      *(undefined1 *)((int)&rec->ea1 + 3) = local_5;
      *(undefined1 *)&rec->ea2 = local_4;
      *(undefined1 *)((int)&rec->ea2 + 1) = local_3;
      *(undefined1 *)((int)&rec->ea2 + 2) = local_2;
      *(undefined1 *)((int)&rec->ea2 + 3) = local_1;
      return result;
    }
    return 0xffffffff;
  case 3:
    result = read_sua_bytes(&local_10,4);
    if (result != 0) {
      *(char *)&rec->filno = local_10;
      *(undefined1 *)((int)&rec->filno + 1) = local_f;
      *(undefined1 *)((int)&rec->linno + 1) = local_d;
      *(undefined1 *)&rec->linno = local_e;
      return result;
    }
    return 0xffffffff;
  case 4:
    result = read_sua_bytes(&local_10,2);
    if (result != 0) {
      *(char *)&rec->ea1 = local_10;
      *(undefined1 *)((int)&rec->ea1 + 1) = local_f;
      return result;
    }
    return 0xffffffff;
  case 5:
    result = read_sua_bytes(&local_10,6);
    if (result != 0) {
      *(char *)&rec->ea1 = local_10;
      *(undefined1 *)((int)&rec->ea1 + 1) = local_f;
      *(undefined1 *)&rec->sptravel = local_e;
      *(undefined1 *)((int)&rec->sptravel + 1) = local_d;
      *(undefined1 *)((int)&rec->sptravel + 2) = local_c;
      *(undefined1 *)((int)&rec->sptravel + 3) = local_b;
      return result;
    }
    return 0xffffffff;
  case 6:
    result = read_sua_bytes(&local_10,5);
    if (result != 0) {
      *(char *)&rec->filno = local_10;
      *(undefined1 *)((int)&rec->filno + 1) = local_f;
      *(undefined1 *)&rec->linno = local_e;
      *(undefined1 *)((int)&rec->linno + 1) = local_d;
      *(undefined1 *)&rec->ea1 = local_c;
      return result;
    }
    return 0xffffffff;
  case 8:
    result = read_sua_bytes(&local_10,0xb);
    if (result == 0) {
      return 0xffffffff;
    }
    *(char *)&rec->filno = local_10;
    *(undefined1 *)((int)&rec->filno + 1) = local_f;
    *(undefined1 *)&rec->linno = local_e;
    *(undefined1 *)((int)&rec->linno + 1) = local_d;
    *(undefined1 *)&rec->expno = local_c;
    *(undefined1 *)((int)&rec->expno + 1) = local_b;
    *(undefined1 *)((int)&rec->expno + 2) = local_a;
    *(undefined1 *)((int)&rec->expno + 3) = local_9;
    rec->flg = local_8 & 0xe3;
    rec->misc = local_7 & 0xa0;
    if (local_6 == '\0') {
      rec->ea1 = (ea *)0x0;
      rec->ea2 = (ea *)0x0;
      return result;
    }
    if (local_6 == '\x01') {
      result = read_sua_operand(rec,1);
      if (result != 0xffffffff) {
        rec->ea2 = (ea *)0x0;
        return result;
      }
    }
    else {
      if (local_6 != '\x02') {
        report_compiler_message(0,0,0x131e,(char *)0x0);
        return result;
      }
      result = read_sua_operand(rec,1);
      if (result != 0xffffffff) {
        result = read_sua_operand(rec,2);
        return result;
      }
    }
    break;
  case 9:
    result = read_sua_pseudo_instruction(rec);
    return result;
  case 10:
    result = read_sua_bytes(&local_10,4);
    if (result != 0) {
      *(char *)&rec->filno = local_10;
      *(undefined1 *)((int)&rec->filno + 1) = local_f;
      *(undefined1 *)((int)&rec->linno + 1) = local_d;
      *(undefined1 *)&rec->linno = local_e;
      return result;
    }
    return 0xffffffff;
  case 0xb:
    result = read_sua_bytes(&local_10,0xc);
    if (result != 0) {
      *(char *)&rec->filno = local_10;
      *(undefined1 *)((int)&rec->filno + 1) = local_f;
      *(undefined1 *)&rec->linno = local_e;
      *(undefined1 *)((int)&rec->linno + 1) = local_d;
      *(undefined1 *)&rec->ea1 = local_c;
      *(undefined1 *)((int)&rec->ea1 + 1) = local_b;
      *(undefined1 *)((int)&rec->ea1 + 2) = local_a;
      *(undefined1 *)((int)&rec->ea1 + 3) = local_9;
      *(byte *)&rec->ea2 = local_8;
      *(byte *)((int)&rec->ea2 + 1) = local_7;
      *(char *)((int)&rec->ea2 + 2) = local_6;
      *(undefined1 *)((int)&rec->ea2 + 3) = local_5;
      return result;
    }
    return 0xffffffff;
  case 0xc:
    result = read_sua_bytes(&local_10,2);
    if (result == 0) {
      return 0xffffffff;
    }
    *(char *)&rec->filno = local_10;
    *(undefined1 *)((int)&rec->filno + 1) = local_f;
    break;
  default:
    report_compiler_message(0,0,0x131d,(char *)0x0);
    return 0;
  }
  return result;
#undef local_10
#undef local_f
#undef local_e
#undef local_d
#undef local_c
#undef local_b
#undef local_a
#undef local_9
#undef local_8
#undef local_7
#undef local_6
#undef local_5
#undef local_4
#undef local_3
#undef local_2
#undef local_1
}



