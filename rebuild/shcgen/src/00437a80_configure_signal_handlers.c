#include "decls.h"
#include "imports.h"

// entry: 00437a80
// name : configure_signal_handlers
// size : 83
// sig  : void configure_signal_handlers(int mode)


int __cdecl configure_signal_handlers(int mode)

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



