#include "decls.h"
#include "imports.h"

// entry: 00425330
// name : write_cpp_block
// size : 194
// sig  : void write_cpp_block(int * src, FILE * fp)


int __cdecl write_cpp_block(int *src,FILE *fp)

{
  unsigned char _frec_2[2];
#define marker (*(char (*)[2])(_frec_2 + 0))
  uint result;
  
  result = write_bytes(fp,(char *)&g_cpp_block_size,2);
  check_write_result(result);
  if (g_cpp_block_size != 0) {
    result = write_bytes(fp,(char *)*src,(int)g_cpp_block_size);
    check_write_result(result);
    marker[0] = '\x05';
    marker[1] = '\0';
    result = write_bytes(fp,marker,2);
    check_write_result(result);
    write_counted_string((char **)(*src + 4),fp);
    write_counted_string((char **)(*src + 8),fp);
    write_counted_string((char **)(*src + 0xc),fp);
    write_counted_string((char **)(*src + 0x10),fp);
    write_counted_string((char **)(*src + 0x14),fp);
  }
  return;
#undef marker
}



