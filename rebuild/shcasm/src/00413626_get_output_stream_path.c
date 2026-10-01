#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))


// entry: 00413626
// name : get_output_stream_path
// size : 101
// sig  : char * get_output_stream_path(short stream)


char * __cdecl get_output_stream_path(short stream)

{
  char *stream_path;
  
  if (0 < stream) {
    if (stream < 3) {
      stream_path = g_current_request->object_path;
    }
    else if (stream == 3) {
      stream_path = g_current_request->temp_list_path;
    }
  }
  return stream_path;
}



