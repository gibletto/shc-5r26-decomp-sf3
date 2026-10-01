#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_input_tail_file
#define g_input_tail_file (*(FILE * *)(g_sd + 0x2732c))


// entry: 004248c0
// name : save_input_tail
// size : 142
// sig  : void save_input_tail(FILE * fp, short phase)


int __cdecl save_input_tail(FILE *fp,short phase)

{
  unsigned char _frec_1[1];
#define ch (*(char *)(_frec_1 + 0))
  uint count;
  
  count = read_bytes(fp,&ch,1);
  if ((count == 0) || (phase == 5)) {
    g_input_tail_file = (FILE *)0x0;
  }
  else {
    g_input_tail_file = open_temp_file();
    if (count != 0) {
      do {
        if (count == 0xffffffff) {
          check_read_result(-1);
        }
        count = write_bytes(g_input_tail_file,&ch,1);
        check_read_result(count);
        count = read_bytes(fp,&ch,1);
      } while (count != 0);
      return;
    }
  }
  return;
#undef ch
}



