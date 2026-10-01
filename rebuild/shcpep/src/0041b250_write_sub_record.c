#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_sub_linno
#define g_sub_linno (*(unsigned short *)(g_sd + 0x5360))


// entry: 0041b250
// name : write_sub_record
// size : 297
// sig  : void write_sub_record(FILE * out, psd * rec)


int __cdecl write_sub_record(FILE *out,psd *rec)

{
  g_sub_linno = 0;
  g_sub_report_extra_arg = 0;
  g_sub_filno = 1;
  if (0xf1 < rec->op) {
    report_compiler_message(1,0,0x1318,(char *)0x0);
    return;
  }
  if (g_sub_record_format_table[(uint)rec->op * 2] != '\0') {
    write_sub_bytes(out,(char *)rec,1);
    switch(g_sub_record_format_table[(uint)rec->op * 2]) {
    case '\x01':
      write_sub_machine_op_record(out,rec);
      return;
    case '\x02':
      write_sub_casejmp_record(out,rec);
      return;
    case '\x03':
      write_sub_ctbl_record(out,rec);
      return;
    case '\x04':
      write_sub_cent_record(out,rec);
      return;
    case '\x05':
      write_sub_label_record(out,rec);
      return;
    case '\x06':
      write_sub_line_record(out,rec);
      return;
    case '\a':
      goto switchD_0041b2d2_caseD_7;
    case '\b':
      write_sub_instruction_record(out,rec);
      return;
    case '\t':
      write_sub_op10_record(out,rec);
      return;
    case '\n':
      write_sub_section_record(out,rec);
switchD_0041b2d2_caseD_7:
      return;
    default:
      report_compiler_message(g_sub_filno,(uint)g_sub_linno,0x1319,(char *)0x0);
      return;
    }
  }
  report_compiler_message(1,0,0x1318,(char *)0x0);
  return;
}



