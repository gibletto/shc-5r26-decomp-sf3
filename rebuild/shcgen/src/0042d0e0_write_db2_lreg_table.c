#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_db2_file
#define g_db2_file (*(FILE * *)(g_sd + 0x1fa24))
#undef g_db2_lreg_record
#define g_db2_lreg_record (*(char *)(g_sd + 0x1e5f0))
#undef g_lreg_table
#define g_lreg_table (*(short * *)(g_sd + 0x1fa10))
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))


// entry: 0042d0e0
// name : write_db2_lreg_table
// size : 314
// sig  : void write_db2_lreg_table(void)


int __cdecl write_db2_lreg_table(void)

{
  unsigned char _frec_2[2];
#define zero_count (*(char (*)[2])(_frec_2 + 0))
  uint uVar1;
  uint uVar2;
  short *entry;
  
  if ((*(short *)g_request->unknown_004 == 0) || (g_no_reg_ranges != '\0')) {
    zero_count[0] = '\0';
    zero_count[1] = '\0';
    uVar1 = write_file_bytes(g_db2_file,zero_count,2);
    if (uVar1 == 0xffffffff) {
      report_codegen_message(0xce7,1,0,0,(char *)0x0);
    }
  }
  else {
    uVar1 = write_file_bytes(g_db2_file,&g_lreg_entry_count,2);
    if (uVar1 == 0xffffffff) {
      report_codegen_message(0xce7,1,0,0,(char *)0x0);
    }
    entry = g_lreg_table;
    if (*g_lreg_table != 0) {
      do {
        DAT_0045e5f1 = (undefined1)*entry;
        DAT_0045e5f2 = *(undefined1 *)((int)entry + 1);
        if (entry[1] < 1) {
          DAT_0045e5f3 = 6;
          uVar1 = 0;
          do {
            uVar2 = uVar1 + 1;
            (&DAT_0045e5f4)[uVar1] = *(undefined1 *)((int)entry + uVar1 + 0x1c);
            uVar1 = uVar2;
          } while (uVar2 < 4);
          g_db2_lreg_record = '\a';
        }
        else {
          DAT_0045e5f3 = 1;
          DAT_0045e5f4 = (undefined1)entry[1];
          g_db2_lreg_record = '\x04';
        }
        uVar1 = write_file_bytes(g_db2_file,&g_db2_lreg_record,(int)g_db2_lreg_record + 1);
        if (uVar1 == 0xffffffff) {
          report_codegen_message(0xce7,1,0,0,(char *)0x0);
        }
        entry = entry + 0x12;
      } while (*entry != 0);
      return;
    }
  }
  return;
#undef zero_count
}



