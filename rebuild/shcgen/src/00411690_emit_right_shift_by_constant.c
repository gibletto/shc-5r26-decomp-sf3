#include "decls.h"
#include "imports.h"

// entry: 00411690
// name : emit_right_shift_by_constant
// size : 639
// sig  : void emit_right_shift_by_constant(ea * reg, int count, char logical)


int __cdecl emit_right_shift_by_constant(ea *reg,int count,char logical)

{
  ea *first;
  ea *second;
  short i;
  gen_node *pgVar1;
  
  if (logical == '\x01') {
    if (count < 0) {
      if (count < 0x1d) {
        return;
      }
    }
    else if (count < 0x1d) {
      emit_shift_by_constant(reg,'\x01',count);
      return;
    }
    if (0x1f < count) {
      return;
    }
    i = 1;
    if (0 < 0x20 - count) {
      do {
        i = i + 1;
        first = copy_ea(reg);
        emit_psd_for_node(0x4e,-1,'\0','\x02',first,(ea *)0x0,(gen_node *)0x0);
      } while ((int)i <= 0x20 - count);
    }
    first = new_ea_operand_with_flags
                      ('\a',-1,-1,(1 << (0x20U - (char)count & 0x1f)) + -1,'\0',(label_ref *)0x0);
    second = copy_ea(reg);
    emit_psd_for_node(0x80,-1,'\0','\x02',first,second,(gen_node *)0x0);
    return;
  }
  if (count < 0) {
    if (0xf < count) goto LAB_00411780;
    if (count < 0x18) goto LAB_004118bd;
  }
  else {
    if (count < 0x10) {
      emit_shift_by_constant(reg,logical,count);
      return;
    }
LAB_00411780:
    if (count < 0x18) {
      i = 1;
      if (0 < count + -0x10) {
        do {
          i = i + 1;
          first = copy_ea(reg);
          emit_psd_for_node(0x59,-1,'\0','\x02',first,(ea *)0x0,(gen_node *)0x0);
        } while ((int)i <= count + -0x10);
      }
      first = copy_ea(reg);
      emit_psd_for_node(0x5d,-1,'\0','\x02',first,(ea *)0x0,(gen_node *)0x0);
      first = copy_ea(reg);
      second = copy_ea(reg);
      emit_psd_for_node(0x7b,-1,'\0','\x01',first,second,(gen_node *)0x0);
      return;
    }
  }
  if (count < 0x1d) {
    i = 1;
    if (0 < count + -0x18) {
      do {
        i = i + 1;
        first = copy_ea(reg);
        emit_psd_for_node(0x59,-1,'\0','\x02',first,(ea *)0x0,(gen_node *)0x0);
      } while ((int)i <= count + -0x18);
    }
    first = copy_ea(reg);
    emit_psd_for_node(0x5d,-1,'\0','\x02',first,(ea *)0x0,(gen_node *)0x0);
    first = copy_ea(reg);
    emit_psd_for_node(0x5c,-1,'\0','\x02',first,(ea *)0x0,(gen_node *)0x0);
    first = copy_ea(reg);
    second = copy_ea(reg);
    emit_psd_for_node(0x7b,-1,'\0','\0',first,second,(gen_node *)0x0);
    return;
  }
LAB_004118bd:
  if (count == 0x1f) {
    pgVar1 = (gen_node *)0x0;
    second = (ea *)0x0;
    first = copy_ea(reg);
    emit_psd_for_node(0x4e,-1,'\0','\x02',first,second,pgVar1);
    pgVar1 = (gen_node *)0x0;
    first = copy_ea(reg);
    second = copy_ea(reg);
    emit_psd_for_node(100,-1,'\0','\x02',second,first,pgVar1);
  }
  return;
}



