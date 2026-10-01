#include "decls.h"
#include "imports.h"

// entry: 00404316
// name : read_branch_label_operand
// size : 216
// sig  : uint read_branch_label_operand(psd * rec)


uint __cdecl read_branch_label_operand(psd *rec)

{
  unsigned char _frec_c[12];
#define labno_buf (*(char *)(_frec_c + 0))
#define local_b (*(undefined1 *)(_frec_c + 1))
#define status (*(uint *)(_frec_c + 4))
  ea *new_ea;
  label_ref *new_ref;
  
  status = 0;
  status = read_backend_stream_bytes(&labno_buf,2);
  if (status == 0) {
    status = 0xffffffff;
  }
  else {
    new_ea = pool_alloc(0xc);
    rec->ea1 = new_ea;
    if (rec->ea1 == (ea *)0x0) {
      report_message_at_source_line(0,0,0xbcd,(char *)0x0);
    }
    rec->ea1->type = '\a';
    new_ref = pool_alloc(8);
    rec->ea1->labels = new_ref;
    if (rec->ea1->labels == (label_ref *)0x0) {
      report_message_at_source_line(0,0,0xbcd,(char *)0x0);
    }
    *(char *)&rec->ea1->labels->labno1 = labno_buf;
    *(undefined1 *)((int)&rec->ea1->labels->labno1 + 1) = local_b;
  }
  return status;
#undef labno_buf
#undef local_b
#undef status
}



