#include "decls.h"
#include "imports.h"

// entry: 00432af0
// name : write_sua_label_list
// size : 153
// sig  : void write_sua_label_list(FILE * out, label_ref * labels)


int __cdecl write_sua_label_list(FILE *out,label_ref *labels)

{
  unsigned char _frec_4[4];
#define labno_count (*(int *)(_frec_4 + 0))
  int counted;
  label_ref *ref;
  
  labno_count = 0;
  counted = labno_count;
  for (ref = labels;
      ((labno_count = counted, ref != (label_ref *)0x0 && (ref->labno1 != 0)) &&
      (labno_count = counted + 1, ref->labno2 != 0)); ref = ref->next) {
    counted = counted + 2;
  }
  write_sua_bytes(out,(char *)&labno_count,4);
  if (labels != (label_ref *)0x0) {
    while (((labno_count != 0 && (labels->labno1 != 0)) && (labno_count != 0))) {
      write_sua_bytes(out,(char *)&labels->labno1,2);
      labno_count = labno_count + -1;
      if (labels->labno2 == 0) {
        return;
      }
      if (labno_count == 0) {
        return;
      }
      write_sua_bytes(out,(char *)&labels->labno2,2);
      labno_count = labno_count + -1;
      labels = labels->next;
      if (labels == (label_ref *)0x0) {
        return;
      }
    }
  }
  return;
#undef labno_count
}



