#include "decls.h"
#include "imports.h"

// entry: 004075e0
// name : read_sua_label_operand
// size : 165
// sig  : uint read_sua_label_operand(psd * rec)


uint __cdecl read_sua_label_operand(psd *rec)

{
  unsigned char _frec_2[2];
#define local_2 (*(char *)(_frec_2 + 0))
#define local_1 (*(undefined1 *)(_frec_2 + 1))
  uint result;
  ea *operand;
  label_ref *ref;
  
  result = read_sua_bytes(&local_2,2);
  if (result == 0) {
    return 0xffffffff;
  }
  operand = alloc_zeroed(0xc);
  rec->ea1 = operand;
  if (operand == (ea *)0x0) {
    report_compiler_message(0,0,0xbcd,(char *)0x0);
  }
  rec->ea1->type = '\a';
  ref = alloc_zeroed(8);
  rec->ea1->labels = ref;
  if (rec->ea1->labels == (label_ref *)0x0) {
    report_compiler_message(0,0,0xbcd,(char *)0x0);
  }
  *(char *)&rec->ea1->labels->labno1 = local_2;
  *(undefined1 *)((int)&rec->ea1->labels->labno1 + 1) = local_1;
  return result;
#undef local_2
#undef local_1
}



