#include "decls.h"
#include "imports.h"

// entry: 00403350
// name : find_single_definition
// size : 44
// sig  : dutbl * find_single_definition(dutbl * chain)


dutbl * __cdecl find_single_definition(dutbl *chain)

{
  int ndefs;
  dutbl *found;
  
  ndefs = 0;
  for (; chain != (dutbl *)0x0; chain = chain->next) {
    if (chain->kind == 2) {
      ndefs = ndefs + 1;
      found = chain;
    }
  }
  return (dutbl *)(-(uint)(ndefs == 1) & (uint)found);
}



