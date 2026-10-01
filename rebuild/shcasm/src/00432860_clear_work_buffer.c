#include "decls.h"
#include "imports.h"

// entry: 00432860
// name : clear_work_buffer
// size : 44
// sig  : void __cdecl clear_work_buffer(int buffer)


int __cdecl clear_work_buffer(int buffer)

{
  undefined4 *buf;
  
  if (buffer == 1) {
    buf = &g_work_buffer_a;
  }
  else {
    buf = &g_work_buffer_b;
    if (buffer != 2) {
      buf = &g_work_buffer_c;
    }
  }
  *(undefined1 *)*buf = 0;
  buf[2] = 0;
  return;
}
