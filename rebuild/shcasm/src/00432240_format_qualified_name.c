#include "decls.h"
#include "imports.h"

// entry: 00432240
// name : format_qualified_name
// size : 307
// sig  : short format_qualified_name(char * mangled, char * dst, int * consumed)


short __cdecl format_qualified_name(char *mangled,char *dst,int *consumed)

{
  unsigned char _frec_24[36];
#define part_count (*(int *)(_frec_24 + 0))
#define part_no (*(int *)(_frec_24 + 4))
#define digit_count (*(int *)(_frec_24 + 8))
#define part_len (*(int *)(_frec_24 + 12))
#define digits (*(byte (*)[20])(_frec_24 + 16))
  char cVar1;
  byte bVar2;
  short sVar3;
  int pos;
  uint uVar4;
  int iVar5;
  uint uVar6;
  char *pcVar7;
  char *pcVar8;
  char *pcVar9;
  
  *dst = '\0';
  cVar1 = mangled[1];
  for (pos = 0; ((cVar1 != '\0' && (bVar2 = mangled[pos + 1], 0x2f < bVar2)) && (bVar2 < 0x3a));
      pos = pos + 1) {
    digits[pos] = bVar2;
    cVar1 = mangled[pos + 2];
  }
  digits[pos] = 0;
  parse_decimal_digits((char *)digits,&part_count,&digit_count);
  if (part_count == 0) {
    return -1;
  }
  part_no = 0;
  pos = digit_count + 3;
  if (0 < part_count) {
    do {
      sVar3 = parse_length_prefixed_name
                        (mangled + pos,(char *)&g_demangle_qualified_component,&part_len);
      if (sVar3 != 0) {
        return sVar3;
      }
      pos = pos + part_len;
      uVar4 = 0xffffffff;
      pcVar7 = (char *)&g_demangle_qualified_component;
      do {
        pcVar9 = pcVar7;
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        pcVar9 = pcVar7 + 1;
        cVar1 = *pcVar7;
        pcVar7 = pcVar9;
      } while (cVar1 != '\0');
      uVar4 = ~uVar4;
      iVar5 = -1;
      pcVar7 = dst;
      do {
        pcVar8 = pcVar7;
        if (iVar5 == 0) break;
        iVar5 = iVar5 + -1;
        pcVar8 = pcVar7 + 1;
        cVar1 = *pcVar7;
        pcVar7 = pcVar8;
      } while (cVar1 != '\0');
      pcVar7 = pcVar9 + -uVar4;
      pcVar9 = pcVar8 + -1;
      for (uVar6 = uVar4 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
        *(undefined4 *)pcVar9 = *(undefined4 *)pcVar7;
        pcVar7 = pcVar7 + 4;
        pcVar9 = pcVar9 + 4;
      }
      for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *pcVar9 = *pcVar7;
        pcVar7 = pcVar7 + 1;
        pcVar9 = pcVar9 + 1;
      }
      if (part_count - part_no != 1) {
        uVar4 = 0xffffffff;
        pcVar7 = (char *)&s_scope_separator;
        do {
          pcVar9 = pcVar7;
          if (uVar4 == 0) break;
          uVar4 = uVar4 - 1;
          pcVar9 = pcVar7 + 1;
          cVar1 = *pcVar7;
          pcVar7 = pcVar9;
        } while (cVar1 != '\0');
        uVar4 = ~uVar4;
        iVar5 = -1;
        pcVar7 = dst;
        do {
          pcVar8 = pcVar7;
          if (iVar5 == 0) break;
          iVar5 = iVar5 + -1;
          pcVar8 = pcVar7 + 1;
          cVar1 = *pcVar7;
          pcVar7 = pcVar8;
        } while (cVar1 != '\0');
        pcVar7 = pcVar9 + -uVar4;
        pcVar9 = pcVar8 + -1;
        for (uVar6 = uVar4 >> 2; uVar6 != 0; uVar6 = uVar6 - 1) {
          *(undefined4 *)pcVar9 = *(undefined4 *)pcVar7;
          pcVar7 = pcVar7 + 4;
          pcVar9 = pcVar9 + 4;
        }
        for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
          *pcVar9 = *pcVar7;
          pcVar7 = pcVar7 + 1;
          pcVar9 = pcVar9 + 1;
        }
      }
      part_no = part_no + 1;
    } while (part_no < part_count);
  }
  *consumed = pos;
  return 0;
#undef part_count
#undef part_no
#undef digit_count
#undef part_len
#undef digits
}



