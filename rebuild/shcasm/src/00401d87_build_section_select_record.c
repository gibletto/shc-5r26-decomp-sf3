#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))


// entry: 00401d87
// name : build_section_select_record
// size : 245
// sig  : int build_section_select_record(uchar * out)


int __cdecl build_section_select_record(uchar *out)

{
  unsigned char _frec_10[16];
#define zero_be (*(ushort (*)[2])(_frec_10 + 0))
#define local_c (*(undefined4 *)(_frec_10 + 4))
#define section_be (*(ushort (*)[2])(_frec_10 + 8))
  int written;
  
  local_c = 0;
  if (g_current_request->code == 1) {
    g_section_data_bytes = 0;
    *out = 0x9a;
    out[1] = '\a';
    zero_be[0] = 0;
    store_u16_big_endian(zero_be,(ushort *)(out + 2));
    switch(g_current_section_kind) {
    case 0:
      section_be[0] = g_section_numbers[0];
      break;
    case 1:
      section_be[0] = g_section_numbers[1];
      break;
    case 2:
      section_be[0] = g_section_numbers[2];
      break;
    case 3:
      section_be[0] = g_section_numbers[3];
    }
    store_u16_big_endian(section_be,(ushort *)(out + 4));
    written = 6;
  }
  else {
    written = 0;
  }
  return written;
#undef zero_be
#undef local_c
#undef section_be
}



