#include "decls.h"
#include "imports.h"

// entry: 0040b770
// name : live_range_lists_overlap
// size : 76
// sig  : int live_range_lists_overlap(reg_range * a, reg_range * b)


/* WARNING: Removing unreachable block (ram,0x0040b7ab) */

int __cdecl live_range_lists_overlap(reg_range *a,reg_range *b)

{
  int overlap;
  reg_range *rb;
  
  overlap = 0;
  do {
    if (a == (reg_range *)0x0) {
      return overlap;
    }
    if (b == (reg_range *)0x0) {
      return overlap;
    }
    rb = b;
    if (overlap == 0) {
      for (; rb != (reg_range *)0x0; rb = rb->next) {
        if (a->start < rb->start) {
          if (rb->start <= a->end) {
LAB_0040b7ad:
            overlap = 1;
            break;
          }
        }
        else if (a->start <= rb->end) goto LAB_0040b7ad;
      }
    }
    a = a->next;
    if (overlap != 0) {
      return overlap;
    }
  } while( true );
}



