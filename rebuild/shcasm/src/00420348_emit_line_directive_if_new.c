#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_source_line_list
#define g_source_line_list (*(source_line_range * *)(g_sd + 0x10c64))


// entry: 00420348
// name : emit_line_directive_if_new
// size : 526
// sig  : void __cdecl emit_line_directive_if_new(psd *rec)


int __cdecl emit_line_directive_if_new(psd *rec)

{
  source_line_range *new_head;
  source_line_range *range_node;
  
  new_head = g_source_line_list;
  if (rec->op == OP_FLABEL) {
    if ((rec->linno != 0) &&
       (((g_source_line_list == (source_line_range *)0x0 ||
         (g_source_line_list->filno != rec->filno)) || (g_source_line_list->linno != rec->linno))))
    {
      new_head = pool_alloc(0x18);
      new_head->filno = rec->filno;
      new_head->linno = rec->linno;
      emit_line_directive((int)new_head->filno,(uint)new_head->linno);
      if (g_source_line_list != (source_line_range *)0x0) {
        g_source_line_list->next = new_head;
        new_head = g_source_line_list;
      }
    }
  }
  else if ((OP_DUMMY_3F < rec->op) && (rec->linno != 0)) {
    if (g_source_line_list == (source_line_range *)0x0) {
      new_head = pool_alloc(0x18);
      new_head->filno = rec->filno;
      new_head->linno = rec->linno;
      emit_line_directive((int)new_head->filno,(uint)new_head->linno);
    }
    else {
      range_node = g_source_line_list;
      while( true ) {
        if ((range_node->filno == rec->filno) && (range_node->linno == rec->linno)) {
          return;
        }
        if (range_node->next == (source_line_range *)0x0) break;
        range_node = range_node->next;
      }
      new_head = pool_alloc(0x18);
      new_head->filno = rec->filno;
      new_head->linno = rec->linno;
      emit_line_directive((int)new_head->filno,(uint)new_head->linno);
      range_node->next = new_head;
      new_head = g_source_line_list;
    }
  }
  g_source_line_list = new_head;
  return;
}
