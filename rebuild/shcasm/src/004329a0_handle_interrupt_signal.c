#include "decls.h"
#include "imports.h"

// entry: 004329a0
// name : handle_interrupt_signal
// size : 16
// sig  : void handle_interrupt_signal(int sig)


/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int __cdecl handle_interrupt_signal(int sig)

{
  close_and_delete_temp_files();
  stock_exit(0xd);
  return;
}



