#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))
#undef g_symbol_table
#define g_symbol_table (*(sym_entry * *)(g_sd + 0x1f9b0))


// entry: 00417000
// name : assign_parameter_home
// size : 1580
// sig  : void assign_parameter_home(param_block * blk, short slot, char release_reg, gen_node * func)


int __cdecl assign_parameter_home(param_block *blk,short slot,char release_reg,gen_node *func)

{
  byte fpu_mode;
  byte bVar1;
  byte bVar2;
  undefined1 home_reg;
  uint uVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  short *symno_ptr;
  short sVar3;
  char base_reg;
  
  uVar4 = (int)func->symx + 0xb6;
  uVar7 = (int)uVar4 >> 0x1f;
  if ((g_symbol_table[(uVar4 ^ uVar7) - uVar7].sym_flags & 0x40) == 0) {
    if ((*(short *)g_request->unknown_004 == 0) || (g_no_reg_ranges != '\0')) {
      iVar5 = (int)slot;
      bVar1 = blk->state[iVar5];
      if ((bVar1 & 1) == 0) {
        symno_ptr = blk->symno + iVar5;
        uVar4 = (int)*symno_ptr >> 0x1f;
        iVar6 = ((int)*symno_ptr ^ uVar4) - uVar4;
        if (((g_symbol_table[iVar6].sclass == '\b') && (blk->sym_flag[iVar5] == '\0')) &&
           ((g_symbol_table[iVar6].type & 2) == 0)) {
          if (((g_request->cpu == 4) && ((g_symbol_table[iVar6].type & 0xf8) == 0x30)) &&
             (iVar6 = has_free_register_pair
                                (g_used_fpr_mask,
                                 (ushort)((1 << (0xcU - g_request->scratch_bank_reg_count & 0x1f)) +
                                          -1 << (g_request->scratch_bank_reg_count + 4U & 0x1f))),
             iVar6 != 0)) {
            bVar1 = blk->state[iVar5];
            blk->state[iVar5] = bVar1 | 2;
            blk->state[iVar5] = bVar1 | 6;
          }
          else {
            sVar3 = g_request->cpu;
            if ((sVar3 != 2) || (bVar1 = 1, g_request->fpu_mode != '\x03')) {
              bVar1 = -(sVar3 == 4) & 2;
            }
            if (((bVar1 == 0) ||
                (uVar4 = (int)*symno_ptr >> 0x1f,
                (g_symbol_table[((int)*symno_ptr ^ uVar4) - uVar4].type & 0xf8) != 0x28)) ||
               (uVar4 = (1 << (0xcU - g_request->scratch_bank_reg_count & 0x1f)) + -1 <<
                        (g_request->scratch_bank_reg_count + 4U & 0x1f),
               ((int)(short)g_used_fpr_mask & uVar4) == uVar4)) {
              uVar4 = (int)*symno_ptr >> 0x1f;
              bVar1 = g_symbol_table[((int)*symno_ptr ^ uVar4) - uVar4].type;
              if ((((bVar1 & 0xe0) == 0) || ((bVar1 & 0xf8) == 0x28)) || ((bVar1 & 0xf8) == 0x40)) {
                if ((sVar3 == 2) && (g_request->fpu_mode == '\x03')) {
                  bVar2 = 1;
                }
                else {
                  bVar2 = -(sVar3 == 4) & 2;
                }
                if (((bVar2 == 0) || ((bVar1 & 0xf8) != 0x28)) &&
                   (((byte)(g_used_gpr_mask >> 8) & 0x7f) != 0x7f)) {
                  bVar1 = blk->state[iVar5];
                  blk->state[iVar5] = bVar1 | 2;
                  blk->state[iVar5] = bVar1 | 6;
                }
              }
            }
            else {
              bVar1 = blk->state[iVar5];
              blk->state[iVar5] = bVar1 | 2;
              blk->state[iVar5] = bVar1 | 6;
            }
          }
        }
      }
      else {
        if (blk->sym_flag[iVar5] == '\0') {
          uVar4 = (int)blk->symno[iVar5] >> 0x1f;
          iVar6 = ((int)blk->symno[iVar5] ^ uVar4) - uVar4;
          bVar2 = g_symbol_table[iVar6].type;
          if ((bVar2 & 2) == 0) {
            if (release_reg == '\0') {
              if (g_symbol_table[iVar6].sclass == '\b') {
                sVar3 = g_request->cpu;
                if ((sVar3 == 4) && ((bVar2 & 0xf8) == 0x30)) {
                  iVar6 = has_free_register_pair
                                    (g_used_fpr_mask,
                                     (ushort)((1 << (0xcU - g_request->scratch_bank_reg_count & 0x1f
                                                    )) + -1 <<
                                             (g_request->scratch_bank_reg_count + 4U & 0x1f)));
                  bVar1 = blk->state[iVar5];
                  if (iVar6 == 0) {
                    blk->state[iVar5] = bVar1 | 2;
                    blk->state[iVar5] = bVar1 & 0xfb | 2;
                  }
                  else {
                    blk->state[iVar5] = bVar1 | 2;
                    blk->state[iVar5] = bVar1 | 6;
                  }
                }
                else {
                  if ((sVar3 != 2) || (fpu_mode = 1, g_request->fpu_mode != '\x03')) {
                    fpu_mode = -(sVar3 == 4) & 2;
                  }
                  if ((fpu_mode == 0) || ((bVar2 & 0xf8) != 0x28)) {
                    if (((bVar2 & 0xe0) == 0) ||
                       (((bVar2 & 0xf8) == 0x28 || ((bVar2 & 0xf8) == 0x40)))) {
                      if ((sVar3 == 2) && (g_request->fpu_mode == '\x03')) {
                        fpu_mode = 1;
                      }
                      else {
                        fpu_mode = -(sVar3 == 4) & 2;
                      }
                      if (((fpu_mode == 0) || ((bVar2 & 0xf8) != 0x28)) &&
                         (((byte)(g_used_gpr_mask >> 8) & 0x7f) != 0x7f)) {
                        blk->state[iVar5] = bVar1 | 2;
                        blk->state[iVar5] = bVar1 | 6;
                        goto LAB_004173f9;
                      }
                    }
                    blk->state[iVar5] = bVar1 | 2;
                    blk->state[iVar5] = bVar1 & 0xfb | 2;
                  }
                  else {
                    uVar4 = (1 << (0xcU - g_request->scratch_bank_reg_count & 0x1f)) + -1 <<
                            (g_request->scratch_bank_reg_count + 4U & 0x1f);
                    if (((int)(short)g_used_fpr_mask & uVar4) == uVar4) {
                      blk->state[iVar5] = bVar1 | 2;
                      blk->state[iVar5] = bVar1 & 0xfb | 2;
                    }
                    else {
                      blk->state[iVar5] = bVar1 | 2;
                      blk->state[iVar5] = bVar1 | 6;
                    }
                  }
                }
              }
              else {
                blk->state[iVar5] = bVar1 | 2;
                blk->state[iVar5] = bVar1 & 0xfb | 2;
              }
            }
            else if (g_symbol_table[iVar6].sclass != '\b') {
              blk->state[iVar5] = bVar1 | 2;
              blk->state[iVar5] = bVar1 & 0xfb | 2;
            }
            goto LAB_004173f9;
          }
        }
        blk->state[iVar5] = bVar1 | 2;
        blk->state[iVar5] = bVar1 & 0xfb | 2;
      }
    }
    else {
      iVar5 = (int)slot;
      if (((blk->sym_flag[iVar5] != '\0') ||
          (uVar4 = (int)blk->symno[iVar5] >> 0x1f,
          (g_symbol_table[((int)blk->symno[iVar5] ^ uVar4) - uVar4].type & 2) != 0)) &&
         (bVar1 = blk->state[iVar5], (bVar1 & 1) != 0)) {
        blk->state[iVar5] = bVar1 | 2;
        blk->state[iVar5] = bVar1 & 0xfb | 2;
      }
    }
  }
LAB_004173f9:
  iVar5 = (int)slot;
  if ((blk->state[iVar5] & 2) == 0) {
    uVar4 = (int)blk->symno[iVar5] >> 0x1f;
    iVar5 = ((int)blk->symno[iVar5] ^ uVar4) - uVar4;
    if ((g_symbol_table[iVar5].storage.type & 0x1f) == 1) {
      g_symbol_table[iVar5].sclass = '\b';
      return;
    }
    g_symbol_table[iVar5].sclass = '\a';
  }
  else {
    if ((blk->state[iVar5] & 4) == 0) {
      symno_ptr = blk->symno + iVar5;
      g_frame_end = allocate_local_frame_offset((int)*symno_ptr,g_frame_end);
      blk->home[iVar5] = g_frame_end;
      uVar4 = (int)*symno_ptr >> 0x1f;
      g_symbol_table[((int)*symno_ptr ^ uVar4) - uVar4].sclass = '\a';
    }
    else {
      sVar3 = g_request->cpu;
      if ((sVar3 == 4) &&
         (uVar4 = (int)blk->symno[iVar5] >> 0x1f,
         (g_symbol_table[((int)blk->symno[iVar5] ^ uVar4) - uVar4].type & 0xf8) == 0x30)) {
        sVar3 = alloc_descending_paired_reg(g_request->scratch_bank_reg_count + 0x24);
        home_reg = (undefined1)sVar3;
      }
      else {
        if ((sVar3 == 2) && (g_request->fpu_mode == '\x03')) {
          bVar1 = 1;
        }
        else {
          bVar1 = -(sVar3 == 4) & 2;
        }
        if ((bVar1 == 0) ||
           (uVar4 = (int)blk->symno[iVar5] >> 0x1f,
           (g_symbol_table[((int)blk->symno[iVar5] ^ uVar4) - uVar4].type & 0xf8) != 0x28)) {
          sVar3 = alloc_descending_general_reg(8);
          home_reg = (undefined1)sVar3;
        }
        else {
          sVar3 = alloc_descending_extended_reg(g_request->scratch_bank_reg_count + 0x14);
          home_reg = (undefined1)sVar3;
        }
      }
      symno_ptr = blk->symno + iVar5;
      *(undefined1 *)(blk->home + iVar5) = home_reg;
      uVar4 = (int)*symno_ptr >> 0x1f;
      g_symbol_table[((int)*symno_ptr ^ uVar4) - uVar4].sclass = '\b';
    }
    if ((release_reg != '\0') &&
       (uVar4 = (int)*symno_ptr >> 0x1f, iVar5 = ((int)*symno_ptr ^ uVar4) - uVar4,
       (g_symbol_table[iVar5].storage.type & 0x1f) == 1)) {
      sVar3 = g_request->cpu;
      if ((sVar3 == 4) && ((g_symbol_table[iVar5].type & 0xf8) == 0x30)) {
        base_reg = g_symbol_table[iVar5].storage.base;
        g_used_fpr_mask =
             g_used_fpr_mask & ~(1 << (base_reg - 0x1fU & 0x1f) | 1 << (base_reg - 0x20U & 0x1f));
        return;
      }
      if ((sVar3 == 2) && (g_request->fpu_mode == '\x03')) {
        bVar1 = 1;
      }
      else {
        bVar1 = -(sVar3 == 4) & 2;
      }
      if ((bVar1 != 0) && ((g_symbol_table[iVar5].type & 0xf8) == 0x28)) {
        g_used_fpr_mask =
             g_used_fpr_mask & ~(1 << (g_symbol_table[iVar5].storage.base - 0x10U & 0x1f));
        return;
      }
      g_used_gpr_mask = g_used_gpr_mask & ~(1 << (g_symbol_table[iVar5].storage.base & 0x1fU));
      return;
    }
  }
  return;
}



