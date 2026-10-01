#include "decls.h"
#include "imports.h"

// entry: 0042b676
// name : flush_output_line
// size : 39
// sig  : void __cdecl flush_output_line(short channel)


int __cdecl flush_output_line(short channel)

{
  if (channel == 2) {
    flush_src_line();
  }
  else {
    flush_listing_entry();
  }
  return;
}
