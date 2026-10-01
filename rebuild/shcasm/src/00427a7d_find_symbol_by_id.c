#include "decls.h"
#include "imports.h"

// entry: 00427a7d
// name : find_symbol_by_id
// size : 154
// sig  : symbol * find_symbol_by_id(short id)


symbol * __cdecl find_symbol_by_id(short id)

{
  symbol *sym;
  
  if (id == -0x8000) {
    report_message_at_source_line(0,0,0x136b,(char *)0x0);
  }
  for (sym = g_symbol_hash[(int)id % 0x3fd]; (sym != (symbol *)0x0 && (sym->number != id));
      sym = sym->hash_next) {
  }
  if (sym == (symbol *)0x0) {
    report_message_at_source_line(0,0,0x136a,(char *)0x0);
  }
  return sym;
}



