#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))


// entry: 0041bae0
// name : remove_serial_from_register_ranges
// size : 387
// sig  : void remove_serial_from_register_ranges(ushort mask, uint serial)


int __cdecl remove_serial_from_register_ranges(ushort mask,uint serial)

{
  reg_range *ptr;
  int reg;
  reg_range *prVar1;
  ushort bit;
  short reg_no;
  reg_range *next_range;
  reg_range *prev;
  
  if ((*(short *)g_request->unknown_004 != 0) && (g_no_reg_ranges == '\0')) {
    bit = 1;
    reg_no = 0;
    do {
      if ((mask & 0xf & bit) != 0) {
        reg = (int)reg_no;
        prVar1 = g_gpr_contents[reg].ranges;
        next_range = prVar1;
        prev = (reg_range *)&g_gpr_contents[reg].ranges;
        while (ptr = next_range, ptr != (reg_range *)0x0) {
          if ((ptr->start < serial) && ((serial < ptr->end || (ptr->end == 0)))) {
            if (serial != g_stmt_serial) {
              prVar1 = alloc_zeroed(0xc);
              prVar1->next = ptr->next;
              ptr->next = prVar1;
              prVar1->start = serial + 1;
              prVar1->end = ptr->end;
              if (g_gpr_contents[reg].ranges_tail == ptr) {
                g_gpr_contents[reg].ranges_tail = prVar1;
              }
            }
            ptr->end = serial - 1;
            break;
          }
          if (ptr->end == serial) {
            if (ptr->start == serial) {
              if (g_gpr_contents[reg].ranges_tail == prVar1) {
                g_gpr_contents[reg].ranges_tail = (reg_range *)0x0;
                g_gpr_contents[reg].ranges = (reg_range *)0x0;
              }
              else {
                prev->next = ptr->next;
                if (g_gpr_contents[reg].ranges_tail == ptr) {
                  g_gpr_contents[reg].ranges_tail = prev;
                }
              }
              pool_free(ptr,0xc);
            }
            else {
              ptr->end = serial - 1;
            }
            break;
          }
          if (serial == ptr->start) {
            if (serial == g_stmt_serial) {
              if (g_gpr_contents[reg].ranges_tail == prVar1) {
                g_gpr_contents[reg].ranges_tail = (reg_range *)0x0;
                g_gpr_contents[reg].ranges = (reg_range *)0x0;
              }
              else {
                prev->next = ptr->next;
                if (g_gpr_contents[reg].ranges_tail == ptr) {
                  g_gpr_contents[reg].ranges_tail = prev;
                }
              }
              pool_free(ptr,0xc);
            }
            else {
              ptr->start = serial + 1;
            }
            break;
          }
          prev = ptr;
          next_range = ptr->next;
        }
      }
      bit = bit * 2;
      reg_no = reg_no + 1;
    } while (reg_no < 4);
  }
  return;
}



