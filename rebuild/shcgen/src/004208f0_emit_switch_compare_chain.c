#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_switch_cases
#define g_switch_cases (*(int * *)(g_sd + 0x1fee0))


// entry: 004208f0
// name : emit_switch_compare_chain
// size : 592
// sig  : ushort emit_switch_compare_chain(uint serial, short filno, ushort linno)


ushort __cdecl emit_switch_compare_chain(uint serial,short filno,ushort linno)

{
  ea *ea1;
  ea *peVar1;
  ea *operand;
  ea *ea2;
  ushort used_regs;
  int iVar2;
  char cVar3;
  int *case_rec;
  short remaining;
  
  used_regs = 0;
  case_rec = g_switch_cases;
  remaining = g_switch_case_count;
  if (g_switch_cases != (int *)0x0) {
    for (; remaining != 0; remaining = remaining + -1) {
      ea1 = alloc_zeroed(0xc);
      iVar2 = *case_rec;
      fill_ea(ea1,'\a',-1,-1,'\0',iVar2,(label_ref *)0x0);
      if ((iVar2 < -0x80) || (0x7f < iVar2)) {
        peVar1 = alloc_zeroed(0xc);
        fill_ea(peVar1,'\x01','\0',-1,'\0',0,(label_ref *)0x0);
        operand = alloc_zeroed(0xc);
        fill_ea(operand,'\x01','\x01',-1,'\0',0,(label_ref *)0x0);
        cVar3 = '\0';
        iVar2 = 0;
        ea2 = copy_ea(operand);
        fill_psd_record((psd *)&g_psd_scratch,OP_MOVI,'\x02','\0',serial,filno,linno,ea1,ea2,iVar2,
                        cVar3);
        emit_psd_record((psd *)&g_psd_scratch,0);
        used_regs = 3;
        fill_psd_record((psd *)&g_psd_scratch,OP_CMP_EQ,'\x02','\0',serial,filno,linno,operand,
                        peVar1,0,'\0');
        emit_psd_record((psd *)&g_psd_scratch,0);
      }
      else {
        used_regs = used_regs | 1;
        peVar1 = alloc_zeroed(0xc);
        fill_ea(peVar1,'\x01','\0',-1,'\0',0,(label_ref *)0x0);
        fill_psd_record((psd *)&g_psd_scratch,OP_CMP_EQ,'\x02','\0',serial,filno,linno,ea1,peVar1,0,
                        '\0');
        emit_psd_record((psd *)&g_psd_scratch,0);
      }
      used_regs = used_regs | 2;
      cVar3 = '\x01';
      iVar2 = 0;
      peVar1 = (ea *)0x0;
      ea1 = make_label_operand((short)case_rec[1]);
      fill_psd_record((psd *)&g_psd_scratch,OP_JUMPT,'\x02','\0',serial,filno,linno,ea1,peVar1,iVar2
                      ,cVar3);
      emit_psd_record((psd *)&g_psd_scratch,0);
      case_rec = case_rec + 2;
    }
  }
  if (g_switch_default_label != 0) {
    cVar3 = '\x01';
    iVar2 = 0;
    peVar1 = (ea *)0x0;
    ea1 = make_label_operand(g_switch_default_label);
    fill_psd_record((psd *)&g_psd_scratch,OP_JUMP,'\x02','\0',serial,filno,linno,ea1,peVar1,iVar2,
                    cVar3);
    used_regs = used_regs | 2;
    emit_psd_record((psd *)&g_psd_scratch,0);
  }
  return used_regs;
}



