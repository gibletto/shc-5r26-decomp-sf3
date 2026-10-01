#include "decls.h"
#include "imports.h"

// entry: 00424950
// name : install_signal_handlers
// size : 83
// sig  : void install_signal_handlers(int mode)


int __cdecl install_signal_handlers(int mode)

{
  if (mode != 1) {
    _signal(2);
    _signal(0x15);
    _signal(4);
    _signal(0x16);
    _signal(0xb);
  }
  return;
}



