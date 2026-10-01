#include "decls.h"
#include "imports.h"

// entry: 00418240
// name : ea_label_list_too_long
// size : 67
// sig  : int ea_label_list_too_long(ea * operand)


int __cdecl ea_label_list_too_long(ea *operand)

{
  int too_long;
  int count;
  
  too_long = 0;
  switch(operand->type & 0x1f) {
  case 2:
  case 7:
  case 8:
  case 0xd:
    if (operand->labels != (label_ref *)0x0) {
      count = count_label_refs(operand->labels);
      too_long = 1;
      if (count < 0xb) {
        too_long = 0;
      }
    }
  }
  return too_long;
}



