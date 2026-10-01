#include "decls.h"
#include "imports.h"

// entry: 0042fa80
// name : format_class_scope_prefix
// size : 498
// sig  : ushort format_class_scope_prefix(char * class_code, char * scope, char * class_name)


ushort __cdecl format_class_scope_prefix(char *class_code,char *scope,char *class_name)

{
  unsigned char _frec_24[36];
#define part_count (*(int *)(_frec_24 + 0))
#define part_no (*(int *)(_frec_24 + 4))
#define part_len (*(int *)(_frec_24 + 8))
#define digit_count (*(int *)(_frec_24 + 12))
#define digits (*(byte (*)[20])(_frec_24 + 16))
  char cVar1;
  byte bVar2;
  ushort uVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  char *pcVar8;
  char *pcVar9;
  char *pcVar10;
  
  iVar4 = 0;
  *scope = '\0';
  if (*class_code != 'Q') {
    uVar3 = parse_length_prefixed_name(class_code,(char *)&g_demangle_name_scratch,&part_len);
    if (uVar3 == 0) {
      uVar5 = 0xffffffff;
      pcVar9 = (char *)&g_demangle_name_scratch;
      do {
        pcVar8 = pcVar9;
        if (uVar5 == 0) break;
        uVar5 = uVar5 - 1;
        pcVar8 = pcVar9 + 1;
        cVar1 = *pcVar9;
        pcVar9 = pcVar8;
      } while (cVar1 != '\0');
      uVar5 = ~uVar5;
      pcVar9 = pcVar8 + -uVar5;
      pcVar8 = scope;
      for (uVar7 = uVar5 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
        *(undefined4 *)pcVar8 = *(undefined4 *)pcVar9;
        pcVar9 = pcVar9 + 4;
        pcVar8 = pcVar8 + 4;
      }
      for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
        *pcVar8 = *pcVar9;
        pcVar9 = pcVar9 + 1;
        pcVar8 = pcVar8 + 1;
      }
      uVar5 = 0xffffffff;
      pcVar9 = (char *)&s_scope_separator;
      do {
        pcVar8 = pcVar9;
        if (uVar5 == 0) break;
        uVar5 = uVar5 - 1;
        pcVar8 = pcVar9 + 1;
        cVar1 = *pcVar9;
        pcVar9 = pcVar8;
      } while (cVar1 != '\0');
      uVar5 = ~uVar5;
      iVar4 = -1;
      do {
        pcVar9 = scope;
        if (iVar4 == 0) break;
        iVar4 = iVar4 + -1;
        pcVar9 = scope + 1;
        cVar1 = *scope;
        scope = pcVar9;
      } while (cVar1 != '\0');
      pcVar8 = pcVar8 + -uVar5;
      pcVar9 = pcVar9 + -1;
      for (uVar7 = uVar5 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
        *(undefined4 *)pcVar9 = *(undefined4 *)pcVar8;
        pcVar8 = pcVar8 + 4;
        pcVar9 = pcVar9 + 4;
      }
      for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
        *pcVar9 = *pcVar8;
        pcVar8 = pcVar8 + 1;
        pcVar9 = pcVar9 + 1;
      }
      uVar5 = 0xffffffff;
      pcVar9 = (char *)&g_demangle_name_scratch;
      do {
        pcVar8 = pcVar9;
        if (uVar5 == 0) break;
        uVar5 = uVar5 - 1;
        pcVar8 = pcVar9 + 1;
        cVar1 = *pcVar9;
        pcVar9 = pcVar8;
      } while (cVar1 != '\0');
      uVar5 = ~uVar5;
      pcVar9 = pcVar8 + -uVar5;
      for (uVar7 = uVar5 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
        *(undefined4 *)class_name = *(undefined4 *)pcVar9;
        pcVar9 = pcVar9 + 4;
        class_name = class_name + 4;
      }
      for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
        *class_name = *pcVar9;
        pcVar9 = pcVar9 + 1;
        class_name = class_name + 1;
      }
      uVar3 = 0;
    }
    return uVar3;
  }
  cVar1 = class_code[1];
  for (; ((cVar1 != '\0' && (bVar2 = class_code[iVar4 + 1], 0x2f < bVar2)) && (bVar2 < 0x3a));
      iVar4 = iVar4 + 1) {
    digits[iVar4] = bVar2;
    cVar1 = class_code[iVar4 + 2];
  }
  digits[iVar4] = 0;
  parse_decimal_digits((char *)digits,&part_count,&digit_count);
  if (part_count == 0) {
    return 0xffff;
  }
  part_no = 0;
  iVar4 = digit_count + 3;
  if (0 < part_count) {
    do {
      uVar3 = parse_length_prefixed_name
                        (class_code + iVar4,(char *)&g_demangle_name_scratch,&part_len);
      if (uVar3 != 0) {
        return uVar3;
      }
      iVar4 = iVar4 + part_len;
      uVar5 = 0xffffffff;
      pcVar9 = (char *)&g_demangle_name_scratch;
      do {
        pcVar8 = pcVar9;
        if (uVar5 == 0) break;
        uVar5 = uVar5 - 1;
        pcVar8 = pcVar9 + 1;
        cVar1 = *pcVar9;
        pcVar9 = pcVar8;
      } while (cVar1 != '\0');
      uVar5 = ~uVar5;
      iVar6 = -1;
      pcVar9 = scope;
      do {
        pcVar10 = pcVar9;
        if (iVar6 == 0) break;
        iVar6 = iVar6 + -1;
        pcVar10 = pcVar9 + 1;
        cVar1 = *pcVar9;
        pcVar9 = pcVar10;
      } while (cVar1 != '\0');
      pcVar9 = pcVar8 + -uVar5;
      pcVar8 = pcVar10 + -1;
      for (uVar7 = uVar5 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
        *(undefined4 *)pcVar8 = *(undefined4 *)pcVar9;
        pcVar9 = pcVar9 + 4;
        pcVar8 = pcVar8 + 4;
      }
      for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
        *pcVar8 = *pcVar9;
        pcVar9 = pcVar9 + 1;
        pcVar8 = pcVar8 + 1;
      }
      uVar5 = 0xffffffff;
      pcVar9 = (char *)&s_scope_separator;
      do {
        pcVar8 = pcVar9;
        if (uVar5 == 0) break;
        uVar5 = uVar5 - 1;
        pcVar8 = pcVar9 + 1;
        cVar1 = *pcVar9;
        pcVar9 = pcVar8;
      } while (cVar1 != '\0');
      uVar5 = ~uVar5;
      iVar6 = -1;
      pcVar9 = scope;
      do {
        pcVar10 = pcVar9;
        if (iVar6 == 0) break;
        iVar6 = iVar6 + -1;
        pcVar10 = pcVar9 + 1;
        cVar1 = *pcVar9;
        pcVar9 = pcVar10;
      } while (cVar1 != '\0');
      pcVar9 = pcVar8 + -uVar5;
      pcVar8 = pcVar10 + -1;
      for (uVar7 = uVar5 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
        *(undefined4 *)pcVar8 = *(undefined4 *)pcVar9;
        pcVar9 = pcVar9 + 4;
        pcVar8 = pcVar8 + 4;
      }
      for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
        *pcVar8 = *pcVar9;
        pcVar9 = pcVar9 + 1;
        pcVar8 = pcVar8 + 1;
      }
      part_no = part_no + 1;
    } while (part_no < part_count);
  }
  uVar5 = 0xffffffff;
  pcVar9 = (char *)&g_demangle_name_scratch;
  do {
    pcVar8 = pcVar9;
    if (uVar5 == 0) break;
    uVar5 = uVar5 - 1;
    pcVar8 = pcVar9 + 1;
    cVar1 = *pcVar9;
    pcVar9 = pcVar8;
  } while (cVar1 != '\0');
  uVar5 = ~uVar5;
  pcVar9 = pcVar8 + -uVar5;
  for (uVar7 = uVar5 >> 2; uVar7 != 0; uVar7 = uVar7 - 1) {
    *(undefined4 *)class_name = *(undefined4 *)pcVar9;
    pcVar9 = pcVar9 + 4;
    class_name = class_name + 4;
  }
  for (uVar5 = uVar5 & 3; uVar5 != 0; uVar5 = uVar5 - 1) {
    *class_name = *pcVar9;
    pcVar9 = pcVar9 + 1;
    class_name = class_name + 1;
  }
  return 0;
#undef part_count
#undef part_no
#undef part_len
#undef digit_count
#undef digits
}



