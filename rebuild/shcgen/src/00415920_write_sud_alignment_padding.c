#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_sud_file
#define g_sud_file (*(FILE * *)(g_sd + 0x1f9f0))
#undef g_symbol_table
#define g_symbol_table (*(sym_entry * *)(g_sd + 0x1f9b0))


// entry: 00415920
// name : write_sud_alignment_padding
// size : 894
// sig  : void write_sud_alignment_padding(int unit_class, uint * offset, uint symno)


int __cdecl write_sud_alignment_padding(int unit_class,uint *offset,uint symno)

{
  unsigned char _frec_8[8];
#define pad_rec (*(char (*)[4])(_frec_8 + 0))
#define pad_count (*(char (*)[4])(_frec_8 + 4))
  uint old_offset;
  
  old_offset = *offset;
  pad_rec[0] = '\n';
  if ((g_symbol_table[symno & 0xffff].attr & 0x40) != 0) {
    switch(old_offset & 7) {
    case 0:
      break;
    case 1:
      pad_count[0] = '\x01';
      pad_count[1] = '\0';
      pad_count[2] = '\0';
      pad_count[3] = '\0';
      pad_rec[1] = 0;
      write_bytes_or_fail(pad_rec,2,g_sud_file);
      write_bytes_or_fail(pad_count,4,g_sud_file);
      pad_rec[1] = 1;
      pad_count[0] = '\x01';
      pad_count[1] = '\0';
      pad_count[2] = '\0';
      pad_count[3] = '\0';
      write_bytes_or_fail(pad_rec,2,g_sud_file);
      write_bytes_or_fail(pad_count,4,g_sud_file);
      pad_count[0] = '\x01';
      pad_count[1] = '\0';
      pad_count[2] = '\0';
      pad_count[3] = '\0';
      pad_rec[1] = 2;
      write_bytes_or_fail(pad_rec,2,g_sud_file);
      write_bytes_or_fail(pad_count,4,g_sud_file);
      *offset = *offset + 7;
      break;
    case 2:
      pad_rec[1] = 1;
      pad_count[0] = '\x01';
      pad_count[1] = '\0';
      pad_count[2] = '\0';
      pad_count[3] = '\0';
      write_bytes_or_fail(pad_rec,2,g_sud_file);
      write_bytes_or_fail(pad_count,4,g_sud_file);
      pad_count[0] = '\x01';
      pad_count[1] = '\0';
      pad_count[2] = '\0';
      pad_count[3] = '\0';
      pad_rec[1] = 2;
      write_bytes_or_fail(pad_rec,2,g_sud_file);
      write_bytes_or_fail(pad_count,4,g_sud_file);
      *offset = *offset + 6;
      break;
    case 3:
      pad_count[0] = '\x01';
      pad_count[1] = '\0';
      pad_count[2] = '\0';
      pad_count[3] = '\0';
      pad_rec[1] = 0;
      write_bytes_or_fail(pad_rec,2,g_sud_file);
      write_bytes_or_fail(pad_count,4,g_sud_file);
      pad_count[0] = '\x01';
      pad_count[1] = '\0';
      pad_count[2] = '\0';
      pad_count[3] = '\0';
      pad_rec[1] = 2;
      write_bytes_or_fail(pad_rec,2,g_sud_file);
      write_bytes_or_fail(pad_count,4,g_sud_file);
      *offset = *offset + 5;
      break;
    case 4:
      pad_rec[1] = 2;
      pad_count[0] = '\x01';
      pad_count[1] = '\0';
      pad_count[2] = '\0';
      pad_count[3] = '\0';
      write_bytes_or_fail(pad_rec,2,g_sud_file);
      write_bytes_or_fail(pad_count,4,g_sud_file);
      *offset = *offset + 4;
      break;
    case 5:
switchD_0041595b_caseD_5:
      pad_count[0] = '\x01';
      pad_count[1] = '\0';
      pad_count[2] = '\0';
      pad_count[3] = '\0';
      pad_rec[1] = 0;
      write_bytes_or_fail(pad_rec,2,g_sud_file);
      write_bytes_or_fail(pad_count,4,g_sud_file);
      pad_rec[1] = 1;
      pad_count[0] = '\x01';
      pad_count[1] = '\0';
      pad_count[2] = '\0';
      pad_count[3] = '\0';
      write_bytes_or_fail(pad_rec,2,g_sud_file);
      write_bytes_or_fail(pad_count,4,g_sud_file);
      *offset = *offset + 3;
      break;
    case 6:
switchD_0041595b_caseD_6:
      pad_rec[1] = 1;
      pad_count[0] = '\x01';
      pad_count[1] = '\0';
      pad_count[2] = '\0';
      pad_count[3] = '\0';
      write_bytes_or_fail(pad_rec,2,g_sud_file);
      write_bytes_or_fail(pad_count,4,g_sud_file);
      *offset = *offset + 2;
      break;
    case 7:
      goto switchD_0041595b_caseD_7;
    default:
      report_codegen_message(0x1236,1,0,0,(char *)0x0);
    }
    goto switchD_0041595b_caseD_0;
  }
  if (unit_class == 1) {
    if ((old_offset & 1) == 0) goto switchD_0041595b_caseD_0;
switchD_0041595b_caseD_7:
    pad_rec[1] = 0;
    pad_count[0] = '\x01';
    pad_count[1] = '\0';
    pad_count[2] = '\0';
    pad_count[3] = '\0';
    write_bytes_or_fail(pad_rec,2,g_sud_file);
    write_bytes_or_fail(pad_count,4,g_sud_file);
    *offset = *offset + 1;
  }
  else {
    switch(old_offset & 3) {
    case 0:
      break;
    case 1:
      goto switchD_0041595b_caseD_5;
    case 2:
      goto switchD_0041595b_caseD_6;
    case 3:
      goto switchD_0041595b_caseD_7;
    default:
      report_codegen_message(0x1236,1,0,0,(char *)0x0);
    }
  }
switchD_0041595b_caseD_0:
  if (*offset < old_offset) {
    report_codegen_message(0xc81,1,0,0,(char *)0x0);
  }
  return;
#undef pad_rec
#undef pad_count
}



