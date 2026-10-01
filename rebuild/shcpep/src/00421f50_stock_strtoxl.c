#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef stock_pctype
#define stock_pctype (*(unsigned char * *)(g_sd + 0x4f48))


// entry: 00421f50
// name : stock_strtoxl
// size : 581
// sig  : uint stock_strtoxl(byte * nptr, undefined4 * endptr, uint ibase, uint flags)


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint __cdecl stock_strtoxl(byte *nptr,undefined4 *endptr,uint ibase,uint flags)

{
  byte *pbVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  byte bVar5;
  byte *pbVar6;
  uint uVar7;
  
  bVar5 = *nptr;
  uVar7 = 0;
  pbVar1 = nptr;
  while( true ) {
    pbVar6 = pbVar1 + 1;
    if (stock_mb_cur_max < 2) {
      uVar2 = *(ushort *)(stock_pctype + (uint)bVar5 * 2) & 8;
    }
    else {
      uVar2 = __isctype((uint)bVar5,8);
    }
    if (uVar2 == 0) break;
    bVar5 = *pbVar6;
    pbVar1 = pbVar6;
  }
  if (bVar5 == 0x2d) {
    bVar5 = *pbVar6;
    flags = flags | 2;
    pbVar6 = pbVar1 + 2;
  }
  else if (bVar5 == 0x2b) {
    bVar5 = *pbVar6;
    pbVar6 = pbVar1 + 2;
  }
  if ((((int)ibase < 0) || (ibase == 1)) || (0x24 < (int)ibase)) {
    if (endptr != (undefined4 *)0x0) {
      *endptr = nptr;
    }
    return 0;
  }
  if (ibase == 0) {
    if (bVar5 == 0x30) {
      if ((*pbVar6 == 0x78) || (*pbVar6 == 0x58)) {
        ibase = 0x10;
      }
      else {
        ibase = 8;
      }
    }
    else {
      ibase = 10;
    }
  }
  if (((ibase == 0x10) && (bVar5 == 0x30)) && ((*pbVar6 == 0x78 || (*pbVar6 == 0x58)))) {
    bVar5 = pbVar6[1];
    pbVar6 = pbVar6 + 2;
  }
  uVar2 = (uint)(0xffffffff / (ulonglong)ibase);
  do {
    if (stock_mb_cur_max < 2) {
      uVar3 = *(ushort *)(stock_pctype + (uint)bVar5 * 2) & 4;
    }
    else {
      uVar3 = __isctype((uint)bVar5,4);
    }
    if (uVar3 == 0) {
      if (stock_mb_cur_max < 2) {
        uVar3 = *(ushort *)(stock_pctype + (uint)bVar5 * 2) & 0x103;
      }
      else {
        uVar3 = __isctype((uint)bVar5,0x103);
      }
      if (uVar3 == 0) {
LAB_004220ee:
        pbVar6 = pbVar6 + -1;
        if ((flags & 8) == 0) {
          if (endptr != (undefined4 *)0x0) {
            pbVar6 = nptr;
          }
          uVar7 = 0;
        }
        else if (((flags & 4) != 0) ||
                (((flags & 1) == 0 &&
                 ((((flags & 2) != 0 && (0x80000000 < uVar7)) ||
                  (((flags & 2) == 0 && (0x7fffffff < uVar7)))))))) {
          _stock_errno = 0x22;
          if ((flags & 1) == 0) {
            if ((flags & 2) == 0) {
              uVar7 = 0x7fffffff;
            }
            else {
              uVar7 = 0x80000000;
            }
          }
          else {
            uVar7 = 0xffffffff;
          }
        }
        if (endptr != (undefined4 *)0x0) {
          *endptr = pbVar6;
        }
        if ((flags & 2) != 0) {
          uVar7 = -uVar7;
        }
        return uVar7;
      }
      iVar4 = FID_conflict___toupper_lk((int)(char)bVar5);
      uVar3 = iVar4 - 0x37;
    }
    else {
      uVar3 = (int)(char)bVar5 - 0x30;
    }
    if (ibase <= uVar3) goto LAB_004220ee;
    if ((uVar7 < uVar2) || ((uVar2 == uVar7 && (uVar3 <= (uint)(0xffffffff % (ulonglong)ibase))))) {
      bVar5 = *pbVar6;
      pbVar6 = pbVar6 + 1;
      uVar7 = uVar7 * ibase + uVar3;
      flags = flags | 8;
    }
    else {
      bVar5 = *pbVar6;
      pbVar6 = pbVar6 + 1;
      flags = flags | 0xc;
    }
  } while( true );
}



