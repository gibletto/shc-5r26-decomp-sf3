#include "decls.h"
#include "imports.h"

// entry: 00403170
// name : merge_bound_lreg
// size : 475
// sig  : void merge_bound_lreg(lreg * dst, lreg * src)


int __cdecl merge_bound_lreg(lreg *dst,lreg *src)

{
  undefined4 *puVar1;
  int iVar2;
  int *piVar3;
  undefined4 *puVar4;
  int *piVar5;
  undefined4 *puVar6;
  int *piVar7;
  undefined4 *clash;
  void *dst_chain;
  bool seen;
  
  puVar1 = src->chain;
  iVar2 = puVar1[2];
  while (iVar2 != 0) {
    puVar1 = (undefined4 *)puVar1[2];
    iVar2 = puVar1[2];
  }
  piVar3 = src->life;
  iVar2 = *piVar3;
  while (puVar6 = puVar1, iVar2 != 0) {
    piVar3 = (int *)*piVar3;
    iVar2 = *piVar3;
  }
LAB_004031bd:
  puVar4 = src->clashed;
  while (clash = puVar4, clash != (undefined4 *)0x0) {
    piVar5 = dst->clashed;
    if (piVar5 != (int *)0x0) {
      do {
        if (piVar5[1] == clash[1]) {
          if (src->clashed == clash) {
            src->clashed = (void *)*clash;
            pool_free(clash,8);
            goto LAB_004031bd;
          }
          *puVar6 = (void *)*clash;
          pool_free(clash,8);
          clash = puVar6;
          break;
        }
        piVar5 = (int *)*piVar5;
      } while (piVar5 != (int *)0x0);
    }
    puVar6 = clash;
    puVar4 = (undefined4 *)*clash;
  }
  piVar5 = src->clashed;
  do {
    piVar7 = piVar5;
    if (piVar7 == (int *)0x0) break;
    piVar5 = (int *)*piVar7;
  } while ((int *)*piVar7 != (int *)0x0);
  dst_chain = dst->chain;
  puVar1[2] = dst_chain;
  dst->chain = src->chain;
  *piVar3 = (int)dst->life;
  dst->life = src->life;
  src->chain = dst_chain;
  if (piVar7 != (int *)0x0) {
    *piVar7 = (int)dst->clashed;
    dst->clashed = src->clashed;
  }
  src->clashed = (void *)0x0;
  src->life = (void *)0x0;
  src->set = 3;
  dst->priori = dst->priori + src->priori + -2;
  piVar3 = dst->clashed;
joined_r0x00403267:
  piVar5 = piVar3;
  if (piVar5 == (int *)0x0) {
    for (puVar1 = dst->clashed; puVar1 != (undefined4 *)0x0; puVar1 = (undefined4 *)*puVar1) {
      for (puVar6 = *(undefined4 **)(puVar1[1] + 0x10); puVar6 != (undefined4 *)0x0;
          puVar6 = (undefined4 *)*puVar6) {
        if ((lreg *)puVar6[1] == src) {
          puVar6[1] = dst;
        }
      }
      seen = false;
      puVar6 = *(undefined4 **)(puVar1[1] + 0x10);
      while (puVar4 = puVar6, puVar4 != (undefined4 *)0x0) {
        if ((*(undefined4 **)(puVar1[1] + 0x10) == puVar4) && ((lreg *)puVar4[1] == dst)) {
          seen = true;
        }
        puVar6 = (undefined4 *)*puVar4;
        if ((puVar6 != (void *)0x0) && ((lreg *)puVar6[1] == dst)) {
          if (seen) {
            *puVar4 = *puVar6;
            pool_free(puVar6,8);
            puVar6 = puVar4;
          }
          else {
            seen = true;
          }
        }
      }
    }
    return;
  }
  piVar3 = (int *)*piVar5;
  if ((piVar3 == (int *)0x0) || ((dst != (lreg *)piVar3[1] && (src != (lreg *)piVar3[1]))))
  goto LAB_00403296;
  *piVar5 = *piVar3;
  piVar7 = piVar5;
  piVar5 = piVar3;
  goto LAB_004032af;
LAB_00403296:
  if ((dst == (lreg *)piVar5[1]) || (src == (lreg *)piVar5[1])) {
    dst->clashed = piVar3;
    piVar7 = piVar3;
LAB_004032af:
    pool_free(piVar5,8);
    piVar3 = piVar7;
  }
  goto joined_r0x00403267;
}



