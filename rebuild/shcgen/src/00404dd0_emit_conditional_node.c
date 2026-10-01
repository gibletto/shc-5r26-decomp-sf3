#include "decls.h"
#include "imports.h"

// entry: 00404dd0
// name : emit_conditional_node
// size : 255
// sig  : void emit_conditional_node(gen_node * node)


int __cdecl emit_conditional_node(gen_node *node)

{
  short labno;
  ea *src;
  gen_node *operand;
  gen_node *then_node;
  uint saved_max_sptravel;
  int saved_sptravel;
  uint then_max_sptravel;
  
  then_node = (gen_node *)0x0;
  operand = node->child;
  if (operand != (gen_node *)0x0) {
    then_node = operand->next;
  }
  emit_node_code(operand);
  saved_max_sptravel = g_max_sptravel;
  saved_sptravel = g_sptravel;
  emit_node_code(then_node);
  labno = make_new_label_number();
  src = new_label_operand(labno);
  emit_psd_for_node(0x24,node->desc->regs_2c[0],'\0','\x02',src,(ea *)0x0,(gen_node *)0x0);
  then_max_sptravel = g_max_sptravel;
  g_sptravel = saved_sptravel;
  g_max_sptravel = saved_max_sptravel;
  fill_label_record((psd *)&g_psd_scratch,OP_LABEL,operand->desc->false_label,(short)saved_sptravel)
  ;
  emit_psd_record((psd *)&g_psd_scratch,0);
  operand = nth_operand(node,3);
  emit_node_code(operand);
  fill_label_record((psd *)&g_psd_scratch,OP_LABEL,labno,(short)g_sptravel);
  emit_psd_record((psd *)&g_psd_scratch,0);
  if (g_max_sptravel < then_max_sptravel) {
    g_max_sptravel = then_max_sptravel;
  }
  return;
}



