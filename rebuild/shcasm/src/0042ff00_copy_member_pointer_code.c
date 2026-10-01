#include "decls.h"
#include "imports.h"

// entry: 0042ff00
// name : copy_member_pointer_code
// size : 143
// sig  : short copy_member_pointer_code(char * src, char * dst, int * consumed)


short __cdecl copy_member_pointer_code(char *src,char *dst,int *consumed)

{
  unsigned char _frec_104[260];
#define parsed_len (*(int *)(_frec_104 + 0))
#define class_name (*(char (*)[256])(_frec_104 + 4))
  char cVar1;
  ushort uVar2;
  uint uVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  
  pcVar5 = src + 1;
  if (*pcVar5 == 'Q') {
    uVar2 = copy_qualified_name_code(pcVar5,class_name,&parsed_len);
  }
  else {
    uVar2 = copy_length_prefixed_name(pcVar5,class_name,&parsed_len);
  }
  if (uVar2 != 0) {
    return -1;
  }
  uVar3 = 0xffffffff;
  pcVar5 = class_name;
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
  pcVar6 = dst + 1;
  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)pcVar6 = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    pcVar6 = pcVar6 + 4;
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *pcVar6 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    pcVar6 = pcVar6 + 1;
  }
  *dst = *src;
  *consumed = parsed_len + 1;
  return 0;
#undef parsed_len
#undef class_name
}



