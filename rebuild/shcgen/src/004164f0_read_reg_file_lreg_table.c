#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_lreg_entry_count
#define g_lreg_entry_count (*(short *)(g_sd + 0x1fa4e))
#undef g_lreg_table
#define g_lreg_table (*(unsigned int * *)(g_sd + 0x1fa10))
#undef g_reg_file
#define g_reg_file (*(FILE * *)(g_sd + 0x1fa2c))


// entry: 004164f0
// name : read_reg_file_lreg_table
// size : 928
// sig  : void read_reg_file_lreg_table(void)


/* WARNING: Removing unreachable block (ram,0x00416659) */
/* WARNING: Removing unreachable block (ram,0x0041661e) */
/* WARNING: Removing unreachable block (ram,0x0041670c) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl read_reg_file_lreg_table(void)

{
  unsigned char _frec_5[5];
#define flag_byte (*(char *)(_frec_5 + 0))
#define trailer (*(char (*)[2])(_frec_5 + 1))
#define header (*(char (*)[2])(_frec_5 + 3))
  ushort *buf;
  uint got;
  void *array;
  reg_range *ranges;
  uint *entry;
  uint *next_entry;
  int iVar1;
  ushort count;
  short entry_id;
  undefined4 *item;
  undefined4 *next;
  
  if (g_lreg_table == (uint *)0x0) {
    g_lreg_table = stock_malloc(0x48024);
    if (g_lreg_table == (uint *)0x0) {
      report_codegen_message(0xbcd,1,0,0,(char *)0x0);
    }
    zero_words(g_lreg_table,0x12009);
  }
  else {
    entry_id = (short)*g_lreg_table;
    entry = g_lreg_table;
    while (entry_id != 0) {
      if ((void *)entry[2] != (void *)0x0) {
        count = *(ushort *)((int)entry + 6);
        if ((count & 1) == 0) {
          iVar1 = (short)count * 2;
        }
        else {
          iVar1 = (int)(short)count << 2;
        }
        pool_free((void *)entry[2],iVar1);
      }
      item = (undefined4 *)entry[4];
      while (item != (undefined4 *)0x0) {
        next = (undefined4 *)*item;
        pool_free(item,0xc);
        item = next;
      }
      *(undefined1 *)((int)entry + 5) = 0;
      item = (undefined4 *)entry[5];
      while (item != (undefined4 *)0x0) {
        next = (undefined4 *)*item;
        pool_free(item,0x14);
        item = next;
      }
      entry = entry + 9;
      entry_id = (short)*entry;
    }
  }
  entry = g_lreg_table;
  got = read_file_bytes(g_reg_file,header,2);
  if (got < 2) {
    if (got == 0xffffffff) {
      iVar1 = 0xce6;
    }
    else {
      iVar1 = 0x120d;
    }
    report_codegen_message(iVar1,1,0,0,(char *)0x0);
  }
  got = read_file_bytes(g_reg_file,&flag_byte,1);
  if (got == 0) {
    report_codegen_message(0x120d,1,0,0,(char *)0x0);
  }
  got = read_file_bytes(g_reg_file,&g_no_reg_ranges,1);
  if (got == 0) {
    report_codegen_message(0x120d,1,0,0,(char *)0x0);
  }
  got = read_file_bytes(g_reg_file,(char *)entry,2);
  if (got < 2) {
    if (got == 0xffffffff) {
      iVar1 = 0xce6;
    }
    else {
      iVar1 = 0x120d;
    }
    report_codegen_message(iVar1,1,0,0,(char *)0x0);
  }
  entry_id = (short)*entry;
  while (entry_id != 0) {
    got = read_file_bytes(g_reg_file,(char *)((int)entry + 2),2);
    if (got < 2) {
      if (got == 0xffffffff) {
        iVar1 = 0xce6;
      }
      else {
        iVar1 = 0x120d;
      }
      report_codegen_message(iVar1,1,0,0,(char *)0x0);
    }
    got = read_file_bytes(g_reg_file,(char *)(entry + 1),1);
    if (got == 0) {
      report_codegen_message(0x120d,1,0,0,(char *)0x0);
    }
    buf = (ushort *)((int)entry + 6);
    got = read_file_bytes(g_reg_file,(char *)buf,2);
    if (got < 2) {
      if (got == 0xffffffff) {
        iVar1 = 0xce6;
      }
      else {
        iVar1 = 0x120d;
      }
      report_codegen_message(iVar1,1,0,0,(char *)0x0);
    }
    count = *buf;
    if (count == 0) {
      entry[2] = 0;
    }
    else {
      if ((count & 1) == 0) {
        got = (short)count * 2;
      }
      else {
        got = (int)(short)count << 2;
      }
      array = alloc_zeroed(got);
      entry[2] = (uint)array;
      if (array == (void *)0x0) {
        report_codegen_message(0x1210,1,0,0,(char *)0x0);
      }
      got = read_file_bytes(g_reg_file,(char *)entry[2],(short)*buf * 2);
      if ((int)got < (short)*buf * 2) {
        if (got == 0xffffffff) {
          report_codegen_message(0xce6,1,0,0,(char *)0x0);
        }
        else {
          report_codegen_message(0x120d,1,0,0,(char *)0x0);
        }
      }
    }
    next_entry = entry + 9;
    ranges = read_reg_file_range_list();
    entry[4] = (uint)ranges;
    entry[5] = 0;
    _g_lreg_entry_count = _g_lreg_entry_count + 1;
    got = read_file_bytes(g_reg_file,(char *)next_entry,2);
    if (got < 2) {
      if (got == 0xffffffff) {
        iVar1 = 0xce6;
      }
      else {
        iVar1 = 0x120d;
      }
      report_codegen_message(iVar1,1,0,0,(char *)0x0);
    }
    entry = next_entry;
    entry_id = (short)*next_entry;
  }
  entry[2] = 0;
  entry[4] = 0;
  got = read_file_bytes(g_reg_file,trailer,2);
  if (got < 2) {
    if (got == 0xffffffff) {
      report_codegen_message(0xce6,1,0,0,(char *)0x0);
      return;
    }
    report_codegen_message(0x120d,1,0,0,(char *)0x0);
  }
  return;
#undef flag_byte
#undef trailer
#undef header
}



