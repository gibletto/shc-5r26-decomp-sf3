#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_work_buffer_a
#define g_work_buffer_a (*(void * *)(g_sd + 0x14f70))
#undef g_work_buffer_b
#define g_work_buffer_b (*(void * *)(g_sd + 0x14f80))
#undef g_work_buffer_c
#define g_work_buffer_c (*(void * *)(g_sd + 0x14f90))


// entry: 004326d0
// name : free_work_buffers
// size : 55
// sig  : void free_work_buffers(void)


int __cdecl free_work_buffers(void)

{
  if (g_work_buffer_a != (void *)0x0) {
    stock_free(g_work_buffer_a);
  }
  if (g_work_buffer_b != (void *)0x0) {
    stock_free(g_work_buffer_b);
  }
  if (g_work_buffer_c != (void *)0x0) {
    stock_free(g_work_buffer_c);
  }
  return;
}
