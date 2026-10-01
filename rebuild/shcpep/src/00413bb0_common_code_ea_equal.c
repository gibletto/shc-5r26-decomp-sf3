#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_stage_flags
#define g_stage_flags (*(unsigned char *)(g_sd + 0x6d64))


// entry: 00413bb0
// name : common_code_ea_equal
// size : 290
// sig  : short common_code_ea_equal(ea * a, ea * b)


short __cdecl common_code_ea_equal(ea *a,ea *b)

{
  int iVar1;
  label_ref *ref_a;
  ea *peVar2;
  short sVar3;
  
  sVar3 = 0;
  if (((byte)g_stage_flags & 0x10) != 0) {
    _printf(s_dc_eacmp_start__00427808);
  }
  if ((a == (ea *)0x0) || (b == (ea *)0x0)) {
LAB_00413c7c:
    peVar2 = a;
    if (a != b) goto LAB_00413c88;
joined_r0x00413c82:
    if (peVar2 != (ea *)0x0) goto LAB_00413c88;
  }
  else {
    if (((((a->type ^ b->type) & 0x1f) != 0) ||
        (((a->type != b->type || (a->base != b->base)) || (a->index != b->index)))) ||
       (a->disp != b->disp)) goto LAB_00413c7c;
    ref_a = a->labels;
    if ((ref_a != (label_ref *)0x0) && (peVar2 = (ea *)b->labels, peVar2 != (ea *)0x0)) {
      if ((ref_a->next == (label_ref *)0x0) ||
         ((*(unsigned char *)((char *)&iVar1 + 0)) = peVar2->type, (*(unsigned char *)((char *)&iVar1 + 1)) = peVar2->base, (*(unsigned char *)((char *)&iVar1 + 2)) = peVar2->index,
         (*(unsigned char *)((char *)&iVar1 + 3)) = peVar2->misc, iVar1 == 0)) {
        if (((*(label_ref **)&peVar2->type != ref_a->next) || (ref_a->labno1 != (short)peVar2->disp)
            ) || (ref_a->labno2 != *(short *)((int)&peVar2->disp + 2))) goto LAB_00413c88;
        goto LAB_00413c84;
      }
      if (ref_a != (label_ref *)0x0) {
        do {
          if (((peVar2 == (ea *)0x0) || ((short)peVar2->disp != ref_a->labno1)) ||
             (*(short *)((int)&peVar2->disp + 2) != ref_a->labno2)) break;
          ref_a = ref_a->next;
          peVar2 = *(ea **)&peVar2->type;
        } while (ref_a != (label_ref *)0x0);
        if (ref_a != (label_ref *)0x0) goto LAB_00413c88;
      }
      goto joined_r0x00413c82;
    }
    if (b->labels != ref_a) goto LAB_00413c88;
  }
LAB_00413c84:
  sVar3 = 1;
LAB_00413c88:
  if (((byte)g_stage_flags & 0x10) != 0) {
    _printf(s_dc_eacmp_end__rc___d_004277f0,(int)sVar3);
  }
  if (((byte)g_stage_flags & 4) != 0) {
    dump_memory_hex(&a->type,s_eatbl_1_00425c80,0xc);
    dump_memory_hex(&b->type,s_eatbl_2_00425c78,0xc);
  }
  return sVar3;
}



