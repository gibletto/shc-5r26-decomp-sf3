#include "decls.h"
#include "imports.h"

// entry: 00432430
// name : write_sua_record
// size : 297
// sig  : void write_sua_record(FILE * out, psd * rec)


int __cdecl write_sua_record(FILE *out,psd *rec)

{
  g_sua_linno = 0;
  g_sua_report_extra_arg = 0;
  g_sua_filno = 1;
  if (0xf1 < rec->op) {
    report_compiler_message(1,0,0x1318,(char *)0x0);
    return;
  }
  if ((&g_sua_record_format_table)[(uint)rec->op * 2] != '\0') {
    write_sua_bytes(out,(char *)rec,1);
    switch((&g_sua_record_format_table)[(uint)rec->op * 2]) {
    case 1:
      write_sua_machine_op_record(out,rec);
      return;
    case 2:
      write_sua_casejmp_record(out,rec);
      return;
    case 3:
      write_sua_ctbl_record(out,rec);
      return;
    case 4:
      write_sua_cent_record(out,rec);
      return;
    case 5:
      write_sua_label_record(out,rec);
      return;
    case 6:
      write_sua_line_record(out,rec);
      return;
    case 7:
      goto switchD_004324b2_caseD_7;
    case 8:
      write_sua_instruction_record(out,rec);
      return;
    case 9:
      write_sua_op10_record(out,rec);
      return;
    case 10:
      write_sua_section_record(out,rec);
switchD_004324b2_caseD_7:
      return;
    default:
      report_compiler_message(g_sua_filno,(uint)g_sua_linno,0x1319,(char *)0x0);
      return;
    }
  }
  report_compiler_message(1,0,0x1318,(char *)0x0);
  return;
}



