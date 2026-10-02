#include "decls.h"
#include "imports.h"
#include "remaprules.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))


// entry: 0041bc70
// name : update_register_ranges_after_statement
// size : 303
// sig  : void update_register_ranges_after_statement(ushort used_mask, reg_content * contents)


int __cdecl update_register_ranges_after_statement(ushort used_mask,reg_content *contents)

{
  reg_range *new_range;
  reg_range *tail;
  ushort bit;
  short reg;
  
  if (contents == g_gpr_contents) {
    REMAP_MARK("st",used_mask,g_stmt_serial);
  }
  if ((*(short *)g_request->unknown_004 != 0) && (g_no_reg_ranges == '\0')) {
    bit = 1;
    reg = 0;
    do {
      if ((used_mask & 0xf & bit) == 0) {
        tail = contents[reg].ranges_tail;
        if (tail == (reg_range *)0x0) {
          tail = alloc_zeroed(0xc);
          contents[reg].ranges_tail = tail;
          contents[reg].ranges = tail;
          (contents[reg].ranges_tail)->start = g_stmt_serial;
        }
        else if (tail->end != 0) {
          if (tail->end < g_stmt_serial) {
            new_range = alloc_zeroed(0xc);
            tail->next = new_range;
            tail = (contents[reg].ranges_tail)->next;
            contents[reg].ranges_tail = tail;
            tail->start = g_stmt_serial;
          }
          else {
            report_codegen_message(0x1223,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0)
            ;
          }
        }
      }
      else {
        tail = contents[reg].ranges_tail;
        if (tail != (reg_range *)0x0) {
          if (tail->end == 0) {
            tail->end = g_stmt_serial - 1;
          }
          else if (g_stmt_serial <= tail->end) {
            report_codegen_message(0x1223,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0)
            ;
          }
        }
      }
      bit = bit * 2;
      reg = reg + 1;
    } while (reg < 4);
  }
  return;
}



