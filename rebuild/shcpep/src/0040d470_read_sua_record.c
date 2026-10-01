#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_last_line_linno
#define g_last_line_linno (*(unsigned short *)(g_sd + 0x2724))
#undef g_sua_input
#define g_sua_input (*(FILE * *)(g_sd + 0x5c00))
#undef g_sub_output
#define g_sub_output (*(FILE * *)(g_sd + 0x5bfc))


// entry: 0040d470
// name : read_sua_record
// size : 754
// sig  : char read_sua_record(psd * rec)


char __cdecl read_sua_record(psd *rec)

{
  unsigned char _frec_8[8];
#define rec_bytes (*(undefined4 *)(_frec_8 + 0))
#define local_4 (*(undefined1 *)(_frec_8 + 4))
  uint result;
  symbol *sym;
  
  rec_bytes = 0;
  rec->ea2 = (ea *)0x0;
  local_4 = 0;
  rec->ea1 = (ea *)0x0;
  result = read_file_bytes(g_sua_input,(char *)&rec_bytes,1);
  if (result == 0) {
    return -1;
  }
  rec->op = (psd_op)rec_bytes;
  rec->tmp = -1;
  switch(*(undefined2 *)(&g_sua_record_class + (rec_bytes & 0xff) * 2)) {
  case 1:
    result = read_file_bytes(g_sua_input,(char *)((int)&rec_bytes + 1),2);
    if (result == 0xffffffff) {
      return -1;
    }
    *(undefined1 *)&rec->ea1 = (*(unsigned char *)((char *)&rec_bytes + 1));
    *(undefined1 *)((int)&rec->ea1 + 1) = (*(unsigned char *)((char *)&rec_bytes + 2));
    count_record_label_references(rec);
    result = write_file_bytes(g_sub_output,(char *)&rec_bytes,3);
    if (result == 0xffffffff) {
      report_fatal_message(0,0,0xce7);
      return '\0';
    }
    break;
  case 2:
    g_copy_rest_verbatim = 1;
    return '\0';
  case 3:
    result = read_sua_record_body(g_sua_input,rec,(psd_op)rec_bytes);
    if (result == 0xffffffff) {
      return -1;
    }
    break;
  case 4:
    break;
  case 5:
    result = read_sua_record_body(g_sua_input,rec,(psd_op)rec_bytes);
    if (result == 0xffffffff) {
      return -1;
    }
    sym = find_label_symbol(rec->linno);
    if (sym != (symbol *)0x0) {
      sym->ref_count = 0x7fff;
      return '\0';
    }
    break;
  case 6:
    result = read_sua_record_body(g_sua_input,rec,(psd_op)rec_bytes);
    if (result == 0xffffffff) {
      return -1;
    }
    break;
  case 7:
    result = read_sua_record_body(g_sua_input,rec,(psd_op)rec_bytes);
    if (result == 0xffffffff) {
      return -1;
    }
    break;
  case 8:
    result = read_sua_record_body(g_sua_input,rec,(psd_op)rec_bytes);
    if (result == 0xffffffff) {
      return -1;
    }
    if (rec->op == OP_FLABEL) {
      rec->filno = g_last_line_filno;
      rec->linno = g_last_line_linno;
      return '\0';
    }
    break;
  case 9:
    result = read_sua_record_body(g_sua_input,rec,(psd_op)rec_bytes);
    if (result != 0xffffffff) {
      g_last_line_filno = rec->filno;
      g_last_line_linno = rec->linno;
      return '\0';
    }
    return -1;
  case 10:
    result = read_sua_record_body(g_sua_input,rec,(psd_op)rec_bytes);
    if (result == 0xffffffff) {
      return -1;
    }
    break;
  case 0xb:
    result = read_sua_record_body(g_sua_input,rec,(psd_op)rec_bytes);
    if (result != 0xffffffff) {
      g_copy_rest_verbatim = 1;
      g_in_program_section = 0;
      g_reuse_input_record = 1;
      return '\0';
    }
    return -1;
  case 0xc:
    result = read_sua_record_body(g_sua_input,rec,(psd_op)rec_bytes);
    if (result == 0xffffffff) {
      return -1;
    }
    break;
  case 0xd:
    result = read_sua_record_body(g_sua_input,rec,(psd_op)rec_bytes);
    if (result == 0xffffffff) {
      return -1;
    }
    break;
  case 0xe:
    result = read_sua_record_body(g_sua_input,rec,(psd_op)rec_bytes);
    if (result == 0xffffffff) {
      return -1;
    }
    break;
  default:
    report_fatal_message(0,0,0x128e);
  }
  return '\0';
#undef rec_bytes
#undef local_4
}



