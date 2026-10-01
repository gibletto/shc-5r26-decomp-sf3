#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))


// entry: 0041bda0
// name : truncate_register_ranges_at_serial
// size : 206
// sig  : void truncate_register_ranges_at_serial(short reg, uint serial, reg_content * contents)


int __cdecl truncate_register_ranges_at_serial(short reg,uint serial,reg_content *contents)

{
  int index;
  reg_range *rest;
  reg_range *prev;
  reg_range *range;
  
  if ((*(short *)g_request->unknown_004 != 0) && (g_no_reg_ranges == '\0')) {
    index = (int)reg;
    rest = contents[index].ranges;
    prev = (reg_range *)&contents[index].ranges;
    while (range = rest, rest = (reg_range *)0x0, range != (reg_range *)0x0) {
      if ((range->start < serial) && ((serial < range->end || (range->end == 0)))) {
        rest = range->next;
        range->next = (reg_range *)0x0;
        if (contents[index].ranges_tail != range) {
          contents[index].ranges_tail = range;
        }
LAB_0041be4b:
        range->end = serial - 1;
        break;
      }
      if ((range->end == serial) || (serial <= range->start)) {
        if (contents[index].ranges == range) {
          contents[index].ranges_tail = (reg_range *)0x0;
          contents[index].ranges = (reg_range *)0x0;
        }
        else {
          contents[index].ranges_tail = prev;
          prev->next = (reg_range *)0x0;
        }
        rest = range;
        if (range->start < serial) {
          rest = range->next;
          goto LAB_0041be4b;
        }
        break;
      }
      prev = range;
      rest = range->next;
    }
    while (rest != (reg_range *)0x0) {
      prev = rest->next;
      pool_free(rest,0xc);
      rest = prev;
    }
  }
  return;
}



