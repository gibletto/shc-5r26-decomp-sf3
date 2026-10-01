#include "decls.h"
#include "imports.h"

// entry: 0042bcab
// name : flush_listing_entry
// size : 87
// sig  : void flush_listing_entry(void)


int __cdecl flush_listing_entry(void)

{
  while ((g_column_starts[0] < g_output_channels[3].cursor ||
         (g_listing_code_row_next <= g_listing_code_row_last))) {
    flush_listing_line();
  }
  g_listing_code_column_pos = 10;
  g_listing_code_row_last = -1;
  g_listing_code_row_next = 0;
  return;
}
