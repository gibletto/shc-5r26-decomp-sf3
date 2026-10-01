#include "decls.h"
#include "imports.h"

// entry: 00433b00
// name : write_request_fixed_part
// size : 36
// sig  : void __cdecl write_request_fixed_part(request *req,FILE *out)


int __cdecl write_request_fixed_part(request *req,FILE *out)

{
  uint result;
  
  result = write_file_bytes(out,(char *)req,(int)g_request_record_size);
  check_request_write_result(result);
  return;
}
