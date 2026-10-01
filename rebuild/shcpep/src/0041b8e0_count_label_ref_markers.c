#include "decls.h"
#include "imports.h"

// entry: 0041b8e0
// name : count_label_ref_markers
// size : 39
// sig  : short count_label_ref_markers(label_ref * labels)


short __cdecl count_label_ref_markers(label_ref *labels)

{
  short count;
  
  count = 0;
  for (; labels != (label_ref *)0x0; labels = labels->next) {
    if (labels->labno1 == -0x8000) {
      count = count + 1;
    }
    if (labels->labno2 == -0x8000) {
      count = count + 1;
    }
  }
  return count;
}



