#include "decls.h"
#include "imports.h"

// entry: 0040a730
// name : find_symbol_record
// size : 47
// sig  : symbol * __cdecl find_symbol_record(short number)


symbol * __cdecl find_symbol_record(short number)

{
  symbol *sym;
  
  for (sym = g_symbol_hash[number % 0x3fd]; (sym != (symbol *)0x0 && (sym->number != number));
      sym = sym->hash_next) {
  }
  return sym;
}
