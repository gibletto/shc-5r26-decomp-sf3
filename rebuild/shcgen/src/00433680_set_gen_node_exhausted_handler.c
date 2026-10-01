#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_gen_node_exhausted_handler
#define g_gen_node_exhausted_handler (*(void * *)(g_sd + 0x1ff94))


// entry: 00433680
// name : set_gen_node_exhausted_handler
// size : 22
// sig  : int set_gen_node_exhausted_handler(void * handler)


int __cdecl set_gen_node_exhausted_handler(void *handler)

{
  if (handler == (void *)0x0) {
    return 0xffff;
  }
  g_gen_node_exhausted_handler = handler;
  return (uint)handler & 0xffff0000;
}



