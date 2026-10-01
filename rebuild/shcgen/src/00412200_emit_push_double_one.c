#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))


// entry: 00412200
// name : emit_push_double_one
// size : 388
// sig  : int emit_push_double_one(gen_node * node, tmpl_entry * entry, ea * * operands)


int __cdecl emit_push_double_one(gen_node *node,tmpl_entry *entry,ea **operands)

{
  unsigned char _frec_8[8];
#define macro_opnds (*(ea * (*)[2])(_frec_8 + 0))
  int entries_used;
  ea *opnd;
  ea *reg_copy;
  int disp;
  gen_node *pgVar1;
  
  entries_used = collect_macro_operand_list(node,entry + 1,macro_opnds,operands);
  if (g_request->unknown_028[2] == '\0') {
    opnd = new_ea_operand_with_flags('\a',-1,-1,g_double_one_lo,'\0',(label_ref *)0x0);
    pgVar1 = node;
    reg_copy = copy_ea(macro_opnds[0]);
    emit_psd_for_node(0x2a,-1,'\0','\x02',opnd,reg_copy,pgVar1);
    pgVar1 = node;
    opnd = copy_ea(&g_ea_push);
    reg_copy = copy_ea(macro_opnds[0]);
    emit_psd_for_node(0x40,-1,'\0','\x02',reg_copy,opnd,pgVar1);
    disp = g_double_one_hi;
  }
  else {
    opnd = new_ea_operand_with_flags('\a',-1,-1,g_double_one_hi,'\0',(label_ref *)0x0);
    pgVar1 = node;
    reg_copy = copy_ea(macro_opnds[0]);
    emit_psd_for_node(0x2a,-1,'\0','\x02',opnd,reg_copy,pgVar1);
    pgVar1 = node;
    opnd = copy_ea(&g_ea_push);
    reg_copy = copy_ea(macro_opnds[0]);
    emit_psd_for_node(0x40,-1,'\0','\x02',reg_copy,opnd,pgVar1);
    disp = g_double_one_lo;
  }
  opnd = new_ea_operand_with_flags('\a',-1,-1,disp,'\0',(label_ref *)0x0);
  pgVar1 = node;
  reg_copy = copy_ea(macro_opnds[0]);
  emit_psd_for_node(0x2a,-1,'\0','\x02',opnd,reg_copy,pgVar1);
  opnd = copy_ea(&g_ea_push);
  reg_copy = copy_ea(macro_opnds[0]);
  emit_psd_for_node(0x40,-1,'\0','\x02',reg_copy,opnd,node);
  free_macro_operand_list(macro_opnds);
  return entries_used;
#undef macro_opnds
}



