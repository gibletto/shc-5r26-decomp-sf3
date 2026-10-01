#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef DAT_0045e615
#define DAT_0045e615 (*(char *)(g_sd + 0x1e615))
#undef g_db2_file
#define g_db2_file (*(FILE * *)(g_sd + 0x1fa24))
#undef g_db2_local_record
#define g_db2_local_record (*(char *)(g_sd + 0x1e610))
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))
#undef g_symbol_table
#define g_symbol_table (*(sym_entry * *)(g_sd + 0x1f9b0))


// entry: 0042cf00
// name : write_db2_scope_locals
// size : 478
// sig  : void write_db2_scope_locals(short sym_index)


int __cdecl write_db2_scope_locals(short sym_index)

{
  byte type_class;
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int slot;
  short *symx_ptr;
  undefined1 uStack_5;
  undefined4 *chunk;
  short local_symx;
  
  uVar3 = (int)sym_index >> 0x1f;
  iVar1 = ((int)sym_index ^ uVar3) - uVar3;
  for (chunk = g_symbol_table[iVar1].list_10; chunk != (undefined4 *)0x0;
      chunk = (undefined4 *)*chunk) {
    slot = 0;
    symx_ptr = (short *)(chunk + 2);
    do {
      local_symx = *symx_ptr;
      if (local_symx == -1) break;
      if (((*(short *)g_request->unknown_004 == 0) || (g_no_reg_ranges != '\0')) ||
         (((uVar3 = (int)local_symx >> 0x1f,
           (g_symbol_table[((int)local_symx ^ uVar3) - uVar3].type & 0xe0) != 0 &&
           ((type_class = g_symbol_table[((int)local_symx ^ uVar3) - uVar3].type & 0xf8,
            type_class != 0x28 && (type_class != 0x40)))) &&
          ((g_request->cpu != 4 || ((type_class != 0x30 && (type_class != 0x38)))))))) {
        DAT_0045e611 = 0;
        DAT_0045e612 = (undefined1)(*symx_ptr + -0xb6);
        uStack_5 = (undefined1)((ushort)(*symx_ptr + -0xb6) >> 8);
        DAT_0045e613 = uStack_5;
        uVar3 = (int)*symx_ptr >> 0x1f;
        if (g_symbol_table[((int)*symx_ptr ^ uVar3) - uVar3].sclass == '\x06') {
          DAT_0045e614 = 1;
          uVar3 = (int)*symx_ptr >> 0x1f;
          DAT_0045e615 = g_symbol_table[((int)*symx_ptr ^ uVar3) - uVar3].storage.base;
          g_db2_local_record = '\x05';
        }
        else {
          if (g_symbol_table[((int)*symx_ptr ^ uVar3) - uVar3].sclass != '\x05') goto LAB_0042d07d;
          DAT_0045e614 = 6;
          uVar3 = 0;
          do {
            uVar4 = (int)*symx_ptr >> 0x1f;
            uVar2 = uVar3 + 1;
            (&DAT_0045e615)[uVar3] =
                 g_symbol_table[((int)*symx_ptr ^ uVar4) - uVar4].unknown_1a[uVar3 + 10];
            uVar3 = uVar2;
          } while (uVar2 < 4);
          g_db2_local_record = '\b';
        }
        uVar3 = write_file_bytes(g_db2_file,&g_db2_local_record,(int)g_db2_local_record + 1);
        if (uVar3 == 0xffffffff) {
          report_codegen_message(0xce7,1,0,0,(char *)0x0);
        }
      }
LAB_0042d07d:
      symx_ptr = symx_ptr + 1;
      slot = slot + 1;
    } while (slot < 4);
  }
  chunk = (undefined4 *)g_symbol_table[iVar1].size;
  do {
    if (chunk == (undefined4 *)0x0) {
      return;
    }
    iVar1 = 0;
    symx_ptr = (short *)(chunk + 1);
    do {
      local_symx = *symx_ptr;
      if (local_symx == -1) break;
      symx_ptr = symx_ptr + 1;
      iVar1 = iVar1 + 1;
      write_db2_scope_locals(local_symx);
    } while (iVar1 < 6);
    chunk = (undefined4 *)*chunk;
  } while( true );
}



