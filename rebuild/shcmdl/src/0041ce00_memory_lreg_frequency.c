#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_debug_flags
#define g_debug_flags (*(unsigned char *)(g_sd + 0x267c0))


// entry: 0041ce00
// name : memory_lreg_frequency
// size : 270
// sig  : int memory_lreg_frequency(lreg * lr)


int __cdecl memory_lreg_frequency(lreg *lr)

{
  int iVar1;
  uint weight;
  int iVar2;
  int iVar3;
  int total;
  void *ref;
  short set_kind;
  undefined4 *use;
  
  total = 0;
  set_kind = lr->set;
  if (set_kind != 0) {
    if (set_kind == 1) {
      for (ref = lr->chain; ref != (void *)0x0; ref = *(void **)((int)ref + 8)) {
        weight = 0;
        iVar1 = *(int *)((int)ref + 0x10);
        if (*(int *)(iVar1 + 0x3c) == iVar1) {
          weight = (uint)*(ushort *)(iVar1 + 0x5c);
        }
        iVar1 = *(int *)(*(int *)((int)ref + 0xc) + 0x30);
        if (iVar1 != 0) {
          iVar2 = 2;
          iVar3 = *(int *)(iVar1 + 0x14);
          while (iVar3 != 0) {
            iVar2 = iVar2 + 1;
            iVar1 = *(int *)(iVar1 + 0x14);
            iVar3 = *(int *)(iVar1 + 0x14);
          }
          weight = iVar2 * weight;
        }
        total = total + weight;
      }
      goto LAB_0041ceba;
    }
    if (set_kind != 2) goto LAB_0041ceba;
  }
  for (use = *(undefined4 **)((int)lr->chain + 8); use != (undefined4 *)0x0;
      use = (undefined4 *)*use) {
    iVar1 = *(int *)(use[1] + 0x30);
    if (iVar1 == 0) {
      iVar3 = 1;
    }
    else {
      iVar3 = 2;
      iVar2 = *(int *)(iVar1 + 0x14);
      while (iVar2 != 0) {
        iVar3 = iVar3 + 1;
        iVar1 = *(int *)(iVar1 + 0x14);
        iVar2 = *(int *)(iVar1 + 0x14);
      }
    }
    if ((*(int *)(use[2] + 0x3c) == 0) || (weight = (uint)*(ushort *)(use[2] + 0x5c), weight == 0))
    {
      weight = 1;
    }
    total = total + weight * iVar3;
  }
LAB_0041ceba:
  if (((*(unsigned char *)((char *)&g_debug_flags + 3)) & 2) != 0) {
    FID_conflict__wprintf(s________memid_freq________00435b94);
    FID_conflict__wprintf
              (s_setdata__d_pregno__d_lregno__d_f_00435b64,(int)lr->set,(int)lr->pregno,
               (int)lr->lregno,total);
    if (lr->set == 0) {
      FID_conflict__wprintf(s_cont__d_00435b58,(int)*(short *)lr->chain);
    }
  }
  return total;
}



