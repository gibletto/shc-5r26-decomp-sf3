#include "decls.h"
#include "imports.h"

// entry: 00432be0
// name : read_request_fixed_part
// size : 36
// sig  : void __cdecl read_request_fixed_part(request *req,FILE *in)


int __cdecl read_request_fixed_part(request *req,FILE *in)

{
  uint result;
  
  result = read_file_bytes(in,(char *)req,(int)g_request_record_size);
  check_request_read_result(result);
  return;
}
