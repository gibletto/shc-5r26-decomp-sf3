#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_sptravel
#define g_sptravel (*(short *)(g_sd + 0x1f944))


// entry: 00429d60
// name : emit_double_to_unsigned
// size : 547
// sig  : int emit_double_to_unsigned(gen_node * node, tmpl_entry * entry, int * opnd_ctx, ea * src, ea * dst)


int __cdecl emit_double_to_unsigned(gen_node *node,tmpl_entry *entry,int *opnd_ctx,ea *src,ea *dst)

{
  unsigned char _frec_c[12];
#define list_ea0 (*(ea * *)(_frec_c + 0))
#define list_ea1 (*(ea * *)(_frec_c + 4))
#define entries_used (*(int *)(_frec_c + 8))
  short labno;
  ea *peVar1;
  ea *peVar2;
  ea *peVar3;
  char flag_20;
  uchar size;
  ea *dst_00;
  gen_node *pgVar4;
  
  entries_used = collect_macro_operand_list(node,entry + 1,&list_ea0,(ea **)opnd_ctx);
  peVar1 = materialize_operand_record_from_descriptor(node,0xf2,(ea **)opnd_ctx);
  pgVar4 = node;
  peVar2 = copy_ea(list_ea0);
  emit_psd_for_node(0x2a,-1,'\0','\x02',peVar1,peVar2,pgVar4);
  peVar1 = materialize_operand_record_from_descriptor(node,0x93,(ea **)opnd_ctx);
  pgVar4 = node;
  peVar2 = copy_ea(peVar1);
  peVar3 = copy_ea(list_ea0);
  emit_psd_for_node(0x8d,-1,'\0','\x02',peVar3,peVar2,pgVar4);
  pgVar4 = node;
  peVar2 = copy_ea(list_ea1);
  peVar3 = copy_ea(peVar1);
  emit_psd_for_node(0xb6,-1,'\0','\x03',peVar3,peVar2,pgVar4);
  pgVar4 = node;
  peVar2 = copy_ea(src);
  peVar3 = copy_ea(list_ea1);
  emit_psd_for_node(0xc1,-1,'\0','\x03',peVar3,peVar2,pgVar4);
  labno = make_new_label_number();
  peVar2 = new_label_operand(labno);
  pgVar4 = (gen_node *)0x0;
  dst_00 = (ea *)0x0;
  size = '\x02';
  flag_20 = '\0';
  peVar3 = copy_ea(list_ea0);
  emit_psd_for_node(0x25,peVar3->base,flag_20,size,peVar2,dst_00,pgVar4);
  pgVar4 = node;
  peVar2 = copy_ea(list_ea1);
  peVar3 = copy_ea(list_ea1);
  emit_psd_for_node(0xb8,-1,'\0','\x03',peVar3,peVar2,pgVar4);
  pgVar4 = node;
  peVar2 = copy_ea(src);
  peVar3 = copy_ea(list_ea1);
  emit_psd_for_node(0xba,-1,'\0','\x03',peVar3,peVar2,pgVar4);
  fill_label_record((psd *)&g_psd_scratch,OP_LABEL,labno,(short)g_sptravel);
  emit_psd_record((psd *)&g_psd_scratch,0);
  pgVar4 = node;
  peVar2 = copy_ea(peVar1);
  peVar3 = copy_ea(src);
  emit_psd_for_node(0xdd,-1,'\0','\x03',peVar3,peVar2,pgVar4);
  peVar2 = copy_ea(dst);
  peVar3 = copy_ea(peVar1);
  emit_psd_for_node(0x9d,-1,'\0','\x02',peVar3,peVar2,node);
  free_macro_operand_list(&list_ea0);
  free_ea(peVar1);
  return entries_used;
#undef list_ea0
#undef list_ea1
#undef entries_used
}



