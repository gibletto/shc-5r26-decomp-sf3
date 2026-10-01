#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_reg_file
#define g_reg_file (*(FILE * *)(g_sd + 0x1fa2c))


// entry: 00416890
// name : read_reg_file_range_list
// size : 276
// sig  : reg_range * read_reg_file_range_list(void)


reg_range * read_reg_file_range_list(void)

{
  unsigned char _frec_a[10];
#define remaining (*(short *)(_frec_a + 0))
#define range_start (*(uint *)(_frec_a + 2))
#define range_end (*(uint *)(_frec_a + 6))
  uint got;
  reg_range *new_range;
  reg_range *list;
  reg_range *cur;
  int msg;
  
  list = (reg_range *)0x0;
  got = read_file_bytes(g_reg_file,(char *)&remaining,2);
  if (got < 2) {
    if (got == 0xffffffff) {
      msg = 0xce6;
    }
    else {
      msg = 0x120e;
    }
    report_codegen_message(msg,1,0,0,(char *)0x0);
  }
  if (0 < remaining) {
    list = alloc_zeroed(0xc);
    cur = list;
    if (list == (reg_range *)0x0) {
      report_codegen_message(0x1210,1,0,0,(char *)0x0);
    }
    while (0 < remaining) {
      got = read_file_bytes(g_reg_file,(char *)&range_start,8);
      if ((int)got < 8) {
        if (got == 0xffffffff) {
          msg = 0xce6;
        }
        else {
          msg = 0x120e;
        }
        report_codegen_message(msg,1,0,0,(char *)0x0);
      }
      cur->start = range_start;
      cur->end = range_end;
      remaining = remaining + -1;
      if (remaining == 0) {
        cur->next = (reg_range *)0x0;
      }
      else {
        new_range = alloc_zeroed(0xc);
        if (new_range == (reg_range *)0x0) {
          report_codegen_message(0x1210,1,0,0,(char *)0x0);
        }
        cur->next = new_range;
        cur = new_range;
      }
    }
  }
  return list;
#undef remaining
#undef range_start
#undef range_end
}



