#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_listing_location_field
#define g_listing_location_field (*(char * *)(g_sd + 0xcc98))


// entry: 00423268
// name : format_listing_location
// size : 31
// sig  : void __cdecl format_listing_location(int location)


int __cdecl format_listing_location(int location)

{
  format_hex_digits(location,4,g_listing_location_field);
  return;
}
