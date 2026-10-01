#include "decls.h"
#include "imports.h"

// entry: 00430f00
// name : parse_mangled_signature_kind
// size : 1189
// sig  : short parse_mangled_signature_kind(char * mangled, char * class_code, char * cv_codes, int * consumed)


short __cdecl parse_mangled_signature_kind(char *mangled,char *class_code,char *cv_codes,int *consumed)

{
  unsigned char _frec_108[264];
#define parsed_len (*(int *)(_frec_108 + 0))
#define cv_len (*(int *)(_frec_108 + 4))
#define class_name (*(char (*)[256])(_frec_108 + 8))
  char cVar1;
  short next_class;
  ushort uVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  char *pcVar6;
  char *pcVar7;
  
  *class_code = '\0';
  *consumed = 0;
  next_class = classify_mangle_code(mangled);
  switch(next_class) {
  case 1:
    if ((*mangled != 'C') && (*mangled != 'V')) {
      return -1;
    }
    iVar3 = copy_cv_qualifier_codes(mangled,cv_codes,&cv_len);
    if ((short)iVar3 != 0) {
      return -1;
    }
    if (mangled[cv_len] == 'F') {
      next_class = classify_mangle_code(mangled + cv_len + 1);
      if ((((next_class < 1) || (7 < next_class)) || (mangled[cv_len + 1] == 'F')) &&
         (next_class != 0xb)) {
        return -1;
      }
      *consumed = cv_len;
      return 5;
    }
    return -1;
  default:
    return -1;
  case 4:
    next_class = classify_mangle_code(mangled + 1);
    if ((((next_class < 1) || (7 < next_class)) || (mangled[1] == 'F')) && (next_class != 0xb)) {
      return -1;
    }
    return 0;
  case 5:
    break;
  case 0xb:
    next_class = copy_qualified_name_code(mangled,class_name,&parsed_len);
    if (next_class != 0) {
      return -1;
    }
    pcVar6 = mangled + parsed_len;
    cVar1 = *pcVar6;
    if (cVar1 != 'F') {
      if ((cVar1 == 'C') || (cVar1 == 'V')) {
        iVar3 = copy_cv_qualifier_codes(pcVar6,cv_codes,&cv_len);
        if ((short)iVar3 != 0) {
          return -1;
        }
        parsed_len = parsed_len + cv_len;
        if (mangled[parsed_len] != 'F') {
          return -1;
        }
        next_class = classify_mangle_code(mangled + parsed_len + 1);
        if ((((next_class < 1) || (7 < next_class)) || (mangled[parsed_len + 1] == 'F')) &&
           (next_class != 0xb)) {
          return -1;
        }
        uVar4 = 0xffffffff;
        pcVar6 = class_name;
        do {
          pcVar7 = pcVar6;
          if (uVar4 == 0) break;
          uVar4 = uVar4 - 1;
          pcVar7 = pcVar6 + 1;
          cVar1 = *pcVar6;
          pcVar6 = pcVar7;
        } while (cVar1 != '\0');
        uVar4 = ~uVar4;
        pcVar6 = pcVar7 + -uVar4;
        for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
          *(undefined4 *)class_code = *(undefined4 *)pcVar6;
          pcVar6 = pcVar6 + 4;
          class_code = class_code + 4;
        }
        for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
          *class_code = *pcVar6;
          pcVar6 = pcVar6 + 1;
          class_code = class_code + 1;
        }
        *consumed = parsed_len;
        return 6;
      }
      if (cVar1 != '\0') {
        return -1;
      }
      uVar4 = 0xffffffff;
      pcVar6 = class_name;
      do {
        pcVar7 = pcVar6;
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        pcVar7 = pcVar6 + 1;
        cVar1 = *pcVar6;
        pcVar6 = pcVar7;
      } while (cVar1 != '\0');
      uVar4 = ~uVar4;
      pcVar6 = pcVar7 + -uVar4;
      for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
        *(undefined4 *)class_code = *(undefined4 *)pcVar6;
        pcVar6 = pcVar6 + 4;
        class_code = class_code + 4;
      }
      for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *class_code = *pcVar6;
        pcVar6 = pcVar6 + 1;
        class_code = class_code + 1;
      }
      *consumed = parsed_len;
      return 4;
    }
    next_class = classify_mangle_code(pcVar6 + 1);
    if ((((next_class < 1) || (7 < next_class)) || (mangled[parsed_len + 1] == 'F')) &&
       (next_class != 0xb)) {
      return -1;
    }
    uVar4 = 0xffffffff;
    pcVar6 = class_name;
    do {
      pcVar7 = pcVar6;
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      pcVar7 = pcVar6 + 1;
      cVar1 = *pcVar6;
      pcVar6 = pcVar7;
    } while (cVar1 != '\0');
    uVar4 = ~uVar4;
    pcVar6 = pcVar7 + -uVar4;
    for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined4 *)class_code = *(undefined4 *)pcVar6;
      pcVar6 = pcVar6 + 4;
      class_code = class_code + 4;
    }
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *class_code = *pcVar6;
      pcVar6 = pcVar6 + 1;
      class_code = class_code + 1;
    }
    *consumed = parsed_len;
    return 1;
  }
  uVar2 = copy_length_prefixed_name(mangled,class_name,&parsed_len);
  if (uVar2 != 0) {
    return -1;
  }
  pcVar6 = mangled + parsed_len;
  cVar1 = *pcVar6;
  if (cVar1 != 'F') {
    if ((cVar1 == 'C') || (cVar1 == 'V')) {
      iVar3 = copy_cv_qualifier_codes(pcVar6,cv_codes,&cv_len);
      if ((short)iVar3 != 0) {
        return -1;
      }
      parsed_len = parsed_len + cv_len;
      if (mangled[parsed_len] != 'F') {
        return -1;
      }
      next_class = classify_mangle_code(mangled + parsed_len + 1);
      if ((((next_class < 1) || (7 < next_class)) || (mangled[parsed_len + 1] == 'F')) &&
         (next_class != 0xb)) {
        return -1;
      }
      uVar4 = 0xffffffff;
      pcVar6 = class_name;
      do {
        pcVar7 = pcVar6;
        if (uVar4 == 0) break;
        uVar4 = uVar4 - 1;
        pcVar7 = pcVar6 + 1;
        cVar1 = *pcVar6;
        pcVar6 = pcVar7;
      } while (cVar1 != '\0');
      uVar4 = ~uVar4;
      pcVar6 = pcVar7 + -uVar4;
      for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
        *(undefined4 *)class_code = *(undefined4 *)pcVar6;
        pcVar6 = pcVar6 + 4;
        class_code = class_code + 4;
      }
      for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *class_code = *pcVar6;
        pcVar6 = pcVar6 + 1;
        class_code = class_code + 1;
      }
      *consumed = parsed_len;
      return 7;
    }
    if (cVar1 != '\0') {
      return -1;
    }
    uVar4 = 0xffffffff;
    pcVar6 = class_name;
    do {
      pcVar7 = pcVar6;
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      pcVar7 = pcVar6 + 1;
      cVar1 = *pcVar6;
      pcVar6 = pcVar7;
    } while (cVar1 != '\0');
    uVar4 = ~uVar4;
    pcVar6 = pcVar7 + -uVar4;
    for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
      *(undefined4 *)class_code = *(undefined4 *)pcVar6;
      pcVar6 = pcVar6 + 4;
      class_code = class_code + 4;
    }
    for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
      *class_code = *pcVar6;
      pcVar6 = pcVar6 + 1;
      class_code = class_code + 1;
    }
    *consumed = parsed_len;
    return 3;
  }
  next_class = classify_mangle_code(pcVar6 + 1);
  if ((((next_class < 1) || (7 < next_class)) || (mangled[parsed_len + 1] == 'F')) &&
     (next_class != 0xb)) {
    return -1;
  }
  uVar4 = 0xffffffff;
  pcVar6 = class_name;
  do {
    pcVar7 = pcVar6;
    if (uVar4 == 0) break;
    uVar4 = uVar4 - 1;
    pcVar7 = pcVar6 + 1;
    cVar1 = *pcVar6;
    pcVar6 = pcVar7;
  } while (cVar1 != '\0');
  uVar4 = ~uVar4;
  pcVar6 = pcVar7 + -uVar4;
  for (uVar5 = uVar4 >> 2; uVar5 != 0; uVar5 = uVar5 - 1) {
    *(undefined4 *)class_code = *(undefined4 *)pcVar6;
    pcVar6 = pcVar6 + 4;
    class_code = class_code + 4;
  }
  for (uVar4 = uVar4 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
    *class_code = *pcVar6;
    pcVar6 = pcVar6 + 1;
    class_code = class_code + 1;
  }
  *consumed = parsed_len;
  return 2;
#undef parsed_len
#undef cv_len
#undef class_name
}



