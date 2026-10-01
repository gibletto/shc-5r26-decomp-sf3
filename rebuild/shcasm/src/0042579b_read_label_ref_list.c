#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_backend_record_input
#define g_backend_record_input (*(FILE * *)(g_sd + 0xf6d4))


// entry: 0042579b
// name : read_label_ref_list
// size : 236
// sig  : void __cdecl read_label_ref_list(short count,label_ref *head)


int __cdecl read_label_ref_list(short count,label_ref *head)

{
  unsigned char _frec_8[8];
#define cur_ref (*(label_ref * *)(_frec_8 + 0))
  uint nread;
  label_ref *new_ref;
  
  cur_ref = head;
  head->next = (label_ref *)0x0;
  while( true ) {
    if (count == 0) {
      return;
    }
    nread = read_file_bytes(g_backend_record_input,(char *)&cur_ref->labno1,2);
    if (nread == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    cur_ref->labno2 = 0;
    if (count == 1) break;
    nread = read_file_bytes(g_backend_record_input,(char *)&cur_ref->labno2,2);
    if (nread == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    count = count + -2;
    if (count == 0) {
      return;
    }
    new_ref = pool_alloc(8);
    cur_ref->next = new_ref;
    cur_ref = cur_ref->next;
  }
  return;
#undef cur_ref
}
