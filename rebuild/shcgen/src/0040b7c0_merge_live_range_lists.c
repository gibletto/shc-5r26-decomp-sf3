#include "decls.h"
#include "imports.h"

// entry: 0040b7c0
// name : merge_live_range_lists
// size : 277
// sig  : reg_range * merge_live_range_lists(reg_range * a, reg_range * b)


reg_range * __cdecl merge_live_range_lists(reg_range *a,reg_range *b)

{
  reg_range *tail;
  reg_range *next_b;
  reg_range *merged_head;
  uint last_end;
  reg_range *next_a;
  
  merged_head = a;
  if (a == (reg_range *)0x0) {
    if (b != (reg_range *)0x0) {
      merged_head = b;
    }
  }
  else if (b != (reg_range *)0x0) {
    if (a->start < b->start) {
      a = a->next;
    }
    else {
      merged_head = b;
      b = b->next;
    }
    merged_head->next = (reg_range *)0x0;
    tail = merged_head;
    while ((a != (reg_range *)0x0 || (b != (reg_range *)0x0))) {
      if ((a == (reg_range *)0x0) ||
         ((b != (reg_range *)0x0 &&
          (((a == (reg_range *)0x0 || (b == (reg_range *)0x0)) || (b->start <= a->start)))))) {
        last_end = tail->end;
        if ((last_end < b->start) && (last_end - b->start != -1)) {
          tail->next = b;
          next_b = b->next;
          b->next = (reg_range *)0x0;
          tail = b;
        }
        else {
          if (last_end < b->end) {
            tail->end = b->end;
          }
          next_b = b->next;
          pool_free(b,0xc);
        }
      }
      else {
        last_end = tail->end;
        next_b = b;
        if ((last_end < a->start) && (last_end - a->start != -1)) {
          tail->next = a;
          next_a = a->next;
          a->next = (reg_range *)0x0;
          tail = a;
          a = next_a;
        }
        else {
          if (last_end < a->end) {
            tail->end = a->end;
          }
          next_a = a->next;
          pool_free(a,0xc);
          a = next_a;
        }
      }
      b = next_b;
      if (tail->next == tail) {
        report_codegen_message(0x1211,1,0,0,(char *)0x0);
      }
    }
  }
  return merged_head;
}



