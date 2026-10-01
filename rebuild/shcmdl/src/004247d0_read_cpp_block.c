#include "decls.h"
#include "imports.h"

// entry: 004247d0
// name : read_cpp_block
// size : 231
// sig  : void read_cpp_block(int * dst, FILE * fp)


int __cdecl read_cpp_block(int *dst,FILE *fp)

{
  unsigned char _frec_4[4];
#define marker (*(char (*)[2])(_frec_4 + 0))
#define size_val (*(short *)(_frec_4 + 2))
  uint result;
  char *buf;
  
  result = read_bytes(fp,(char *)&size_val,2);
  check_read_result(result);
  if (size_val != 0) {
    g_cpp_block_size = size_val;
    buf = stock_malloc((int)size_val);
    if (buf == (char *)0x0) {
      write_error_record((char *)0x0,0,0xbcd,(char *)0x0);
      stock_exit(9);
    }
    result = read_bytes(fp,buf,(int)size_val);
    check_read_result(result);
    result = read_bytes(fp,marker,2);
    check_read_result(result);
    read_counted_string((char **)(buf + 4),fp);
    read_counted_string((char **)(buf + 8),fp);
    read_counted_string((char **)(buf + 0xc),fp);
    read_counted_string((char **)(buf + 0x10),fp);
    read_counted_string((char **)(buf + 0x14),fp);
    *dst = (int)buf;
  }
  return;
#undef marker
#undef size_val
}



