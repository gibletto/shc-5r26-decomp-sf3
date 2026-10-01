#include "decls.h"
#include "imports.h"

// entry: 00432410
// name : format_type_back_reference
// size : 188
// sig  : short format_type_back_reference(char * mangled, char * dst, int * consumed)


short __cdecl format_type_back_reference(char *mangled,char *dst,int *consumed)

{
  unsigned char _frec_14[20];
#define ref_no (*(int *)(_frec_14 + 0))
#define digit_count (*(int *)(_frec_14 + 4))
#define digits (*(byte (*)[12])(_frec_14 + 8))
  char cVar1;
  byte bVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  byte abStackY_800c [32736];
  short i;
  
  cVar1 = mangled[1];
  i = 0;
  while (cVar1 != '\0') {
    bVar2 = mangled[i + 1];
    if ((bVar2 < 0x30) || (0x39 < bVar2)) break;
    digits[i] = bVar2;
    cVar1 = mangled[(short)(i + 1) + 1];
    i = i + 1;
  }
  digits[i] = 0;
  parse_decimal_digits((char *)digits,&ref_no,&digit_count);
  if (ref_no == 0) {
    return -1;
  }
  if (*(short *)(&DAT_00450398 + ref_no * 8) == 0) {
    return -1;
  }
  uVar3 = 0xffffffff;
  pcVar5 = *(char **)(&DAT_0045039c + ref_no * 8);
  do {
    pcVar6 = pcVar5;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar6 = pcVar5 + 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar6;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  pcVar5 = pcVar6 + -uVar3;
  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)dst = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    dst = dst + 4;
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *dst = *pcVar5;
    pcVar5 = pcVar5 + 1;
    dst = dst + 1;
  }
  *consumed = digit_count + 1;
  return 0;
#undef ref_no
#undef digit_count
#undef digits
}



