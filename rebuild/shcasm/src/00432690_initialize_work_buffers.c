#include "decls.h"
#include "imports.h"

// entry: 00432690
// name : initialize_work_buffers
// size : 56
// sig  : void initialize_work_buffers(void)


int __cdecl initialize_work_buffers(void)

{
  g_work_buffer_a = 0;
  g_work_buffer_a_capacity = 0x400;
  g_work_buffer_a_length = 0;
  g_work_buffer_b = 0;
  g_work_buffer_b_capacity = 0x400;
  g_work_buffer_b_length = 0;
  g_work_buffer_c = 0;
  g_work_buffer_c_capacity = 0x400;
  g_work_buffer_c_length = 0;
  return;
}
