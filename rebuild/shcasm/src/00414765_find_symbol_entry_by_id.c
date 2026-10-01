#include "decls.h"
#include "imports.h"

// entry: 00414765
// name : find_symbol_entry_by_id
// size : 87
// sig  : symbol * find_symbol_entry_by_id(short id)


symbol * __cdecl find_symbol_entry_by_id(short id)

{
  symbol *sym;
  
  for (sym = g_symbol_hash[(int)id % 0x3fd]; (sym != (symbol *)0x0 && (sym->number != id));
      sym = sym->hash_next) {
  }
  return sym;
}



