#include "decls.h"
#include "imports.h"

// entry: 0041b910
// name : write_sub_label_list
// size : 153
// sig  : void write_sub_label_list(FILE * out, label_ref * labels)


int __cdecl write_sub_label_list(FILE *out,label_ref *labels)

{
  unsigned char _frec_4[4];
#define n_labels (*(int *)(_frec_4 + 0))
  label_ref *lref;
  int n;
  
  n_labels = 0;
  n = n_labels;
  for (lref = labels;
      ((n_labels = n, lref != (label_ref *)0x0 && (lref->labno1 != 0)) &&
      (n_labels = n + 1, lref->labno2 != 0)); lref = lref->next) {
    n = n + 2;
  }
  write_sub_bytes(out,(char *)&n_labels,4);
  if (labels != (label_ref *)0x0) {
    while (((n_labels != 0 && (labels->labno1 != 0)) && (n_labels != 0))) {
      write_sub_bytes(out,(char *)&labels->labno1,2);
      n_labels = n_labels + -1;
      if (labels->labno2 == 0) {
        return;
      }
      if (n_labels == 0) {
        return;
      }
      write_sub_bytes(out,(char *)&labels->labno2,2);
      n_labels = n_labels + -1;
      labels = labels->next;
      if (labels == (label_ref *)0x0) {
        return;
      }
    }
  }
  return;
#undef n_labels
}



