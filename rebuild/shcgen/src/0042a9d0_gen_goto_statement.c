#include "decls.h"
#include "imports.h"

// entry: 0042a9d0
// name : gen_goto_statement
// size : 211
// sig  : void gen_goto_statement(gen_node * node)


int __cdecl gen_goto_statement(gen_node *node)

{
  short sVar1;
  ea *label_ea;
  
  if (node->symx < 0) {
    sVar1 = g_last_goto_label;
    if (g_last_goto_label == 0) {
      report_codegen_message(0x120b,node->filn,(uint)node->line,(int)node->listno,(char *)0x0);
      goto LAB_0042aa2e;
    }
  }
  else {
    sVar1 = node->symx + 0xb6;
  }
  label_ea = make_label_operand(sVar1);
LAB_0042aa2e:
  sVar1 = choose_general_register(0,0,'\0');
  remove_serial_from_register_ranges(1 << ((byte)sVar1 & 0x1f),g_stmt_serial);
  fill_psd_record((psd *)&g_psd_scratch,OP_JUMP,'\x02','\0',g_stmt_serial,g_msg_filn,g_msg_line,
                  label_ea,(ea *)0x0,0,(byte)sVar1);
  emit_psd_record((psd *)&g_psd_scratch,0);
  return;
}



