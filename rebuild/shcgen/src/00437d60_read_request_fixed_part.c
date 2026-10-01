#include "decls.h"
#include "imports.h"

// entry: 00437d60
// name : read_request_fixed_part
// size : 36
// sig  : void read_request_fixed_part(request * req, FILE * in)


int __cdecl read_request_fixed_part(request *req,FILE *in)

{
  uint result;
  
  result = read_file_bytes(in,(char *)req,(int)g_request_fixed_size);
  check_request_read_result(result);
  return;
}



