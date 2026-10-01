#include "decls.h"
#include "imports.h"

// entry: 00401000
// name : optimizer_main
// size : 40
// sig  : int __cdecl optimizer_main(int argc,char **argv)


int __cdecl optimizer_main(int argc,char **argv)

{
  int extraout_EAX;
  
  print_phase_banner(1);
  initialize_optimizer(argv);
  process_input_functions();
  terminate_optimizer(argv);
  return extraout_EAX;
}
