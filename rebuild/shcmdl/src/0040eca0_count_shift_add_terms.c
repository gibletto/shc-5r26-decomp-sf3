#include "decls.h"
#include "imports.h"

// entry: 0040eca0
// name : count_shift_add_terms
// size : 288
// sig  : int count_shift_add_terms(char * digits, uint value, int is_signed)


int __cdecl count_shift_add_terms(char *digits,uint value,int is_signed)

{
  int ndigits;
  int iVar1;
  uint uVar2;
  uint words;
  int iVar3;
  int j;
  char *dst;
  bool changed;
  char *digit;
  uint is_unsigned;
  
  if ((is_signed != 0) && ((int)value < 0)) {
    return 0;
  }
  is_unsigned = (uint)(is_signed == 0);
  ndigits = is_unsigned + 0x1e;
  iVar3 = 0;
  do {
    iVar1 = iVar3 + 1;
    digits[iVar3] = '\x01' - ((1 << ((byte)iVar3 & 0x1f) & value) == 0);
    iVar3 = iVar1;
  } while (iVar1 < 0x20);
  do {
    changed = false;
    iVar3 = 0;
    if (is_unsigned != 0xffffffe2) {
      do {
        digit = digits + iVar3;
        if ((*digit == '\x01') && (digit[1] != '\x01')) {
          iVar1 = 1;
          j = iVar3 + -1;
          while ((-1 < j && (digits[iVar3 - iVar1] == '\x01'))) {
            iVar1 = iVar1 + 1;
            j = iVar3 - iVar1;
          }
          if (iVar1 != 1) {
            if (iVar1 == 2) {
              if ((ndigits <= iVar3 + 2) || ((digit[2] != '\x01' && (digit[1] != -1))))
              goto LAB_0040ed8c;
              digit[-1] = -1;
              *digit = '\0';
            }
            else {
              uVar2 = iVar1 - 1;
              digits[iVar3 - uVar2] = -1;
              if (-1 < iVar1 + -2) {
                dst = digits + (iVar3 - (iVar1 + -2));
                for (words = uVar2 >> 2; words != 0; words = words - 1) {
                  dst[0] = '\0';
                  dst[1] = '\0';
                  dst[2] = '\0';
                  dst[3] = '\0';
                  dst = dst + 4;
                }
                for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
                  *dst = '\0';
                  dst = dst + 1;
                }
              }
            }
            changed = true;
            digit[1] = '\x01' - (digit[1] == -1);
          }
        }
LAB_0040ed8c:
        iVar3 = iVar3 + 1;
      } while (iVar3 < ndigits);
    }
    if (!changed) {
      iVar1 = 0;
      iVar3 = 0;
      if (ndigits != -1) {
        do {
          if (digits[iVar1] != '\0') {
            iVar3 = iVar3 + 1;
          }
          iVar1 = iVar1 + 1;
        } while (iVar1 < (int)(is_unsigned + 0x1f));
      }
      return iVar3;
    }
  } while( true );
}



