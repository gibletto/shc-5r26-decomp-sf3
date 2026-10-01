#include "decls.h"
#include "imports.h"

// entry: 00433830
// name : read_request_cpp_block
// size : 231
// sig  : void __cdecl read_request_cpp_block(request_cpp_block **block,FILE *in)


int __cdecl read_request_cpp_block(request_cpp_block **block,FILE *in)

{
  unsigned char _frec_4[4];
#define string_count (*(char (*)[2])(_frec_4 + 0))
#define block_size (*(short *)(_frec_4 + 2))
  uint result;
  request_cpp_block *buf;
  
  result = read_file_bytes(in,(char *)&block_size,2);
  check_request_read_result(result);
  if (block_size != 0) {
    g_request_cpp_block_size = block_size;
    buf = stock_malloc((int)block_size);
    if (buf == (request_cpp_block *)0x0) {
      report_message_by_code((char *)0x0,0,0xbcd,(char *)0x0);
      stock_exit(9);
    }
    result = read_file_bytes(in,&buf->preprocessor,(int)block_size);
    check_request_read_result(result);
    result = read_file_bytes(in,string_count,2);
    check_request_read_result(result);
    read_request_string(buf->strings,in);
    read_request_string(buf->strings + 1,in);
    read_request_string(buf->strings + 2,in);
    read_request_string(buf->strings + 3,in);
    read_request_string(buf->strings + 4,in);
    *block = buf;
  }
  return;
#undef string_count
#undef block_size
}
