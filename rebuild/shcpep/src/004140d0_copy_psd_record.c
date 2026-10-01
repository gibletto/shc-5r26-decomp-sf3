#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_stage_flags
#define g_stage_flags (*(unsigned char *)(g_sd + 0x6d64))


// entry: 004140d0
// name : copy_psd_record
// size : 829
// sig  : void __cdecl copy_psd_record(psd *src,psd *dst)


int __cdecl copy_psd_record(psd *src,psd *dst)

{
  ea *new_ea;
  bool dst_ea_shared;
  bool dst_live;
  psd_op op;
  
  dst_live = false;
  dst_ea_shared = false;
  if (((byte)g_stage_flags & 2) != 0) {
    _printf(s_dc_cpycd_start__inp__08lx__outp__004278e4,src,dst);
    dump_memory_hex(&src->op,s_dc_cpycd___input_psdtbl_dmp_004278c8,0x18);
  }
  if (src->op == OP_DUMMY) {
    if (dst->op != OP_DUMMY) {
      clear_psd_record(dst);
    }
  }
  else {
    op = dst->op;
    if ((op != OP_DUMMY) &&
       ((((dst_live = true, op == OP_CASEJMP ||
          ((((OP_BEND < op && (op < OP_NON_1C)) || (op == OP_CTBL)) ||
           ((op == OP_CENT || (op == OP_LINE)))))) || (op == OP_NON_10)) || (op == OP_PROGRAM)))) {
      dst_ea_shared = true;
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
    }
    else if ((op < OP_LABEL) || (OP_FLABEL < op)) {
      if ((op == OP_CTBL) || (op == OP_CENT)) {
        dst->filno = src->filno;
        dst->linno = src->linno;
        dst->ea1 = src->ea1;
        dst->ea2 = src->ea2;
      }
      else if (op == OP_LINE) {
        dst->filno = src->filno;
        dst->linno = src->linno;
        dst->ea1 = src->ea1;
        dst->ea2 = src->ea2;
      }
      else if (op == OP_NON_10) {
        dst->filno = src->filno;
        dst->linno = src->linno;
        dst->ea1 = src->ea1;
        dst->ea2 = src->ea2;
      }
      else {
        dst->filno = src->filno;
        dst->linno = src->linno;
        if (op == OP_PROGRAM) {
          dst->ea1 = src->ea1;
          dst->ea2 = src->ea2;
        }
        else {
          if (src->ea1 == (ea *)0x0) {
            if (dst_live) {
              if ((!dst_ea_shared) && (dst->ea1 != (ea *)0x0)) {
                free_ea(dst->ea1);
              }
              dst->ea1 = (ea *)0x0;
            }
          }
          else {
            new_ea = copy_ea(src->ea1);
            dst->ea1 = new_ea;
          }
          if (src->ea2 == (ea *)0x0) {
            if (dst_live) {
              if ((!dst_ea_shared) && (dst->ea2 != (ea *)0x0)) {
                free_ea(dst->ea2);
              }
              dst->ea2 = (ea *)0x0;
            }
          }
          else {
            new_ea = copy_ea(src->ea2);
            dst->ea2 = new_ea;
          }
        }
      }
    }
    else {
      dst->filno = src->filno;
      dst->linno = src->linno;
      dst->ea1 = src->ea1;
      dst->ea2 = src->ea2;
    }
  }
  if (((byte)g_stage_flags & 2) != 0) {
    dump_memory_hex(&dst->op,s_dc_cpycd___output_psdtbl_dmp_004278a8,0x18);
    _printf(s_dc_cpycd_end__00427898);
  }
  return;
}
