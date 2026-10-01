#include "decls.h"
#include "imports.h"

// entry: 00438c40
// name : write_request_fixed_part
// size : 36
// sig  : void write_request_fixed_part(request * req, FILE * out)


int __cdecl write_request_fixed_part(request *req,FILE *out)

{
  uint result;
  
  result = write_file_bytes(out,(char *)req,(int)g_request_fixed_size);
  check_request_write_result(result);
  return;
}



