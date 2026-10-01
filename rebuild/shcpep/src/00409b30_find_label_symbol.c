#include "decls.h"
#include "imports.h"

// entry: 00409b30
// name : find_label_symbol
// size : 56
// sig  : symbol * find_label_symbol(short labno)


symbol * __cdecl find_label_symbol(short labno)

{
  symbol *sym;
  
  sym = (symbol *)0x0;
  if (0xb6 < labno) {
    for (sym = g_symbol_hash[labno % 0x3fd]; (sym != (symbol *)0x0 && (sym->number != labno));
        sym = sym->hash_next) {
    }
  }
  return sym;
}



