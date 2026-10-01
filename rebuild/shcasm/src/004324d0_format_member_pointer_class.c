#include "decls.h"
#include "imports.h"

// entry: 004324d0
// name : format_member_pointer_class
// size : 161
// sig  : short format_member_pointer_class(char * mangled, char * dst, int * consumed)


short __cdecl format_member_pointer_class(char *mangled,char *dst,int *consumed)

{
  unsigned char _frec_4[4];
#define name_consumed (*(int *)(_frec_4 + 0))
  short status;
  char *pcVar1;
  uint len;
  uint words;
  int iVar2;
  char *pcVar3;
  char ch;
  
  pcVar1 = mangled + 1;
  if (*pcVar1 == 'Q') {
    status = format_qualified_name(pcVar1,&g_demangle_member_class_text,&name_consumed);
  }
  else {
    status = parse_length_prefixed_name(pcVar1,&g_demangle_member_class_text,&name_consumed);
  }
  if (status == 0) {
    len = 0xffffffff;
    pcVar1 = &g_demangle_member_class_text;
    do {
      pcVar3 = pcVar1;
      if (len == 0) break;
      len = len - 1;
      pcVar3 = pcVar1 + 1;
      ch = *pcVar1;
      pcVar1 = pcVar3;
    } while (ch != '\0');
    len = ~len;
    pcVar1 = pcVar3 + -len;
    pcVar3 = dst;
    for (words = len >> 2; words != 0; words = words - 1) {
      *(undefined4 *)pcVar3 = *(undefined4 *)pcVar1;
      pcVar1 = pcVar1 + 4;
      pcVar3 = pcVar3 + 4;
    }
    for (len = len & 3; len != 0; len = len - 1) {
      *pcVar3 = *pcVar1;
      pcVar1 = pcVar1 + 1;
      pcVar3 = pcVar3 + 1;
    }
    len = 0xffffffff;
    pcVar1 = (char *)&s_member_pointer_suffix;
    do {
      pcVar3 = pcVar1;
      if (len == 0) break;
      len = len - 1;
      pcVar3 = pcVar1 + 1;
      ch = *pcVar1;
      pcVar1 = pcVar3;
    } while (ch != '\0');
    len = ~len;
    iVar2 = -1;
    do {
      pcVar1 = dst;
      if (iVar2 == 0) break;
      iVar2 = iVar2 + -1;
      pcVar1 = dst + 1;
      ch = *dst;
      dst = pcVar1;
    } while (ch != '\0');
    pcVar3 = pcVar3 + -len;
    pcVar1 = pcVar1 + -1;
    for (words = len >> 2; words != 0; words = words - 1) {
      *(undefined4 *)pcVar1 = *(undefined4 *)pcVar3;
      pcVar3 = pcVar3 + 4;
      pcVar1 = pcVar1 + 4;
    }
    for (len = len & 3; len != 0; len = len - 1) {
      *pcVar1 = *pcVar3;
      pcVar3 = pcVar3 + 1;
      pcVar1 = pcVar1 + 1;
    }
    *consumed = name_consumed + 1;
  }
  return status;
#undef name_consumed
}



