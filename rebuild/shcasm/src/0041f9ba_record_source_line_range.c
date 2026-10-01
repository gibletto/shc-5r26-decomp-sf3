#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_source_line_list
#define g_source_line_list (*(source_line_range * *)(g_sd + 0x10c64))


// entry: 0041f9ba
// name : record_source_line_range
// size : 752
// sig  : void __cdecl record_source_line_range(psd *rec)


int __cdecl record_source_line_range(psd *rec)

{
  source_line_range *new_head;
  line_call_site *call_site;
  line_call_site *last_call;
  source_line_range *line_range;
  
  new_head = g_source_line_list;
  if (rec->op == OP_FLABEL) {
    if ((rec->linno != 0) &&
       (((g_source_line_list == (source_line_range *)0x0 ||
         (rec->filno != g_source_line_list->filno)) || (rec->linno != g_source_line_list->linno))))
    {
      new_head = pool_alloc(0x18);
      new_head->filno = rec->filno;
      new_head->linno = rec->linno;
      new_head->section = g_section_numbers[0];
      new_head->start = g_location_counter;
      new_head->end = g_location_counter + 2;
      if (g_source_line_list != (source_line_range *)0x0) {
        g_source_line_list->next = new_head;
        new_head = g_source_line_list;
      }
    }
  }
  else if ((OP_DUMMY_3F < rec->op) && (rec->linno != 0)) {
    if (g_source_line_list == (source_line_range *)0x0) {
      g_source_line_list = pool_alloc(0x18);
      g_source_line_list->filno = rec->filno;
      g_source_line_list->linno = rec->linno;
      g_source_line_list->section = g_section_numbers[0];
      g_source_line_list->start = g_location_counter + -2;
      g_source_line_list->end = g_location_counter;
      line_range = g_source_line_list;
    }
    else {
      line_range = g_source_line_list;
      while( true ) {
        if ((rec->filno == line_range->filno) && (rec->linno == line_range->linno)) {
          line_range->end = g_location_counter;
          goto LAB_0041fc24;
        }
        if (line_range->next == (source_line_range *)0x0) break;
        line_range = line_range->next;
      }
      new_head = pool_alloc(0x18);
      new_head->filno = rec->filno;
      new_head->linno = rec->linno;
      new_head->section = g_section_numbers[0];
      if ((rec->flg & 0x40) == 0) {
        new_head->start = g_location_counter + -2;
      }
      else {
        new_head->start = g_location_counter + -4;
      }
      new_head->end = g_location_counter;
      line_range->next = new_head;
      line_range = new_head;
    }
LAB_0041fc24:
    if (((rec->op == OP_JSR) || (rec->op == OP_BSR)) ||
       (new_head = g_source_line_list, rec->op == OP_BSRF)) {
      line_range->call_count = line_range->call_count + 1;
      call_site = pool_alloc(8);
      call_site->address = g_location_counter + -2;
      if (line_range->calls == (line_call_site *)0x0) {
        line_range->calls = call_site;
        new_head = g_source_line_list;
      }
      else {
        for (last_call = line_range->calls; last_call->next != (line_call_site *)0x0;
            last_call = last_call->next) {
        }
        last_call->next = call_site;
        new_head = g_source_line_list;
      }
    }
  }
  g_source_line_list = new_head;
  return;
}
