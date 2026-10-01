#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request_trailer_file
#define g_request_trailer_file (*(FILE * *)(g_sd + 0x6e30))


// entry: 0041da20
// name : save_request_trailer_to_temp
// size : 142
// sig  : void save_request_trailer_to_temp(FILE * in, short stage)


int __cdecl save_request_trailer_to_temp(FILE *in,short stage)

{
  unsigned char _frec_1[1];
#define ch (*(char *)(_frec_1 + 0))
  uint result;
  
  result = read_file_bytes(in,&ch,1);
  if ((result == 0) || (stage == 5)) {
    g_request_trailer_file = (FILE *)0x0;
  }
  else {
    g_request_trailer_file = open_temp_file();
    if (result != 0) {
      do {
        if (result == 0xffffffff) {
          check_request_read_result(-1);
        }
        result = write_file_bytes(g_request_trailer_file,&ch,1);
        check_request_read_result(result);
        result = read_file_bytes(in,&ch,1);
      } while (result != 0);
      return;
    }
  }
  return;
#undef ch
}



