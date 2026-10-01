#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_sptravel
#define g_sptravel (*(short *)(g_sd + 0x1f944))


// entry: 004297f0
// name : emit_unsigned_to_float
// size : 416
// sig  : int emit_unsigned_to_float(gen_node * node, tmpl_entry * entry, int * opnd_ctx, ea * src, ea * dst)


int __cdecl emit_unsigned_to_float(gen_node *node,tmpl_entry *entry,int *opnd_ctx,ea *src,ea *dst)

{
  unsigned char _frec_c[12];
#define list_ea0 (*(ea * *)(_frec_c + 0))
#define list_ea1 (*(ea * *)(_frec_c + 4))
#define entries_used (*(int *)(_frec_c + 8))
  short labno;
  ea *fpul_ea;
  ea *peVar1;
  ea *peVar2;
  char cVar3;
  uchar uVar4;
  ea *peVar5;
  gen_node *pgVar6;
  
  entries_used = collect_macro_operand_list(node,entry + 1,&list_ea0,(ea **)opnd_ctx);
  fpul_ea = materialize_operand_record_from_descriptor(node,0x93,(ea **)opnd_ctx);
  pgVar6 = node;
  peVar1 = copy_ea(fpul_ea);
  peVar2 = copy_ea(src);
  emit_psd_for_node(0x8d,-1,'\0','\x02',peVar2,peVar1,pgVar6);
  pgVar6 = node;
  peVar1 = copy_ea(dst);
  peVar2 = copy_ea(fpul_ea);
  emit_psd_for_node(0xdc,-1,'\0','\x02',peVar2,peVar1,pgVar6);
  peVar2 = (ea *)0x0;
  pgVar6 = node;
  peVar1 = copy_ea(src);
  emit_psd_for_node(0x55,-1,'\0','\x02',peVar1,peVar2,pgVar6);
  labno = make_new_label_number();
  peVar1 = new_label_operand(labno);
  pgVar6 = (gen_node *)0x0;
  peVar5 = (ea *)0x0;
  uVar4 = '\x02';
  cVar3 = '\0';
  peVar2 = copy_ea(list_ea0);
  emit_psd_for_node(0x25,peVar2->base,cVar3,uVar4,peVar1,peVar5,pgVar6);
  peVar1 = materialize_operand_record_from_descriptor(node,0x95,(ea **)opnd_ctx);
  pgVar6 = node;
  peVar2 = copy_ea(list_ea1);
  uVar4 = '\x02';
  cVar3 = '\0';
  peVar5 = copy_ea(list_ea0);
  emit_psd_for_node(0x2c,peVar5->base,cVar3,uVar4,peVar1,peVar2,pgVar6);
  peVar1 = copy_ea(dst);
  peVar2 = copy_ea(list_ea1);
  emit_psd_for_node(0xb8,-1,'\0','\x02',peVar2,peVar1,node);
  fill_label_record((psd *)&g_psd_scratch,OP_LABEL,labno,(short)g_sptravel);
  emit_psd_record((psd *)&g_psd_scratch,0);
  free_macro_operand_list(&list_ea0);
  free_ea(fpul_ea);
  return entries_used;
#undef list_ea0
#undef list_ea1
#undef entries_used
}



