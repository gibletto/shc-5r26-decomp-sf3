#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_assigned_symbol_count
#define g_assigned_symbol_count (*(short *)(g_sd + 0x1ee98))
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))
#undef g_symbol_table
#define g_symbol_table (*(sym_entry * *)(g_sd + 0x1f9b0))


// entry: 004176b0
// name : assign_block_local_storage
// size : 994
// sig  : void assign_block_local_storage(short block_symno, uint frame_offset)


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl assign_block_local_storage(short block_symno,uint frame_offset)

{
  byte fpu_mode;
  int iVar1;
  int sym_index;
  byte sym_type;
  uint uVar2;
  short sVar3;
  uchar type;
  short slot_no;
  undefined4 *blk;
  short entry_symno;
  ushort saved_fpr_mask;
  ushort saved_gpr_mask;
  sym_entry *sym;
  
  saved_fpr_mask = g_var_fpr_mask;
  saved_gpr_mask = g_var_gpr_mask;
  if ((*(short *)g_request->unknown_004 == 0) || (g_no_reg_ranges != '\0')) {
    uVar2 = (int)block_symno >> 0x1f;
    for (blk = g_symbol_table[((int)block_symno ^ uVar2) - uVar2].list_10; blk != (undefined4 *)0x0;
        blk = (undefined4 *)*blk) {
      slot_no = 0;
      do {
        iVar1 = (int)slot_no;
        sVar3 = *(short *)((int)blk + iVar1 * 2 + 8);
        if (sVar3 == -1) break;
        uVar2 = (uint)sVar3;
        sym_index = (uVar2 ^ (int)uVar2 >> 0x1f) - ((int)uVar2 >> 0x1f);
        sym = g_symbol_table + sym_index;
        sym_type = g_symbol_table[sym_index].type;
        if (((((g_request->cpu == 4) && (g_symbol_table[sym_index].sclass == '\x06')) &&
             ((sym_type & 0xf8) == 0x30)) &&
            (((sym_type & 2) == 0 && (*(char *)(iVar1 + 4 + (int)blk) == '\0')))) &&
           (sVar3 = alloc_descending_paired_reg(0x24), sVar3 != -1)) {
          type = '\x01';
          uVar2 = 0;
LAB_004179e1:
          fill_ea(&sym->storage,type,(char)sVar3,-1,'\0',uVar2,(label_ref *)0x0);
          _g_assigned_symbol_count = _g_assigned_symbol_count + 1;
        }
        else {
          if ((g_request->cpu == 2) && (g_request->fpu_mode == '\x03')) {
            fpu_mode = 1;
          }
          else {
            fpu_mode = -(g_request->cpu == 4) & 2;
          }
          if ((((fpu_mode != 0) && (g_symbol_table[sym_index].sclass == '\x06')) &&
              ((sym_type & 0xf8) == 0x28)) &&
             ((((g_symbol_table[sym_index].type & 2) == 0 &&
               (*(char *)(iVar1 + 4 + (int)blk) == '\0')) &&
              (sVar3 = alloc_descending_extended_reg(0x14), sVar3 != -1)))) {
            type = '\x01';
            uVar2 = 0;
            goto LAB_004179e1;
          }
          if ((((sym_type & 0xe0) != 0x60) && ((sym_type & 0xe0) != 0x80)) &&
             (((sym_type & 0xe0) == 0 ||
              (((sym_type & 0xf8) == 0x28 || ((sym_type & 0xf8) == 0x40)))))) {
            sVar3 = g_request->cpu;
            if ((sVar3 != 2) || (fpu_mode = 1, g_request->fpu_mode != '\x03')) {
              fpu_mode = -(sVar3 == 4) & 2;
            }
            if (((fpu_mode == 0) || ((sym_type & 0xf8) != 0x28)) &&
               (((sVar3 != 4 || ((sym_type & 0xf8) != 0x30)) &&
                ((((g_symbol_table[sym_index].sclass == '\x06' &&
                   ((g_symbol_table[sym_index].type & 2) == 0)) &&
                  (*(char *)(iVar1 + 4 + (int)blk) == '\0')) &&
                 (sVar3 = alloc_descending_general_reg(4), sVar3 != -1)))))) {
              type = '\x01';
              uVar2 = 0;
              goto LAB_004179e1;
            }
          }
          if (g_symbol_table[sym_index].sclass != '\x04') {
            g_symbol_table[sym_index].sclass = '\x05';
            frame_offset = allocate_local_frame_offset(uVar2,frame_offset);
            sVar3 = 0x6c;
            type = '\b';
            uVar2 = frame_offset;
            goto LAB_004179e1;
          }
        }
        slot_no = slot_no + 1;
      } while (slot_no < 4);
    }
  }
  else {
    uVar2 = (int)block_symno >> 0x1f;
    for (blk = g_symbol_table[((int)block_symno ^ uVar2) - uVar2].list_10; blk != (undefined4 *)0x0;
        blk = (undefined4 *)*blk) {
      sVar3 = 0;
      do {
        entry_symno = *(short *)((int)blk + sVar3 * 2 + 8);
        if (entry_symno == -1) break;
        uVar2 = (uint)entry_symno;
        iVar1 = (uVar2 ^ (int)uVar2 >> 0x1f) - ((int)uVar2 >> 0x1f);
        sym = g_symbol_table + iVar1;
        if (((((g_symbol_table[iVar1].type & 0xe0) != 0) &&
             (sym_type = g_symbol_table[iVar1].type & 0xf8, sym_type != 0x28)) &&
            ((sym_type != 0x40 && ((g_request->cpu != 4 || (sym_type != 0x30)))))) &&
           (g_symbol_table[iVar1].sclass != '\x04')) {
          g_symbol_table[iVar1].sclass = '\x05';
          frame_offset = allocate_local_frame_offset(uVar2,frame_offset);
          fill_ea(&sym->storage,'\b','l',-1,'\0',frame_offset,(label_ref *)0x0);
          _g_assigned_symbol_count = _g_assigned_symbol_count + 1;
        }
        sVar3 = sVar3 + 1;
      } while (sVar3 < 4);
    }
  }
  if ((int)frame_offset < g_frame_end) {
    g_frame_end = frame_offset;
  }
  uVar2 = (int)block_symno >> 0x1f;
  blk = (undefined4 *)g_symbol_table[((int)block_symno ^ uVar2) - uVar2].size;
  do {
    if (blk == (undefined4 *)0x0) {
      g_var_fpr_mask = saved_fpr_mask;
      g_var_gpr_mask = saved_gpr_mask;
      return;
    }
    sVar3 = 0;
    do {
      entry_symno = *(short *)((int)blk + sVar3 * 2 + 4);
      if (entry_symno == -1) break;
      sVar3 = sVar3 + 1;
      assign_block_local_storage(entry_symno,frame_offset);
    } while (sVar3 < 6);
    blk = (undefined4 *)*blk;
  } while( true );
}



