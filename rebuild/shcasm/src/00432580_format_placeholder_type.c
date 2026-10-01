#include "decls.h"
#include "imports.h"

// entry: 00432580
// name : format_placeholder_type
// size : 142
// sig  : ushort format_placeholder_type(char * mangled, char * dst, int * consumed)


ushort __cdecl format_placeholder_type(char *mangled,char *dst,int *consumed)

{
  unsigned char _frec_14[20];
#define type_index (*(int *)(_frec_14 + 0))
#define digit_text (*(undefined2 *)(_frec_14 + 4))
#define local_e (*(char *)(_frec_14 + 6))
#define local_d (*(undefined1 *)(_frec_14 + 7))
#define digits_consumed (*(int *)(_frec_14 + 16))
  uint len;
  uint words;
  char *src;
  char *scan;
  char ch;
  
  digit_text = *(undefined2 *)(mangled + 2);
  local_e = mangled[4];
  local_d = 0;
  parse_decimal_digits((char *)&digit_text,&type_index,&digits_consumed);
  if (g_demangle_placeholder_types[type_index].kind == 0) {
    return 0xffff;
  }
  len = 0xffffffff;
  src = g_demangle_placeholder_types[type_index].text;
  do {
    scan = src;
    if (len == 0) break;
    len = len - 1;
    scan = src + 1;
    ch = *src;
    src = scan;
  } while (ch != '\0');
  len = ~len;
  src = scan + -len;
  for (words = len >> 2; words != 0; words = words - 1) {
    *(undefined4 *)dst = *(undefined4 *)src;
    src = src + 4;
    dst = dst + 4;
  }
  for (len = len & 3; len != 0; len = len - 1) {
    *dst = *src;
    src = src + 1;
    dst = dst + 1;
  }
  *consumed = 5;
  return 0;
#undef type_index
#undef digit_text
#undef local_e
#undef local_d
#undef digits_consumed
}



