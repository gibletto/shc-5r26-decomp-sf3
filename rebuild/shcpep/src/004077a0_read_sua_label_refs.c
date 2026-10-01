#include "decls.h"
#include "imports.h"

// entry: 004077a0
// name : read_sua_label_refs
// size : 233
// sig  : void read_sua_label_refs(int count, ea * op)


int __cdecl read_sua_label_refs(int count,ea *op)

{
  unsigned char _frec_2[2];
#define local_2 (*(char *)(_frec_2 + 0))
#define local_1 (*(undefined1 *)(_frec_2 + 1))
  uint result;
  label_ref *tail;
  label_ref *next_ref;
  
  for (; count != 0; count = count + -1) {
    result = read_sua_bytes(&local_2,2);
    if ((int)result < 1) {
      report_compiler_message(0,0,0x1323,(char *)0x0);
    }
    tail = op->labels;
    if (tail == (label_ref *)0x0) {
      tail = alloc_zeroed(8);
      op->labels = tail;
      if (tail == (label_ref *)0x0) {
        report_compiler_message(0,0,0xbcd,(char *)0x0);
      }
      *(char *)&op->labels->labno1 = local_2;
      *(undefined1 *)((int)&op->labels->labno1 + 1) = local_1;
    }
    else {
      next_ref = tail->next;
      while (next_ref != (label_ref *)0x0) {
        tail = tail->next;
        next_ref = tail->next;
      }
      if (tail->labno2 == 0) {
        *(char *)&tail->labno2 = local_2;
        *(undefined1 *)((int)&tail->labno2 + 1) = local_1;
      }
      else {
        next_ref = alloc_zeroed(8);
        tail->next = next_ref;
        if (next_ref == (label_ref *)0x0) {
          report_compiler_message(0,0,0xbcd,(char *)0x0);
        }
        *(char *)&tail->next->labno1 = local_2;
        *(undefined1 *)((int)&tail->next->labno1 + 1) = local_1;
      }
    }
  }
  return;
#undef local_2
#undef local_1
}



