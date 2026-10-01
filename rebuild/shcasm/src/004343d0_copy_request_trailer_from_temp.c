#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request_trailer_file
#define g_request_trailer_file (*(FILE * *)(g_sd + 0x1331c))


// entry: 004343d0
// name : copy_request_trailer_from_temp
// size : 132
// sig  : void __cdecl copy_request_trailer_from_temp(FILE *out)


int __cdecl copy_request_trailer_from_temp(FILE *out)

{
  unsigned char _frec_1[1];
#define ch (*(char *)(_frec_1 + 0))
  uint nread;
  
  _rewind(g_request_trailer_file);
  nread = read_file_bytes(g_request_trailer_file,&ch,1);
  while (nread != 0) {
    nread = write_file_bytes(out,&ch,1);
    check_request_write_result(nread);
    nread = read_file_bytes(g_request_trailer_file,&ch,1);
    check_request_write_result(nread);
  }
  g_request_trailer_file = (FILE *)0x0;
  close_and_delete_temp_files();
  return;
#undef ch
}
