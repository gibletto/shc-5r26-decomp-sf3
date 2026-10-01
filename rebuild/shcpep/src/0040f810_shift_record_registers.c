#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0x5bf0))
#undef g_stage_flags
#define g_stage_flags (*(unsigned char *)(g_sd + 0x6d64))


// entry: 0040f810
// name : shift_record_registers
// size : 680
// sig  : void __cdecl shift_record_registers(psd *rec)


int __cdecl shift_record_registers(psd *rec)

{
  char old_base1;
  char old_base2;
  char old_tmp;
  ea *opnd;
  
  if (((*(unsigned char *)((char *)&g_stage_flags + 1)) & 1) != 0) {
    _printf(s_______before_register_shift__ea1_0042689c);
    _printf(s_psdop___x_____00426888,(int)(char)rec->op);
    _printf(s_expno___d_____00426878,rec->expno);
    _printf(s_tempreg__d_00426868,(int)rec->tmp);
    if (rec->ea1 != (ea *)0x0) {
      _printf(s_basereg__d_00426858,(int)rec->ea1->base);
      _printf(s_indexreg__d_00426848,(int)rec->ea1->index);
    }
    if (rec->ea2 != (ea *)0x0) {
      _printf(s_______before_register_shift__ea2_0042681c);
      _printf(s_basereg__d_00426858,(int)rec->ea2->base);
      _printf(s_indexreg__d_0042680c,(int)rec->ea2->index);
    }
  }
  old_tmp = rec->tmp;
  if (old_tmp != -1) {
    rec->tmp = (&g_reg_remap_table)[old_tmp];
  }
  opnd = rec->ea1;
  if (opnd != (ea *)0x0) {
    old_base1 = opnd->base;
    shift_ea_registers(opnd);
  }
  opnd = rec->ea2;
  if (opnd != (ea *)0x0) {
    old_base2 = opnd->base;
    shift_ea_registers(opnd);
  }
  if ((((((rec->tmp != old_tmp) && ((old_tmp < '\x04' || ('\a' < old_tmp)))) &&
        ((old_tmp < '\x14' || (g_current_request->scratch_bank_reg_count + 0x13 < (int)old_tmp))))
       && ((old_tmp < '$' || (g_current_request->scratch_bank_reg_count + 0x23 < (int)old_tmp)))) ||
      (((((rec->ea1 != (ea *)0x0 && (rec->ea1->base != old_base1)) &&
         ((old_base1 < '\x04' || ('\a' < old_base1)))) &&
        ((old_base1 < '\x14' || (g_current_request->scratch_bank_reg_count + 0x13 < (int)old_base1))
        )) && ((old_base1 < '$' ||
               (g_current_request->scratch_bank_reg_count + 0x23 < (int)old_base1)))))) ||
     (((rec->ea2 != (ea *)0x0 && (rec->ea2->base != old_base2)) &&
      ((((old_base2 < '\x04' || ('\a' < old_base2)) &&
        ((old_base2 < '\x14' || (g_current_request->scratch_bank_reg_count + 0x13 < (int)old_base2))
        )) && ((old_base2 < '$' ||
               (g_current_request->scratch_bank_reg_count + 0x23 < (int)old_base2)))))))) {
    rec->misc = rec->misc | 0x10;
  }
  if (((*(unsigned char *)((char *)&g_stage_flags + 1)) & 1) != 0) {
    _printf(s_______after_register_shift__ea1__004267e0);
    _printf(s_tempreg__d_00426868,(int)rec->tmp);
    if (rec->ea1 != (ea *)0x0) {
      _printf(s_basereg__d_00426858,(int)rec->ea1->base);
      _printf(s_indexreg__d_00426848,(int)rec->ea1->index);
    }
    if (rec->ea2 != (ea *)0x0) {
      _printf(s_______after_register_shift__ea2__004267b4);
      _printf(s_basereg__d_00426858,(int)rec->ea2->base);
      _printf(s_indexreg__d_0042680c,(int)rec->ea2->index);
    }
  }
  return;
}
