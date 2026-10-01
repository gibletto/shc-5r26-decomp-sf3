#include "decls.h"
#include "imports.h"
#include "mulrules.h"

// entry: 00416754
// name : commit_scheduled_pipeline_entry
// size : 1160
// sig  : void __cdecl commit_scheduled_pipeline_entry(int index)


int __cdecl commit_scheduled_pipeline_entry(int index)

{
  symbol *label_sym;
  uint uVar1;
  psd_op op_code;
  
  if (g_pipeline_last_scheduled == -1) {
    g_pipeline_first_scheduled = index;
  }
  else {
    g_pipeline_window[g_pipeline_last_scheduled].next = (short)index;
  }
  g_pipeline_last_scheduled = index;
  g_pipeline_window[index].next = -2;
  op_code = g_pipeline_window[index].rec.op;
  if ((OP_BEND < op_code) && (op_code < OP_DUMMY_1C)) {
    label_sym = find_symbol_by_id(*(short *)&g_pipeline_window[index].rec.ea1);
    g_pipeline_load_result_regs[0] = 0;
    g_pipeline_load_result_regs[1] = 0;
    g_pipeline_mac_busy = '\0';
    g_pipeline_fsqrt_busy = '\0';
    g_pipeline_fdiv_busy = '\0';
    g_pipeline_code_offset = (char)label_sym->value;
    return;
  }
  if ((((((op_code == OP_BRA) || (op_code == OP_BSR)) || (op_code == OP_JMP)) ||
       ((op_code == OP_JSR || (op_code == OP_RTS)))) || (op_code == OP_BT_S)) ||
     (((op_code == OP_BF_S || (op_code == OP_BSRF)) ||
      ((op_code == OP_BRAF || ((op_code == OP_RTE || (op_code == OP_TRAPA)))))))) {
    g_pipeline_code_offset = g_pipeline_code_offset + '\x04';
  }
  else {
    if (op_code == OP_B_ASM) {
      uVar1 = (int)g_pipeline_code_offset >> 0x1f;
      if ((((int)g_pipeline_code_offset ^ uVar1) - uVar1 & 3 ^ uVar1) == uVar1) {
        return;
      }
      g_pipeline_code_offset = g_pipeline_code_offset + '\x02';
      return;
    }
    if (op_code == OP_C_JMP) {
      return;
    }
    g_pipeline_code_offset = g_pipeline_code_offset + '\x02';
  }
  if ((((op_code == OP_MUL) || (op_code == OP_MULS)) || (op_code == OP_MULU)) || (op_code == OP_MAC)
     ) {
    g_pipeline_mac_busy = (char)MUL_BUSY_COUNT;
  }
  else if ((op_code == OP_LDS) &&
          (((g_pipeline_window[index].rec.ea2)->base == REG_MACH ||
           ((g_pipeline_window[index].rec.ea2)->base == REG_MACL)))) {
    g_pipeline_mac_busy = '\0';
  }
  else if ((op_code == OP_STS) &&
          (((g_pipeline_window[index].rec.ea1)->base == REG_MACH ||
           ((g_pipeline_window[index].rec.ea1)->base == REG_MACL)))) {
    g_pipeline_mac_busy = '\0';
  }
  else if (g_pipeline_mac_busy != '\0') {
    g_pipeline_mac_busy = g_pipeline_mac_busy + -1;
  }
  if (op_code == OP_FDIV) {
    g_pipeline_fdiv_busy = '\x04';
    g_pipeline_fsqrt_busy = '\0';
  }
  else if (op_code == OP_FSQRT) {
    g_pipeline_fsqrt_busy = '\x04';
    g_pipeline_fdiv_busy = '\0';
  }
  else if ((op_code < OP_FMOV) || (OP_FLDS < op_code)) {
    if (g_pipeline_fdiv_busy != '\0') {
      g_pipeline_fdiv_busy = g_pipeline_fdiv_busy + -1;
    }
    if (g_pipeline_fsqrt_busy != '\0') {
      g_pipeline_fsqrt_busy = g_pipeline_fsqrt_busy + -1;
    }
  }
  else {
    g_pipeline_fdiv_busy = '\0';
    g_pipeline_fsqrt_busy = '\0';
  }
  if (((((g_pipeline_window[index].rec.ea1 == (ea *)0x0) ||
        (((g_pipeline_window[index].rec.ea1)->type & 0x1f) == 1)) ||
       (((g_pipeline_window[index].rec.ea1)->type & 0x1f) == 5)) ||
      (((((g_pipeline_window[index].rec.ea1)->type & 0x1f) == 6 ||
        (((g_pipeline_window[index].rec.ea1)->type & 0x1f) == 0xf)) ||
       ((((g_pipeline_window[index].rec.ea1)->type & 0x1f) == 0x10 ||
        (((g_pipeline_window[index].rec.ea1)->type & 0x1f) == 7)))))) &&
     ((op_code < OP_FMOV || (OP_FLDS < op_code)))) {
    g_pipeline_load_result_regs[1] = 0;
    g_pipeline_load_result_regs[0] = 0;
  }
  else {
    g_pipeline_load_result_regs[0] = g_pipeline_window[index].setreg[0];
    g_pipeline_load_result_regs[1] = g_pipeline_window[index].setreg[1];
  }
  return;
}
