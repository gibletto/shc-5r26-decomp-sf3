#include "decls.h"
#include "imports.h"

// entry: 00404596
// name : read_operand_label_refs
// size : 314
// sig  : void __cdecl read_operand_label_refs(int count,ea *op)


int __cdecl read_operand_label_refs(int count,ea *op)

{
  unsigned char _frec_c[12];
#define labno_buf (*(char *)(_frec_c + 0))
#define local_b (*(undefined1 *)(_frec_c + 1))
#define last_ref (*(label_ref * *)(_frec_c + 4))
  uint nread;
  label_ref *new_ref;
  
  for (; count != 0; count = count + -1) {
    nread = read_backend_stream_bytes(&labno_buf,2);
    if ((int)nread < 1) {
      report_message_at_source_line(0,0,0x1323,(char *)0x0);
    }
    if (op->labels == (label_ref *)0x0) {
      new_ref = pool_alloc(8);
      op->labels = new_ref;
      if (op->labels == (label_ref *)0x0) {
        report_message_at_source_line(0,0,0xbcd,(char *)0x0);
      }
      *(char *)&op->labels->labno1 = labno_buf;
      *(undefined1 *)((int)&op->labels->labno1 + 1) = local_b;
    }
    else {
      for (last_ref = op->labels; last_ref->next != (label_ref *)0x0; last_ref = last_ref->next) {
      }
      if (last_ref->labno2 == 0) {
        *(char *)&last_ref->labno2 = labno_buf;
        *(undefined1 *)((int)&last_ref->labno2 + 1) = local_b;
      }
      else {
        new_ref = pool_alloc(8);
        last_ref->next = new_ref;
        if (last_ref->next == (label_ref *)0x0) {
          report_message_at_source_line(0,0,0xbcd,(char *)0x0);
        }
        *(char *)&last_ref->next->labno1 = labno_buf;
        *(undefined1 *)((int)&last_ref->next->labno1 + 1) = local_b;
      }
    }
  }
  return;
#undef labno_buf
#undef local_b
#undef last_ref
}
