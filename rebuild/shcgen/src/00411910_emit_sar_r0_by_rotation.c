#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_sptravel
#define g_sptravel (*(short *)(g_sd + 0x1f944))


// entry: 00411910
// name : emit_sar_r0_by_rotation
// size : 558
// sig  : void emit_sar_r0_by_rotation(int count, ea * hint)


int __cdecl emit_sar_r0_by_rotation(int count,ea *hint)

{
  short negative_label;
  short end_label;
  ea *src;
  ea *opnd;
  ea *peVar1;
  ea *dst;
  short i;
  int rotations;
  
  rotations = 0x1f - count;
  src = new_ea_operand_with_flags('\x01','\0',-1,0,'\0',(label_ref *)0x0);
  opnd = copy_ea(src);
  emit_psd_for_node(0x4e,-1,'\0','\x02',opnd,(ea *)0x0,(gen_node *)0x0);
  negative_label = make_new_label_number();
  opnd = new_label_operand(negative_label);
  end_label = make_new_label_number();
  peVar1 = new_label_operand(end_label);
  i = 1;
  emit_psd_for_node(0x25,hint->base,'\0','\x02',opnd,(ea *)0x0,(gen_node *)0x0);
  if (0 < rotations) {
    do {
      i = i + 1;
      opnd = copy_ea(src);
      emit_psd_for_node(0x4e,-1,'\0','\x02',opnd,(ea *)0x0,(gen_node *)0x0);
    } while (i <= rotations);
  }
  opnd = new_ea_operand_with_flags
                   ('\a',-1,-1,(1 << (0x20U - (char)count & 0x1f)) + -1,'\0',(label_ref *)0x0);
  dst = copy_ea(src);
  emit_psd_for_node(0x80,-1,'\0','\x02',opnd,dst,(gen_node *)0x0);
  copy_ea(peVar1);
  emit_psd_for_node(0x24,hint->base,'\0','\x02',peVar1,(ea *)0x0,(gen_node *)0x0);
  i = 1;
  fill_label_record((psd *)&g_psd_scratch,OP_LABEL,negative_label,(short)g_sptravel);
  emit_psd_record((psd *)&g_psd_scratch,0);
  if (0 < rotations) {
    do {
      i = i + 1;
      opnd = copy_ea(src);
      emit_psd_for_node(0x4e,-1,'\0','\x02',opnd,(ea *)0x0,(gen_node *)0x0);
    } while (i <= rotations);
  }
  opnd = new_ea_operand_with_flags
                   ('\a',-1,-1,-1 << (0x1fU - (char)count & 0x1f) & 0xff,'\0',(label_ref *)0x0);
  peVar1 = copy_ea(src);
  emit_psd_for_node(0x81,-1,'\0','\x02',opnd,peVar1,(gen_node *)0x0);
  opnd = copy_ea(src);
  peVar1 = copy_ea(src);
  emit_psd_for_node(0x7b,-1,'\0','\0',opnd,peVar1,(gen_node *)0x0);
  fill_label_record((psd *)&g_psd_scratch,OP_LABEL,end_label,(short)g_sptravel);
  emit_psd_record((psd *)&g_psd_scratch,0);
  free_ea(src);
  return;
}



