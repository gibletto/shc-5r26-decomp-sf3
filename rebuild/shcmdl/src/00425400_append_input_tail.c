#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_input_tail_file
#define g_input_tail_file (*(FILE * *)(g_sd + 0x2732c))


// entry: 00425400
// name : append_input_tail
// size : 132
// sig  : void append_input_tail(FILE * out)


int __cdecl append_input_tail(FILE *out)

{
  unsigned char _frec_1[1];
#define ch (*(char *)(_frec_1 + 0))
  uint count;
  
  _rewind(g_input_tail_file);
  count = read_bytes(g_input_tail_file,&ch,1);
  while (count != 0) {
    count = write_bytes(out,&ch,1);
    check_write_result(count);
    count = read_bytes(g_input_tail_file,&ch,1);
    check_write_result(count);
  }
  g_input_tail_file = (FILE *)0x0;
  remove_temp_files();
  return;
#undef ch
}



