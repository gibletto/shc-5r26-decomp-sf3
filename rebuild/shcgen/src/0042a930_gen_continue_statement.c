#include "decls.h"
#include "imports.h"
#include "remaprules.h"

// entry: 0042a930
// name : gen_continue_statement
// size : 151
// sig  : void gen_continue_statement(void)


int __cdecl gen_continue_statement(void)

{
  short reg;
  ea *ea1;
  byte tmp;
  ea *ea2;
  int sptravel;
  
  if (g_continue_label == 0) {
    g_continue_label = make_new_label_number();
  }
  reg = choose_general_register(0,0,'\0');
  tmp = (byte)reg;
  remove_serial_from_register_ranges(JUMP_TEMP_REGS(1,1 << (tmp & 0x1f)),g_stmt_serial);
  sptravel = 0;
  ea2 = (ea *)0x0;
  ea1 = make_label_operand(g_continue_label);
  fill_psd_record((psd *)&g_psd_scratch,OP_JUMP,'\x02','\0',g_stmt_serial,g_msg_filn,g_msg_line,ea1,
                  ea2,sptravel,tmp);
  emit_psd_record((psd *)&g_psd_scratch,0);
  return;
}



