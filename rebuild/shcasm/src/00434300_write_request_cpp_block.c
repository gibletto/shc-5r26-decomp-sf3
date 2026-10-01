#include "decls.h"
#include "imports.h"

// entry: 00434300
// name : write_request_cpp_block
// size : 194
// sig  : void __cdecl write_request_cpp_block(request_cpp_block **block,FILE *out)


int __cdecl write_request_cpp_block(request_cpp_block **block,FILE *out)

{
  unsigned char _frec_2[2];
#define string_count (*(char (*)[2])(_frec_2 + 0))
  uint result;
  
  result = write_file_bytes(out,(char *)&g_request_cpp_block_size,2);
  check_request_write_result(result);
  if (g_request_cpp_block_size != 0) {
    result = write_file_bytes(out,&(*block)->preprocessor,(int)g_request_cpp_block_size);
    check_request_write_result(result);
    string_count[0] = '\x05';
    string_count[1] = '\0';
    result = write_file_bytes(out,string_count,2);
    check_request_write_result(result);
    write_request_string((*block)->strings,out);
    write_request_string((*block)->strings + 1,out);
    write_request_string((*block)->strings + 2,out);
    write_request_string((*block)->strings + 3,out);
    write_request_string((*block)->strings + 4,out);
  }
  return;
#undef string_count
}
