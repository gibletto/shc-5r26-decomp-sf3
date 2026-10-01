#include "decls.h"
#include "imports.h"

// entry: 00423bb0
// name : read_option_strings_and_lists
// size : 846
// sig  : void read_option_strings_and_lists(int * record, FILE * fp)


int __cdecl read_option_strings_and_lists(int *record,FILE *fp)

{
  unsigned char _frec_2[2];
#define format_version (*(short *)(_frec_2 + 0))
  int *dst;
  uint result;
  int cmp;
  byte *s1;
  char *s2;
  bool below;
  byte ch;
  
  result = read_bytes(fp,(char *)&format_version,2);
  check_read_result(result);
  read_counted_string((char **)record,fp);
  read_counted_string((char **)(record + 0xe),fp);
  read_counted_string((char **)(record + 0xf),fp);
  read_counted_string((char **)(record + 0x14),fp);
  read_counted_string((char **)(record + 0x15),fp);
  read_counted_string((char **)(record + 0x16),fp);
  read_counted_string((char **)(record + 0x17),fp);
  read_counted_string((char **)(record + 0x18),fp);
  read_counted_string((char **)(record + 0x19),fp);
  read_counted_string((char **)(record + 0x1a),fp);
  read_counted_string((char **)(record + 0x1b),fp);
  read_counted_string((char **)(record + 0x1c),fp);
  read_counted_string((char **)(record + 0x1d),fp);
  read_counted_string((char **)(record + 0x1e),fp);
  read_counted_string((char **)(record + 0x1f),fp);
  read_counted_string((char **)(record + 0x20),fp);
  read_counted_string((char **)(record + 0x21),fp);
  read_counted_string((char **)(record + 0x22),fp);
  read_counted_string((char **)(record + 0x23),fp);
  read_counted_string((char **)(record + 0x24),fp);
  read_counted_string((char **)(record + 0x25),fp);
  read_counted_string((char **)(record + 0x26),fp);
  read_counted_string((char **)(record + 0x27),fp);
  read_counted_string((char **)(record + 0x28),fp);
  read_counted_string((char **)(record + 0x29),fp);
  read_counted_string((char **)(record + 0x2a),fp);
  read_counted_string((char **)(record + 0x45),fp);
  read_counted_string((char **)(record + 0x50),fp);
  read_counted_string((char **)(record + 0x47),fp);
  dst = record + 0x51;
  read_counted_string((char **)(record + 0x48),fp);
  if (*dst == 0) {
    s1 = (byte *)record[0x47];
    s2 = s_SH_SERIES_C_Compiler_Ver__5_0_Re_004331f0;
    do {
      ch = *s1;
      below = ch < (byte)*s2;
      if (ch != *s2) {
LAB_00423dbe:
        cmp = (1 - (uint)below) - (uint)(below != 0);
        goto LAB_00423dc3;
      }
      if (ch == 0) break;
      ch = s1[1];
      below = ch < (byte)s2[1];
      if (ch != s2[1]) goto LAB_00423dbe;
      s1 = s1 + 2;
      s2 = s2 + 2;
    } while (ch != 0);
    cmp = 0;
LAB_00423dc3:
    if (cmp == 0) {
      s1 = (byte *)record[0x48];
      s2 = s_Copyright__c__1992_1996_Hitachi__00433220;
      do {
        ch = *s1;
        below = ch < (byte)*s2;
        if (ch != *s2) {
LAB_00423def:
          cmp = (1 - (uint)below) - (uint)(below != 0);
          goto LAB_00423df4;
        }
        if (ch == 0) break;
        ch = s1[1];
        below = ch < (byte)s2[1];
        if (ch != s2[1]) goto LAB_00423def;
        s1 = s1 + 2;
        s2 = s2 + 2;
      } while (ch != 0);
      cmp = 0;
LAB_00423df4:
      if (cmp == 0) goto LAB_00423e03;
    }
    g_version_mismatch = 1;
  }
  else {
LAB_00423e03:
    g_version_mismatch = 0;
  }
  if (format_version != 0x1e) {
    write_error_record((char *)*record,0,0x12c1,(char *)0x0);
    stock_exit(0xb);
  }
  record[9] = 0;
  read_named_record_list(record + 9,fp);
  record[0x10] = 0;
  read_string_list(record + 0x10,fp);
  record[0x12] = 0;
  read_string_list_c(record + 0x12,fp);
  record[0x13] = 0;
  read_sized_string_list(record + 0x13,fp);
  record[0x3b] = 0;
  read_tagged_string_list(record + 0x3b,fp);
  record[0x2e] = 0;
  read_record11_list(record + 0x2e,fp);
  record[0x2f] = 0;
  read_record11_list(record + 0x2f,fp);
  record[0x30] = 0;
  read_record12_list(record + 0x30,fp);
  *dst = 0;
  read_cpp_block(dst,fp);
  read_counted_string((char **)(record + 0x57),fp);
  return;
#undef format_version
}



