#include "decls.h"
#include "imports.h"

// entry: 0041a950
// name : move_psd_record
// size : 781
// sig  : void __cdecl move_psd_record(psd *src,psd *dst)


int __cdecl move_psd_record(psd *src,psd *dst)

{
  psd_op op;
  
  if (src == (psd *)0x0) {
    return;
  }
  if (dst == (psd *)0x0) {
    return;
  }
  if (dst == src) {
    return;
  }
  op = dst->op;
  if (((((op != OP_CASEJMP) && (op != OP_LABEL)) && (op != OP_CLABEL)) &&
      (((op != OP_DLABEL && (op != OP_FLABEL)) &&
       ((op != OP_CTBL && ((op != OP_CENT && (op != OP_LINE)))))))) &&
     ((op != OP_NON_10 && (op != OP_PROGRAM)))) {
    if (dst->ea1 != (ea *)0x0) {
      free_ea(dst->ea1);
      dst->ea1 = (ea *)0x0;
    }
    if (dst->ea2 != (ea *)0x0) {
      free_ea(dst->ea2);
      dst->ea2 = (ea *)0x0;
    }
  }
  dst->op = src->op;
  dst->flg = src->flg;
  dst->misc = src->misc;
  dst->tmp = src->tmp;
  dst->sptravel = src->sptravel;
  dst->expno = src->expno;
  op = src->op;
  if (op == OP_CASEJMP) {
    dst->filno = src->filno;
    dst->linno = src->linno;
    dst->ea1 = src->ea1;
    dst->ea2 = src->ea2;
    src->ea1 = (ea *)0x0;
    src->filno = 0;
    src->linno = 0;
  }
  else {
    if ((((op < OP_LABEL) || (OP_FLABEL < op)) && (op != OP_CTBL)) && (op != OP_CENT)) {
      if (op != OP_LINE) {
        if (op == OP_NON_10) {
          dst->filno = src->filno;
          dst->linno = src->linno;
          dst->ea1 = src->ea1;
          dst->ea2 = src->ea2;
          src->ea1 = (ea *)0x0;
          src->filno = 0;
          src->linno = 0;
        }
        else {
          dst->filno = src->filno;
          dst->linno = src->linno;
          if (op == OP_PROGRAM) {
            dst->ea1 = src->ea1;
            dst->ea2 = src->ea2;
            src->ea1 = (ea *)0x0;
            src->filno = 0;
            src->linno = 0;
          }
          else {
            src->filno = 0;
            src->linno = 0;
            if (src->ea1 == (ea *)0x0) {
              dst->ea1 = (ea *)0x0;
            }
            else {
              dst->ea1 = src->ea1;
              src->ea1 = (ea *)0x0;
            }
            if (src->ea2 == (ea *)0x0) {
              dst->ea2 = (ea *)0x0;
              goto LAB_0041ac3d;
            }
            dst->ea2 = src->ea2;
          }
        }
        goto LAB_0041ac36;
      }
      dst->filno = src->filno;
      dst->linno = src->linno;
      dst->ea1 = src->ea1;
      dst->ea2 = src->ea2;
      *(undefined1 *)&src->ea1 = 0;
      *(undefined1 *)((int)&src->ea1 + 1) = 0;
      src->filno = 0;
      src->linno = 0;
    }
    else {
      dst->filno = src->filno;
      dst->linno = src->linno;
      dst->ea1 = src->ea1;
      dst->ea2 = src->ea2;
      src->filno = 0;
      src->linno = 0;
      *(undefined2 *)&src->ea1 = 0;
    }
    *(undefined2 *)((int)&src->ea1 + 2) = 0;
  }
LAB_0041ac36:
  src->ea2 = (ea *)0x0;
LAB_0041ac3d:
  src->flg = '\0';
  src->misc = '\0';
  src->tmp = -1;
  src->sptravel = 0;
  src->expno = 0;
  src->op = OP_DUMMY;
  return;
}
