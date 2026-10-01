#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef DAT_0045e605
#define DAT_0045e605 (*(char *)(g_sd + 0x1e605))
#undef DAT_0045e608
#define DAT_0045e608 (*(char *)(g_sd + 0x1e608))
#undef DAT_0045e60b
#define DAT_0045e60b (*(char *)(g_sd + 0x1e60b))
#undef g_db2_file
#define g_db2_file (*(FILE * *)(g_sd + 0x1fa24))
#undef g_db2_param_record
#define g_db2_param_record (*(char *)(g_sd + 0x1e600))
#undef g_symbol_table
#define g_symbol_table (*(sym_entry * *)(g_sd + 0x1f9b0))


// entry: 0042cb60
// name : write_db2_function_locations
// size : 924
// sig  : void write_db2_function_locations(gen_node * func)


int __cdecl write_db2_function_locations(gen_node *func)

{
  uchar uVar1;
  uint uVar2;
  int func_sym;
  byte bVar3;
  uint uVar4;
  uint uVar5;
  short *param_symx;
  char *param_loc;
  char param_no;
  int slot_index;
  undefined4 *chunk;
  byte param_flags;
  short param_symno;
  
  uVar2 = write_file_bytes(g_db2_file,&g_assigned_symbol_count,2);
  if (uVar2 == 0xffffffff) {
    report_codegen_message(0xce7,func->filn,(uint)func->line,(int)func->listno,(char *)0x0);
  }
  uVar2 = (int)func->symx + 0xb6;
  uVar4 = (int)uVar2 >> 0x1f;
  func_sym = (uVar2 ^ uVar4) - uVar4;
  param_no = '\0';
  uVar1 = g_symbol_table[func_sym].ret_19;
  bVar3 = g_symbol_table[func_sym].sym_flags & 1;
  chunk = (undefined4 *)g_symbol_table[func_sym].size;
  do {
    if (chunk == (undefined4 *)0x0) {
      write_db2_scope_locals(func->child->symx + 0xb6);
      return;
    }
    param_loc = (char *)(chunk + 5);
    param_symx = (short *)(chunk + 2);
    slot_index = 0;
    do {
      DAT_0045e601 = 0xe;
      param_no = param_no + '\x01';
      if (*param_symx == -1) break;
      param_symno = *param_symx + -0xb6;
      param_flags = *(byte *)((int)chunk + slot_index + 0x10);
      if ((param_flags & 2) == 0) {
        uVar2 = (int)*param_symx >> 0x1f;
        if ((g_symbol_table[((int)*param_symx ^ uVar2) - uVar2].storage.type & 0x1f) == 1) {
          DAT_0045e604 = 1;
          uVar2 = (int)*param_symx >> 0x1f;
          DAT_0045e605 = g_symbol_table[((int)*param_symx ^ uVar2) - uVar2].storage.base;
          if (((bVar3 == 0) || (uVar1 == '\0')) || ((int)param_no <= (char)uVar1 + -1)) {
            DAT_0045e606 = 0;
          }
          else {
            DAT_0045e606 = 1;
          }
          DAT_0045e607 = 0;
          g_db2_param_record = '\a';
        }
        else {
          DAT_0045e604 = 6;
          uVar2 = 0;
          do {
            DAT_0045e603 = (undefined1)((ushort)param_symno >> 8);
            DAT_0045e602 = (undefined1)param_symno;
            uVar5 = (int)*param_symx >> 0x1f;
            uVar4 = uVar2 + 1;
            (&DAT_0045e605)[uVar2] =
                 g_symbol_table[((int)*param_symx ^ uVar5) - uVar5].unknown_1a[uVar2 + 10];
            param_symno = CONCAT11(DAT_0045e603,DAT_0045e602);
            uVar2 = uVar4;
          } while (uVar4 < 4);
          if (((bVar3 == 0) || (uVar1 == '\0')) || ((int)param_no <= (char)uVar1 + -1)) {
            DAT_0045e609 = 0;
          }
          else {
            DAT_0045e609 = 1;
          }
          DAT_0045e60a = 0;
          g_db2_param_record = '\n';
        }
      }
      else {
        if ((param_flags & 4) == 0) {
          DAT_0045e604 = 6;
          uVar2 = 0;
          do {
            DAT_0045e603 = (undefined1)((ushort)param_symno >> 8);
            DAT_0045e602 = (undefined1)param_symno;
            uVar4 = uVar2 + 1;
            (&DAT_0045e605)[uVar2] = param_loc[uVar2];
            param_symno = CONCAT11(DAT_0045e603,DAT_0045e602);
            uVar2 = uVar4;
          } while (uVar4 < 4);
          if (((bVar3 == 0) || (uVar1 == '\0')) || ((int)param_no <= (char)uVar1 + -1)) {
            DAT_0045e609 = 0;
          }
          else {
            DAT_0045e609 = 1;
          }
          DAT_0045e60a = 0xc0;
          uVar2 = (int)*param_symx >> 0x1f;
          DAT_0045e60b = g_symbol_table[((int)*param_symx ^ uVar2) - uVar2].storage.base;
        }
        else {
          uVar2 = (int)*param_symx >> 0x1f;
          DAT_0045e604 = 1;
          DAT_0045e605 = *param_loc;
          if ((g_symbol_table[((int)*param_symx ^ uVar2) - uVar2].storage.type & 0x1f) == 1) {
            if (((bVar3 == 0) || (uVar1 == '\0')) || ((int)param_no <= (char)uVar1 + -1)) {
              DAT_0045e606 = 0;
            }
            else {
              DAT_0045e606 = 1;
            }
            DAT_0045e607 = 0xc0;
            uVar2 = (int)*param_symx >> 0x1f;
            DAT_0045e608 = g_symbol_table[((int)*param_symx ^ uVar2) - uVar2].storage.base;
            g_db2_param_record = '\b';
            goto LAB_0042ce74;
          }
          if (((bVar3 == 0) || (uVar1 == '\0')) || ((int)param_no <= (char)uVar1 + -1)) {
            DAT_0045e606 = 0;
          }
          else {
            DAT_0045e606 = 1;
          }
          DAT_0045e607 = 0x80;
          uVar2 = 0;
          do {
            DAT_0045e603 = (undefined1)((ushort)param_symno >> 8);
            DAT_0045e602 = (undefined1)param_symno;
            uVar5 = (int)*param_symx >> 0x1f;
            uVar4 = uVar2 + 1;
            (&DAT_0045e608)[uVar2] =
                 g_symbol_table[((int)*param_symx ^ uVar5) - uVar5].unknown_1a[uVar2 + 10];
            param_symno = CONCAT11(DAT_0045e603,DAT_0045e602);
            uVar2 = uVar4;
          } while (uVar4 < 4);
        }
        param_symno = CONCAT11(DAT_0045e603,DAT_0045e602);
        g_db2_param_record = '\v';
      }
LAB_0042ce74:
      DAT_0045e603 = (undefined1)((ushort)param_symno >> 8);
      DAT_0045e602 = (undefined1)param_symno;
      uVar2 = write_file_bytes(g_db2_file,&g_db2_param_record,(int)g_db2_param_record + 1);
      if (uVar2 == 0xffffffff) {
        report_codegen_message(0xce7,func->filn,(uint)func->line,(int)func->listno,(char *)0x0);
      }
      param_loc = param_loc + 4;
      param_symx = param_symx + 1;
      slot_index = slot_index + 1;
    } while (slot_index < 4);
    chunk = (undefined4 *)*chunk;
  } while( true );
}



