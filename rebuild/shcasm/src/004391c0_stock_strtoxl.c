#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef stock_pctype
#define stock_pctype (*(unsigned char * *)(g_sd + 0x8ca0))


// entry: 004391c0
// name : stock_strtoxl
// size : 581
// sig  : uint stock_strtoxl(byte * param_1, undefined4 * param_2, uint param_3, uint param_4)


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint __cdecl stock_strtoxl(byte *param_1,undefined4 *param_2,uint param_3,uint param_4)

{
  uint uVar1;
  uint digit;
  int upper;
  byte ch;
  byte *p;
  uint number;
  byte *cur;
  
  ch = *param_1;
  number = 0;
  cur = param_1;
  while( true ) {
    p = cur + 1;
    if (stock_mb_cur_max < 2) {
      uVar1 = *(ushort *)(stock_pctype + (uint)ch * 2) & 8;
    }
    else {
      uVar1 = __isctype((uint)ch,8);
    }
    if (uVar1 == 0) break;
    ch = *p;
    cur = p;
  }
  if (ch == 0x2d) {
    ch = *p;
    param_4 = param_4 | 2;
    p = cur + 2;
  }
  else if (ch == 0x2b) {
    ch = *p;
    p = cur + 2;
  }
  if ((((int)param_3 < 0) || (param_3 == 1)) || (0x24 < (int)param_3)) {
    if (param_2 != (undefined4 *)0x0) {
      *param_2 = param_1;
    }
    return 0;
  }
  if (param_3 == 0) {
    if (ch == 0x30) {
      if ((*p == 0x78) || (*p == 0x58)) {
        param_3 = 0x10;
      }
      else {
        param_3 = 8;
      }
    }
    else {
      param_3 = 10;
    }
  }
  if (((param_3 == 0x10) && (ch == 0x30)) && ((*p == 0x78 || (*p == 0x58)))) {
    ch = p[1];
    p = p + 2;
  }
  uVar1 = (uint)(0xffffffff / (ulonglong)param_3);
  do {
    if (stock_mb_cur_max < 2) {
      digit = *(ushort *)(stock_pctype + (uint)ch * 2) & 4;
    }
    else {
      digit = __isctype((uint)ch,4);
    }
    if (digit == 0) {
      if (stock_mb_cur_max < 2) {
        digit = *(ushort *)(stock_pctype + (uint)ch * 2) & 0x103;
      }
      else {
        digit = __isctype((uint)ch,0x103);
      }
      if (digit == 0) {
LAB_0043935e:
        p = p + -1;
        if ((param_4 & 8) == 0) {
          if (param_2 != (undefined4 *)0x0) {
            p = param_1;
          }
          number = 0;
        }
        else if (((param_4 & 4) != 0) ||
                (((param_4 & 1) == 0 &&
                 ((((param_4 & 2) != 0 && (0x80000000 < number)) ||
                  (((param_4 & 2) == 0 && (0x7fffffff < number)))))))) {
          _stock_errno = 0x22;
          if ((param_4 & 1) == 0) {
            if ((param_4 & 2) == 0) {
              number = 0x7fffffff;
            }
            else {
              number = 0x80000000;
            }
          }
          else {
            number = 0xffffffff;
          }
        }
        if (param_2 != (undefined4 *)0x0) {
          *param_2 = p;
        }
        if ((param_4 & 2) != 0) {
          number = -number;
        }
        return number;
      }
      upper = FID_conflict___toupper_lk((int)(char)ch);
      digit = upper - 0x37;
    }
    else {
      digit = (int)(char)ch - 0x30;
    }
    if (param_3 <= digit) goto LAB_0043935e;
    if ((number < uVar1) ||
       ((uVar1 == number && (digit <= (uint)(0xffffffff % (ulonglong)param_3))))) {
      ch = *p;
      p = p + 1;
      number = number * param_3 + digit;
      param_4 = param_4 | 8;
    }
    else {
      ch = *p;
      p = p + 1;
      param_4 = param_4 | 0xc;
    }
  } while( true );
}



