#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_sptravel
#define g_sptravel (*(short *)(g_sd + 0x1f944))


// entry: 00429b80
// name : emit_float_to_unsigned
// size : 475
// sig  : int emit_float_to_unsigned(gen_node * node, tmpl_entry * entry, int * opnd_ctx, ea * src, ea * dst)


int __cdecl emit_float_to_unsigned(gen_node *node,tmpl_entry *entry,int *opnd_ctx,ea *src,ea *dst)

{
  unsigned char _frec_c[12];
#define list_ea0 (*(ea * *)(_frec_c + 0))
#define list_ea1 (*(ea * *)(_frec_c + 4))
#define entries_used (*(int *)(_frec_c + 8))
  short labno;
  ea *fpul_ea;
  ea *peVar1;
  ea *peVar2;
  ea *peVar3;
  char cVar4;
  uchar uVar5;
  gen_node *pgVar6;
  
  entries_used = collect_macro_operand_list(node,entry + 1,&list_ea0,(ea **)opnd_ctx);
  fpul_ea = materialize_operand_record_from_descriptor(node,0x93,(ea **)opnd_ctx);
  peVar1 = materialize_operand_record_from_descriptor(node,0x96,(ea **)opnd_ctx);
  pgVar6 = node;
  peVar2 = copy_ea(list_ea1);
  uVar5 = '\x02';
  cVar4 = '\0';
  peVar3 = copy_ea(list_ea0);
  emit_psd_for_node(0x2c,peVar3->base,cVar4,uVar5,peVar1,peVar2,pgVar6);
  pgVar6 = node;
  peVar1 = copy_ea(list_ea1);
  peVar2 = copy_ea(src);
  emit_psd_for_node(0xc1,-1,'\0','\x02',peVar2,peVar1,pgVar6);
  labno = make_new_label_number();
  peVar1 = new_label_operand(labno);
  pgVar6 = (gen_node *)0x0;
  peVar3 = (ea *)0x0;
  uVar5 = '\x02';
  cVar4 = '\0';
  peVar2 = copy_ea(list_ea0);
  emit_psd_for_node(0x25,peVar2->base,cVar4,uVar5,peVar1,peVar3,pgVar6);
  pgVar6 = node;
  peVar1 = copy_ea(list_ea1);
  peVar2 = copy_ea(list_ea1);
  emit_psd_for_node(0xb8,-1,'\0','\x02',peVar2,peVar1,pgVar6);
  pgVar6 = node;
  peVar1 = copy_ea(src);
  peVar2 = copy_ea(list_ea1);
  emit_psd_for_node(0xba,-1,'\0','\x02',peVar2,peVar1,pgVar6);
  fill_label_record((psd *)&g_psd_scratch,OP_LABEL,labno,(short)g_sptravel);
  emit_psd_record((psd *)&g_psd_scratch,0);
  pgVar6 = node;
  peVar1 = copy_ea(fpul_ea);
  peVar2 = copy_ea(src);
  emit_psd_for_node(0xdd,-1,'\0','\x02',peVar2,peVar1,pgVar6);
  peVar1 = copy_ea(dst);
  peVar2 = copy_ea(fpul_ea);
  emit_psd_for_node(0x9d,-1,'\0','\x02',peVar2,peVar1,node);
  free_macro_operand_list(&list_ea0);
  free_ea(fpul_ea);
  return entries_used;
#undef list_ea0
#undef list_ea1
#undef entries_used
}



