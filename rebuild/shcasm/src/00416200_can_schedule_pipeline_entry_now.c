#include "decls.h"
#include "imports.h"

// entry: 00416200
// name : can_schedule_pipeline_entry_now
// size : 874
// sig  : int can_schedule_pipeline_entry_now(int index)


int __cdecl can_schedule_pipeline_entry_now(int index)

{
  int uses_memory;
  uint uVar1;
  
  if ((((g_pipeline_load_result_regs[0] &
        (g_pipeline_window[index].setreg[0] | g_pipeline_window[index].refreg[0])) != 0) ||
      ((g_pipeline_load_result_regs[1] &
       (g_pipeline_window[index].setreg[1] | g_pipeline_window[index].refreg[1])) != 0)) &&
     (((g_pipeline_window[index].rec.op < OP_FMOV ||
       (((((OP_FLDS < g_pipeline_window[index].rec.op ||
           (g_pipeline_window[index].rec.ea2 == (ea *)0x0)) ||
          (((g_pipeline_window[index].rec.ea2)->type & 0x1f) == 1)) ||
         ((((g_pipeline_window[index].rec.ea2)->type & 0x1f) == 5 ||
          (((g_pipeline_window[index].rec.ea2)->type & 0x1f) == 6)))) ||
        (((g_pipeline_window[index].rec.ea2)->type & 0x1f) == 0xf)))) ||
      ((((g_pipeline_window[index].rec.ea2)->type & 0x1f) == 0x10 ||
       (((g_pipeline_window[index].rec.ea2)->type & 0x1f) == 7)))))) {
    return 0;
  }
  if (g_pipeline_mac_busy != '\0') {
    if ((((g_pipeline_window[index].rec.op == OP_MUL) ||
         (g_pipeline_window[index].rec.op == OP_MULS)) ||
        (g_pipeline_window[index].rec.op == OP_MULU)) || (g_pipeline_window[index].rec.op == OP_MAC)
       ) {
      return 0;
    }
    if ((g_pipeline_window[index].rec.op == OP_LDS) &&
       (((g_pipeline_window[index].rec.ea2)->base == REG_MACH ||
        ((g_pipeline_window[index].rec.ea2)->base == REG_MACL)))) {
      return 0;
    }
    if ((g_pipeline_window[index].rec.op == OP_STS) &&
       (((g_pipeline_window[index].rec.ea1)->base == REG_MACH ||
        ((g_pipeline_window[index].rec.ea1)->base == REG_MACL)))) {
      return 0;
    }
  }
  if ((((g_pipeline_fdiv_busy != '\0') || (g_pipeline_fsqrt_busy != '\0')) &&
      (OP_DUMMY_AF < g_pipeline_window[index].rec.op)) &&
     (g_pipeline_window[index].rec.op < OP_DUMMY_E0)) {
    return 0;
  }
  if (((((g_pipeline_window[index].rec.op != OP_FLABEL) &&
        (g_pipeline_window[index].rec.op != OP_LABEL)) &&
       ((g_pipeline_window[index].rec.op != OP_CLABEL &&
        ((g_pipeline_window[index].rec.op != OP_DLABEL &&
         (g_pipeline_window[index].rec.op != OP_C_JMP)))))) &&
      (g_pipeline_window[index].rec.op != OP_B_ASM)) &&
     (((uVar1 = (int)g_pipeline_code_offset >> 0x1f,
       (((int)g_pipeline_code_offset ^ uVar1) - uVar1 & 3 ^ uVar1) != uVar1 &&
       (uses_memory = pipeline_entry_uses_memory_stage(index), uses_memory != 0)) ||
      ((uVar1 = (int)g_pipeline_code_offset >> 0x1f,
       (((int)g_pipeline_code_offset ^ uVar1) - uVar1 & 3 ^ uVar1) == uVar1 &&
       (uses_memory = pipeline_entry_uses_memory_stage(index), uses_memory == 0)))))) {
    return 0;
  }
  return 1;
}



