#include "decls.h"
#include "imports.h"

// entry: 00413a4a
// name : free_size_decision_stream_buffer
// size : 96
// sig  : void free_size_decision_stream_buffer(void)


int __cdecl free_size_decision_stream_buffer(void)

{
  if (g_output_channels[0].opened == 1) {
    g_output_channels[0].opened = 0;
  }
  stock_free(g_output_channels[0].buffer);
  return;
}
