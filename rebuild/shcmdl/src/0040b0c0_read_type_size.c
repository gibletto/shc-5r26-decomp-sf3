#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_sym_file
#define g_sym_file (*(FILE * *)(g_sd + 0x267c4))


// entry: 0040b0c0
// name : read_type_size
// size : 51
// sig  : int read_type_size(uchar type)


int __cdecl read_type_size(uchar type)

{
  unsigned char _frec_4[4];
#define size_val (*(int *)(_frec_4 + 0))
  
  size_val = 0;
  if (0x5f < (type & 0xe0)) {
    read_or_fail(g_sym_file,(char *)&size_val,4);
  }
  return size_val;
#undef size_val
}



