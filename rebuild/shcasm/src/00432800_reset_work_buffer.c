#include "decls.h"
#include "imports.h"

// entry: 00432800
// name : reset_work_buffer
// size : 81
// sig  : int reset_work_buffer(int buffer)


int __cdecl reset_work_buffer(int buffer)

{
  void *mem;
  int *buf;
  
  if (buffer == 1) {
    buf = &g_work_buffer_a;
  }
  else {
    buf = &g_work_buffer_b;
    if (buffer != 2) {
      buf = &g_work_buffer_c;
    }
  }
  if (*buf == 0) {
    mem = stock_malloc(buf[1]);
    *buf = (int)mem;
    if (mem == (void *)0x0) {
      return -1;
    }
  }
  *(undefined1 *)*buf = 0;
  buf[2] = 0;
  return 1;
}



