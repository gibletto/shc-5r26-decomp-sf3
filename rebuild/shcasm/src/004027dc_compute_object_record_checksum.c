#include "decls.h"
#include "imports.h"

// entry: 004027dc
// name : compute_object_record_checksum
// size : 86
// sig  : uint compute_object_record_checksum(void)


uint __cdecl compute_object_record_checksum(void)

{
  short sum;
  char *p;
  
  sum = 0;
  for (p = g_output_channels[1].buffer; g_output_channels[1].cursor != p; p = p + 1) {
    sum = *p + sum;
  }
  return ~(int)sum;
}



