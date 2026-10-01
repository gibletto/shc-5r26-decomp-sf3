#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_assigned_symbol_count
#define g_assigned_symbol_count (*(short *)(g_sd + 0x1ee98))
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))
#undef g_stack_param_offset
#define g_stack_param_offset (*(unsigned int *)(g_sd + 0x1fa38))
#undef g_symbol_table
#define g_symbol_table (*(sym_entry * *)(g_sd + 0x1f9b0))
#undef g_used_gpr_mask
#define g_used_gpr_mask (*(unsigned char *)(g_sd + 0x1ff60))


// entry: 004169b0
// name : assign_parameter_storage
// size : 1389
// sig  : void assign_parameter_storage(gen_node * func)


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl assign_parameter_storage(gen_node *func)

{
  param_block *blk;
  byte bVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  int sym_index;
  int pair_free;
  byte fpu_mode;
  uint uVar5;
  char cVar6;
  byte local_15;
  byte local_14;
  byte local_13;
  uchar reg_args_left;
  ushort gpr_used;
  short slot_no;
  ushort fpr_used;
  short param_symno;
  bool limited_reg_args;
  
  gpr_used = 0xff0f;
  g_stack_param_offset = 0;
  param_symno = 0;
  reg_args_left = '\0';
  limited_reg_args = false;
  fpr_used = ~(((1 << (g_request->scratch_bank_reg_count & 0x1fU)) + -1) * 0x10);
  if (func->op == IL_FUNC) {
    uVar3 = (int)func->symx + 0xb6;
    uVar5 = (int)uVar3 >> 0x1f;
    bVar1 = g_symbol_table[(uVar3 ^ uVar5) - uVar5].sym_flags;
    local_15 = bVar1 & 4;
    local_14 = bVar1 & 0x20;
    local_13 = bVar1 & 0x80;
  }
  else {
    report_codegen_message(0x120c,func->filn,(uint)func->line,(int)func->listno,(char *)0x0);
  }
  uVar3 = (int)func->symx + 0xb6;
  uVar5 = (int)uVar3 >> 0x1f;
  if (((g_symbol_table[(uVar3 ^ uVar5) - uVar5].ret_type & 0xe0) == 0x60) ||
     ((g_request->cpu != 4 && ((g_symbol_table[(uVar3 ^ uVar5) - uVar5].ret_type & 0xf8) == 0x30))))
  {
    g_stack_param_offset = 4;
  }
  uVar3 = (int)func->symx + 0xb6;
  uVar5 = (int)uVar3 >> 0x1f;
  iVar4 = (uVar3 ^ uVar5) - uVar5;
  if ((g_symbol_table[iVar4].sym_flags & 2) != 0) {
    limited_reg_args = true;
    reg_args_left = g_symbol_table[iVar4].ret_19;
    if (reg_args_left != '\0') {
      reg_args_left = reg_args_left + 0xff;
    }
  }
  if (((local_15 == 0) || (local_14 != 0)) || (local_13 != 0)) {
    (*(unsigned char *)((char *)&g_used_gpr_mask + 0)) = (byte)g_used_gpr_mask | 0xf0;
    g_used_fpr_mask =
         g_used_fpr_mask | ((1 << (g_request->scratch_bank_reg_count & 0x1fU)) + -1) * 0x10;
  }
  uVar3 = (int)func->symx + 0xb6;
  uVar5 = (int)uVar3 >> 0x1f;
  blk = (param_block *)g_symbol_table[(uVar3 ^ uVar5) - uVar5].size;
  uVar3 = g_stack_param_offset;
  do {
    if ((blk == (param_block *)0x0) || (param_symno == -1)) {
      g_stack_param_offset = uVar3;
      return;
    }
    slot_no = 0;
    do {
      iVar4 = (int)slot_no;
      param_symno = blk->symno[iVar4];
      if (param_symno == -1) break;
      if (((g_request->cpu != 4) ||
          (uVar5 = (int)param_symno >> 0x1f, sym_index = ((int)param_symno ^ uVar5) - uVar5,
          (g_symbol_table[sym_index].type & 0xf8) != 0x30)) ||
         ((pair_free = has_free_register_pair
                                 (fpr_used,((short)(1 << (g_request->scratch_bank_reg_count & 0x1fU)
                                                   ) + -1) * 0x10), pair_free == 0 ||
          ((limited_reg_args && (reg_args_left == '\0')))))) {
        sVar2 = g_request->cpu;
        if ((sVar2 != 2) || (bVar1 = 1, g_request->fpu_mode != '\x03')) {
          bVar1 = -(sVar2 == 4) & 2;
        }
        if ((((bVar1 == 0) ||
             (uVar5 = (int)param_symno >> 0x1f, sym_index = ((int)param_symno ^ uVar5) - uVar5,
             (g_symbol_table[sym_index].type & 0xf8) != 0x28)) ||
            (uVar5 = ((1 << (g_request->scratch_bank_reg_count & 0x1fU)) + -1) * 0x10,
            (uVar5 & (int)(short)fpr_used) == uVar5)) ||
           ((limited_reg_args && (reg_args_left == '\0')))) {
          uVar5 = (int)param_symno >> 0x1f;
          sym_index = ((int)param_symno ^ uVar5) - uVar5;
          bVar1 = g_symbol_table[sym_index].type;
          if (((bVar1 & 0xe0) == 0) || (((bVar1 & 0xf8) == 0x28 || ((bVar1 & 0xf8) == 0x40)))) {
            if ((bVar1 & 0xf8) == 0x28) {
              if ((sVar2 == 2) && (g_request->fpu_mode == '\x03')) {
                fpu_mode = 1;
              }
              else {
                fpu_mode = -(sVar2 == 4) & 2;
              }
              if (fpu_mode != 0) goto LAB_00416de0;
            }
            if ((((byte)gpr_used & 0xf0) != 0xf0) &&
               ((!limited_reg_args || (reg_args_left != '\0')))) {
              sVar2 = alloc_general_reg_from_low_mask(gpr_used);
              fill_ea(&g_symbol_table[sym_index].storage,'\x01',(byte)sVar2,-1,'\0',0,
                      (label_ref *)0x0);
              blk->state[iVar4] = '\x01';
              gpr_used = gpr_used | 1 << ((byte)sVar2 & 0x1f);
              goto LAB_00416ea6;
            }
          }
LAB_00416de0:
          if (g_request->unknown_028[2] == '\0') {
            if ((bVar1 & 0xf8) == 0) {
              uVar3 = uVar3 + 3;
            }
            else if ((bVar1 & 0xf8) == 8) {
              uVar3 = uVar3 + 2;
            }
          }
          fill_ea(&g_symbol_table[sym_index].storage,'\b','l',-1,'\0',uVar3,(label_ref *)0x0);
          switch(g_symbol_table[sym_index].type & 0xfc) {
          case 0:
          case 4:
            uVar3 = uVar3 + 1;
            break;
          case 8:
          case 0xc:
            uVar3 = uVar3 + 2;
            break;
          case 0x10:
          case 0x14:
          case 0x18:
          case 0x1c:
          case 0x28:
          case 0x40:
            uVar3 = uVar3 + 4;
            break;
          case 0x30:
          case 0x38:
            uVar3 = uVar3 + 8;
            break;
          case 0x60:
          case 0x68:
          case 0x70:
          case 0x80:
          case 0x88:
          case 0x90:
            uVar3 = uVar3 + g_symbol_table[sym_index].size;
          }
          uVar5 = (int)uVar3 >> 0x1f;
          iVar4 = ((uVar3 ^ uVar5) - uVar5 & 3 ^ uVar5) - uVar5;
          if (iVar4 == 1) {
            uVar3 = uVar3 + 3;
          }
          else if (iVar4 == 2) {
            uVar3 = uVar3 + 2;
          }
          else if (iVar4 == 3) {
            uVar3 = uVar3 + 1;
          }
          if ((int)uVar3 < 1) {
            report_codegen_message(0xc84,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
          }
        }
        else {
          sVar2 = alloc_extended_reg_from_low_mask(fpr_used);
          fill_ea(&g_symbol_table[sym_index].storage,'\x01',(char)sVar2,-1,'\0',0,(label_ref *)0x0);
          blk->state[iVar4] = '\x01';
          fpr_used = fpr_used | 1 << ((char)sVar2 - 0x10U & 0x1f);
        }
      }
      else {
        sVar2 = alloc_paired_reg_from_low_mask(fpr_used);
        cVar6 = (char)sVar2;
        fill_ea(&g_symbol_table[sym_index].storage,'\x01',cVar6,-1,'\0',0,(label_ref *)0x0);
        blk->state[iVar4] = '\x01';
        fpr_used = fpr_used | 1 << (cVar6 - 0x1fU & 0x1f) | 1 << (cVar6 - 0x20U & 0x1f);
      }
LAB_00416ea6:
      if (limited_reg_args) {
        reg_args_left = reg_args_left + 0xff;
      }
      _g_assigned_symbol_count = _g_assigned_symbol_count + 1;
      if (((local_15 == 0) || (local_14 != 0)) || (cVar6 = '\x01', local_13 != 0)) {
        cVar6 = '\0';
      }
      assign_parameter_home(blk,slot_no,cVar6,func);
      slot_no = slot_no + 1;
    } while (slot_no < 4);
    blk = blk->next;
  } while( true );
}



