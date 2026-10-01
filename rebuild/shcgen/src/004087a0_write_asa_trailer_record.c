#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_asa_file
#define g_asa_file (*(FILE * *)(g_sd + 0x1f988))


// entry: 004087a0
// name : write_asa_trailer_record
// size : 143
// sig  : void write_asa_trailer_record(char kind)


int __cdecl write_asa_trailer_record(char kind)

{
  unsigned char _frec_1[1];
#define rec_kind (*(char *)(_frec_1 + 0))
  int bits_left;
  uint i;
  uint bit;
  
  rec_kind = kind;
  write_bytes_or_fail(&rec_kind,1,g_asa_file);
  i = 0;
  do {
    bit = 1;
    bits_left = 8;
    do {
      if ((bit & (int)(char)(&g_used_routine_bits)[i]) != 0) {
        g_asa_external_count = g_asa_external_count + 1;
      }
      bit = bit * 2;
      bits_left = bits_left + -1;
    } while (bits_left != 0);
    i = i + 1;
  } while (i < 0x20);
  write_bytes_or_fail((char *)&g_asa_defined_count,2,g_asa_file);
  write_bytes_or_fail((char *)&g_asa_external_count,2,g_asa_file);
  write_bytes_or_fail(&g_used_routine_bits,0x20,g_asa_file);
  return;
#undef rec_kind
}



