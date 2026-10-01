#include "decls.h"
#include "imports.h"

// entry: 00424b60
// name : write_option_strings_and_lists
// size : 631
// sig  : void write_option_strings_and_lists(int * record, FILE * fp)


int __cdecl write_option_strings_and_lists(int *record,FILE *fp)

{
  unsigned char _frec_2[2];
#define format_version (*(char (*)[2])(_frec_2 + 0))
  uint result;
  
  format_version[0] = '\x1e';
  format_version[1] = '\0';
  result = write_bytes(fp,format_version,2);
  check_write_result(result);
  write_counted_string((char **)record,fp);
  write_counted_string((char **)(record + 0xe),fp);
  write_counted_string((char **)(record + 0xf),fp);
  write_counted_string((char **)(record + 0x14),fp);
  write_counted_string((char **)(record + 0x15),fp);
  write_counted_string((char **)(record + 0x16),fp);
  write_counted_string((char **)(record + 0x17),fp);
  write_counted_string((char **)(record + 0x18),fp);
  write_counted_string((char **)(record + 0x19),fp);
  write_counted_string((char **)(record + 0x1a),fp);
  write_counted_string((char **)(record + 0x1b),fp);
  write_counted_string((char **)(record + 0x1c),fp);
  write_counted_string((char **)(record + 0x1d),fp);
  write_counted_string((char **)(record + 0x1e),fp);
  write_counted_string((char **)(record + 0x1f),fp);
  write_counted_string((char **)(record + 0x20),fp);
  write_counted_string((char **)(record + 0x21),fp);
  write_counted_string((char **)(record + 0x22),fp);
  write_counted_string((char **)(record + 0x23),fp);
  write_counted_string((char **)(record + 0x24),fp);
  write_counted_string((char **)(record + 0x25),fp);
  write_counted_string((char **)(record + 0x26),fp);
  write_counted_string((char **)(record + 0x27),fp);
  write_counted_string((char **)(record + 0x28),fp);
  write_counted_string((char **)(record + 0x29),fp);
  write_counted_string((char **)(record + 0x2a),fp);
  write_counted_string((char **)(record + 0x45),fp);
  write_counted_string((char **)(record + 0x50),fp);
  write_counted_string((char **)(record + 0x47),fp);
  write_counted_string((char **)(record + 0x48),fp);
  write_named_record_list(record + 9,fp);
  write_string_list(record + 0x10,fp);
  write_string_list_c(record + 0x12,fp);
  write_sized_string_list(record + 0x13,fp);
  write_tagged_string_list(record + 0x3b,fp);
  write_record11_list(record + 0x2e,fp);
  write_record11_list(record + 0x2f,fp);
  write_record12_list(record + 0x30,fp);
  write_cpp_block(record + 0x51,fp);
  write_counted_string((char **)(record + 0x57),fp);
  return;
#undef format_version
}



