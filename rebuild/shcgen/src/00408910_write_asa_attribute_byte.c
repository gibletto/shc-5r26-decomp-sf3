#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_asa_file
#define g_asa_file (*(FILE * *)(g_sd + 0x1f988))


// entry: 00408910
// name : write_asa_attribute_byte
// size : 88
// sig  : void write_asa_attribute_byte(uchar attr)


int __cdecl write_asa_attribute_byte(uchar attr)

{
  unsigned char _frec_1[1];
#define out_attr (*(byte *)(_frec_1 + 0))
  
  out_attr = (attr & 1) != 0;
  if ((attr & 2) != 0) {
    out_attr = out_attr | 2;
  }
  if ((attr & 0x20) != 0) {
    out_attr = out_attr | 0x20;
  }
  if ((attr & 4) != 0) {
    out_attr = out_attr | 4;
  }
  if ((attr & 8) != 0) {
    out_attr = out_attr | 8;
  }
  if ((attr & 0x10) != 0) {
    out_attr = out_attr | 0x10;
  }
  write_bytes_or_fail((char *)&out_attr,1,g_asa_file);
  return;
#undef out_attr
}



