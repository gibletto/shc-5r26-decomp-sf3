#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_stage_request
#define g_stage_request (*(request * *)(g_sd + 0x1ee88))


// entry: 00432290
// name : compute_record_code_size
// size : 316
// sig  : int compute_record_code_size(psd * rec)


/* WARNING: Type propagation algorithm not settling */

int __cdecl compute_record_code_size(psd *rec)

{
  int *size;
  ea *operand;
  
  size = (int *)(int)*(short *)(&g_op_code_size_table + (uint)rec->op * 2);
  switch((uint)rec->op) {
  case 0x10:
    operand = rec->ea2;
    if (operand != (ea *)0x0) {
      size = (int *)(&operand->index + ((uint)operand & 1));
    }
    break;
  case 0x14:
    size = (int *)((int)rec->filno << 2);
    break;
  case 0x20:
    if (((g_stage_request->cpu == 2) && (g_stage_request->fpu_mode == '\x03')) ||
       ((g_stage_request->cpu == 4 && (g_stage_request->fpu_mode == '\x03')))) {
      size = (int *)0x5a;
    }
    else {
      size = (int *)0x36;
    }
    break;
  case 0x21:
    if (((g_stage_request->cpu == 2) && (g_stage_request->fpu_mode == '\x03')) ||
       ((g_stage_request->cpu == 4 && (g_stage_request->fpu_mode == '\x03')))) {
      size = (int *)0x54;
    }
    else {
      size = (int *)0x30;
    }
    break;
  case 0x22:
    size = (int *)0x10;
    break;
  case 0x27:
    size = (int *)0x6;
    break;
  case 0x28:
    size = (int *)0x4;
    break;
  case 0x2a:
    if ((rec->misc & 0x40U) == 0) {
      size = (int *)((int)size + 0xfffffffe);
    }
    break;
  case 0x2c:
    size = (int *)((-(uint)(rec->tmp == '\0') & 0xfffffffe) + 6);
    break;
  case 0x40:
    if ((g_stage_request->flags_13d & 4) == 0) break;
    if ((rec->flg & 0x40U) == 0) {
      if ((((rec->ea1->type & 0x1f) == 1) && ((rec->ea2->type & 0x1f) == 1)) &&
         (rec->ea2->base == '\0')) {
        size = (int *)((int)size + 2);
      }
      break;
    }
    goto LAB_004323c7;
  }
  if ((rec->flg & 0x40U) != 0) {
LAB_004323c7:
    size = (int *)((int)size + 0xfffffffe);
  }
  return (int)size;
}



