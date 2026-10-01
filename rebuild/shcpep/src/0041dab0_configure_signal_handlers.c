#include "decls.h"
#include "imports.h"

// entry: 0041dab0
// name : configure_signal_handlers
// size : 83
// sig  : void configure_signal_handlers(int mode)


int __cdecl configure_signal_handlers(int mode)

{
  if (mode != 1) {
    _signal(2,handle_interrupt_signal);
    _signal(0x15,handle_fault_signal);
    _signal(4,handle_fault_signal);
    _signal(0x16,handle_fault_signal);
    _signal(0xb,handle_fault_signal);
  }
  return;
}



