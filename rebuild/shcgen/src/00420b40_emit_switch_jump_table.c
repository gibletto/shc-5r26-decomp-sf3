#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_switch_cases
#define g_switch_cases (*(int * *)(g_sd + 0x1fee0))


// entry: 00420b40
// name : emit_switch_jump_table
// size : 263
// sig  : ushort emit_switch_jump_table(uint serial, gen_node * sw)


ushort __cdecl emit_switch_jump_table(uint serial,gen_node *sw)

{
  int value;
  short remaining;
  int *cur_case;
  int *next_case;
  int *prev_case;
  
  fill_psd_record_without_sptravel
            ((psd *)&g_psd_scratch,OP_CASEJMP,'\x02','\0',serial,sw->symx,g_switch_default_label,
             (ea *)g_switch_min_case,(ea *)((g_switch_max_case - g_switch_min_case) + 1));
  emit_psd_record((psd *)&g_psd_scratch,0);
  fill_case_table_record
            ((psd *)&g_psd_scratch,OP_CTBL,((short)g_switch_max_case - (short)g_switch_min_case) + 1
             ,g_break_label);
  emit_psd_record((psd *)&g_psd_scratch,0);
  next_case = g_switch_cases;
  prev_case = g_switch_cases;
  for (remaining = g_switch_case_count; cur_case = next_case, remaining != 0;
      remaining = remaining + -1) {
    value = *prev_case + 1;
    if (value < *cur_case) {
      do {
        value = value + 1;
        fill_case_table_record((psd *)&g_psd_scratch,OP_CENT,0,g_switch_default_label);
        emit_psd_record((psd *)&g_psd_scratch,0);
      } while (value < *cur_case);
    }
    fill_case_table_record((psd *)&g_psd_scratch,OP_CENT,0,(short)cur_case[1]);
    emit_psd_record((psd *)&g_psd_scratch,0);
    next_case = cur_case + 2;
    prev_case = cur_case;
  }
  return 3;
}



