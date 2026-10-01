#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_stage_flags
#define g_stage_flags (*(unsigned char *)(g_sd + 0x6d64))


// entry: 00409840
// name : operands_equal
// size : 309
// sig  : char operands_equal(ea * a, ea * b)


char __cdecl operands_equal(ea *a,ea *b)

{
  label_ref *plVar1;
  byte kind;
  ea *a_ref;
  char equal;
  ea *peVar2;
  
  equal = '\0';
  if (((byte)g_stage_flags & 0x10) != 0) {
    _printf(s_opeacmp_start__00425c88);
  }
  if ((((a == (ea *)0x0) || (b == (ea *)0x0)) || (((b->type ^ a->type) & 0xdf) != 0)) ||
     (((kind = a->type & 0x1f, kind == 3 || (kind == 4)) ||
      ((b->base != a->base || ((b->index != a->index || (b->disp != a->disp)))))))) {
    peVar2 = a;
    if (b != a) goto LAB_0040992c;
joined_r0x00409928:
    if (peVar2 != (ea *)0x0) goto LAB_0040992c;
  }
  else {
    a_ref = (ea *)a->labels;
    if ((a_ref == (ea *)0x0) || (peVar2 = (ea *)b->labels, peVar2 == (ea *)0x0)) {
      peVar2 = a_ref;
      if ((ea *)b->labels != a_ref) goto LAB_0040992c;
      goto joined_r0x00409928;
    }
    plVar1 = *(label_ref **)&a_ref->type;
    if ((plVar1 != (label_ref *)0x0) && (*(label_ref **)&peVar2->type != (label_ref *)0x0)) {
      if (a_ref != (ea *)0x0) {
        do {
          if (((peVar2 == (ea *)0x0) || ((short)peVar2->disp != (short)a_ref->disp)) ||
             (*(short *)((int)&peVar2->disp + 2) != *(short *)((int)&a_ref->disp + 2))) break;
          a_ref = *(ea **)&a_ref->type;
          peVar2 = *(ea **)&peVar2->type;
        } while (a_ref != (ea *)0x0);
        if (a_ref != (ea *)0x0) goto LAB_0040992c;
      }
      goto joined_r0x00409928;
    }
    if (((*(label_ref **)&peVar2->type != plVar1) || (plVar1 != (label_ref *)0x0)) ||
       (((short)a_ref->disp != (short)peVar2->disp ||
        (*(short *)((int)&a_ref->disp + 2) != *(short *)((int)&peVar2->disp + 2)))))
    goto LAB_0040992c;
  }
  equal = '\x01';
LAB_0040992c:
  if (((byte)g_stage_flags & 4) != 0) {
    dump_memory_hex(&a->type,s_eatbl_1_00425c80,0xc);
    dump_memory_hex(&a->type,s_eatbl_2_00425c78,0xc);
  }
  if (((byte)g_stage_flags & 0x10) != 0) {
    _printf(s_opeacmp_end__rc___d_00425c60,(int)equal);
  }
  return equal;
}



