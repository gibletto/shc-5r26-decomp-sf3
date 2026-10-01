#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_symbol_table
#define g_symbol_table (*(sym_entry * *)(g_sd + 0x1f9b0))


// entry: 00414900
// name : emit_block_copy_macro
// size : 1826
// sig  : void emit_block_copy_macro(ushort op, ea * src, ea * dst, ea * * temps, ea * dst_addr, gen_node * node)


/* WARNING: Removing unreachable block (ram,0x00414f27) */
/* WARNING: Removing unreachable block (ram,0x0041497f) */
/* WARNING: Removing unreachable block (ram,0x00414b4d) */

int __cdecl emit_block_copy_macro(ushort op,ea *src,ea *dst,ea **temps,ea *dst_addr,gen_node *node)

{
  byte bVar1;
  byte type_class;
  int iVar2;
  uint uVar3;
  ea *opnd_a;
  ea *opnd_b;
  uint uVar4;
  int iVar5;
  int copied;
  uchar move_size;
  uint copy_len;
  label_ref *lab;
  gen_node *no_node;
  
  if ((op != 0x2400) && (op != 0x2a00)) {
    if (op == 0x2500) {
      bVar1 = dst_addr->type & 0x1f;
      if ((((bVar1 == 2) && (dst_addr->base == 'l')) || ((bVar1 == 8 && (dst_addr->base == 'l'))))
         || ((bVar1 == 0xd && (dst_addr->labels == (label_ref *)0x0)))) {
        uVar4 = dst_addr->disp;
      }
      else {
        if (dst_addr->labels == (label_ref *)0x0) {
          iVar2 = 0;
        }
        else {
          iVar2 = (int)dst_addr->labels->labno1;
        }
        uVar4 = g_symbol_table[iVar2].frame_offset + dst_addr->disp;
      }
      uVar3 = 0;
      if ((uVar4 & 3) != 0) {
        uVar3 = 4 - (uVar4 & 3);
      }
      if ((uVar3 & 1) != 0) {
        opnd_a = copy_ea(src);
        no_node = (gen_node *)0x0;
        opnd_a->type = opnd_a->type & 0xf4 | 4;
        opnd_b = copy_ea(*temps);
        emit_psd_for_node(0x40,-1,'\0','\0',opnd_a,opnd_b,no_node);
        no_node = (gen_node *)0x0;
        opnd_a = copy_ea(dst);
        opnd_b = copy_ea(*temps);
        emit_psd_for_node(0x40,-1,'\0','\0',opnd_b,opnd_a,no_node);
        opnd_a = copy_ea(dst);
        no_node = (gen_node *)0x0;
        opnd_a->type = opnd_a->type & 0xf1 | 1;
        opnd_b = new_ea_operand_with_flags('\a',-1,-1,1,'\0',(label_ref *)0x0);
        emit_psd_for_node(0x60,-1,'\0','\x02',opnd_b,opnd_a,no_node);
      }
      if ((uVar3 & 2) == 0) {
        return;
      }
      opnd_a = copy_ea(src);
      no_node = (gen_node *)0x0;
      opnd_a->type = opnd_a->type & 0xf4 | 4;
      opnd_b = copy_ea(*temps);
      emit_psd_for_node(0x40,-1,'\0','\x01',opnd_a,opnd_b,no_node);
      no_node = (gen_node *)0x0;
      opnd_a = copy_ea(dst);
      opnd_b = copy_ea(*temps);
      emit_psd_for_node(0x40,-1,'\0','\x01',opnd_b,opnd_a,no_node);
      opnd_a = copy_ea(dst);
      no_node = (gen_node *)0x0;
      opnd_a->type = opnd_a->type & 0xf1 | 1;
      opnd_b = new_ea_operand_with_flags('\a',-1,-1,2,'\0',(label_ref *)0x0);
      emit_psd_for_node(0x60,-1,'\0','\x02',opnd_b,opnd_a,no_node);
      return;
    }
    if (op != 0x2600) {
      return;
    }
    bVar1 = dst_addr->type & 0x1f;
    if ((((bVar1 == 2) && (dst_addr->base == 'l')) || ((bVar1 == 8 && (dst_addr->base == 'l')))) ||
       ((bVar1 == 0xd && (dst_addr->labels == (label_ref *)0x0)))) {
      uVar4 = dst_addr->disp;
    }
    else {
      if (dst_addr->labels == (label_ref *)0x0) {
        iVar2 = 0;
      }
      else {
        iVar2 = (int)dst_addr->labels->labno1;
      }
      uVar4 = g_symbol_table[iVar2].frame_offset + dst_addr->disp;
    }
    iVar2 = 0;
    if ((uVar4 & 3) != 0) {
      iVar2 = 4 - (uVar4 & 3);
    }
    uVar3 = node->val - iVar2;
    uVar4 = (int)uVar3 >> 0x1f;
    uVar4 = ((uVar3 ^ uVar4) - uVar4 & 3 ^ uVar4) - uVar4;
    opnd_a = copy_ea(src);
    no_node = (gen_node *)0x0;
    opnd_a->type = opnd_a->type & 0xf1 | 1;
    opnd_b = new_ea_operand_with_flags('\a',-1,-1,uVar3 - uVar4,'\0',(label_ref *)0x0);
    emit_psd_for_node(0x60,-1,'\0','\x02',opnd_b,opnd_a,no_node);
    if (uVar4 != 0) {
      opnd_a = copy_ea(dst);
      no_node = (gen_node *)0x0;
      opnd_a->type = opnd_a->type & 0xf1 | 1;
      opnd_b = new_ea_operand_with_flags('\a',-1,-1,uVar3 - uVar4,'\0',(label_ref *)0x0);
      emit_psd_for_node(0x60,-1,'\0','\x02',opnd_b,opnd_a,no_node);
    }
    if ((uVar4 & 2) != 0) {
      opnd_a = copy_ea(src);
      no_node = (gen_node *)0x0;
      opnd_a->type = opnd_a->type & 0xf4 | 4;
      opnd_b = copy_ea(*temps);
      emit_psd_for_node(0x40,-1,'\0','\x01',opnd_a,opnd_b,no_node);
      no_node = (gen_node *)0x0;
      opnd_a = copy_ea(dst);
      opnd_b = copy_ea(*temps);
      emit_psd_for_node(0x40,-1,'\0','\x01',opnd_b,opnd_a,no_node);
      if ((uVar4 & 1) == 0) goto LAB_00414d14;
      opnd_a = copy_ea(dst);
      no_node = (gen_node *)0x0;
      opnd_a->type = opnd_a->type & 0xf1 | 1;
      opnd_b = new_ea_operand_with_flags('\a',-1,-1,2,'\0',(label_ref *)0x0);
      emit_psd_for_node(0x60,-1,'\0','\x02',opnd_b,opnd_a,no_node);
    }
    if ((uVar4 & 1) != 0) {
      opnd_a = copy_ea(src);
      no_node = (gen_node *)0x0;
      opnd_a->type = opnd_a->type & 0xf4 | 4;
      opnd_b = copy_ea(*temps);
      emit_psd_for_node(0x40,-1,'\0','\0',opnd_a,opnd_b,no_node);
      no_node = (gen_node *)0x0;
      opnd_a = copy_ea(dst);
      opnd_b = copy_ea(*temps);
      emit_psd_for_node(0x40,-1,'\0','\0',opnd_b,opnd_a,no_node);
    }
LAB_00414d14:
    opnd_a = copy_ea(src);
    no_node = (gen_node *)0x0;
    opnd_a->type = opnd_a->type & 0xf1 | 1;
    opnd_b = new_ea_operand_with_flags('\a',-1,-1,-node->val,'\0',(label_ref *)0x0);
    emit_psd_for_node(0x60,-1,'\0','\x02',opnd_b,opnd_a,no_node);
    return;
  }
  iVar2 = 0;
  if (op != 0x2a00) {
    bVar1 = node->type;
    if (((((bVar1 & 0xe0) == 0x60) || ((bVar1 & 0xe0) == 0x80)) && ((bVar1 & 0x18) == 0)) ||
       ((bVar1 & 0xf8) == 0)) {
      move_size = '\0';
      iVar5 = 1;
    }
    else {
      move_size = '\x01';
      iVar5 = 2;
    }
    goto LAB_00414f7c;
  }
  bVar1 = node->type;
  type_class = bVar1 & 0xe0;
  if ((((type_class != 0x60) && (type_class != 0x80)) || ((bVar1 & 0x18) != 0x10)) &&
     ((((bVar1 & 0xf8) != 0x10 && ((bVar1 & 0xf8) != 0x18)) &&
      ((type_class != 0x20 && (type_class != 0x40)))))) {
    bVar1 = dst_addr->type & 0x1f;
    if (((bVar1 != 2) || (dst_addr->base != 'l')) && ((bVar1 != 8 || (dst_addr->base != 'l')))) {
      if (bVar1 != 0xd) goto LAB_00414f38;
      if (dst_addr->labels != (label_ref *)0x0) {
        lab = dst_addr->labels;
        if ((lab == (label_ref *)0x0) || (lab->labno2 != 0)) goto LAB_00414f38;
        iVar5 = 0;
        if (lab != (label_ref *)0x0) {
          iVar5 = (int)lab->labno1;
        }
        if (g_symbol_table[iVar5].sclass != '\x03') {
          iVar5 = 0;
          if (lab != (label_ref *)0x0) {
            iVar5 = (int)lab->labno1;
          }
          if (g_symbol_table[iVar5].sclass != '\x01') {
            iVar5 = 0;
            if (lab != (label_ref *)0x0) {
              iVar5 = (int)lab->labno1;
            }
            if (g_symbol_table[iVar5].sclass != '\t') {
              iVar5 = 0;
              if (lab != (label_ref *)0x0) {
                iVar5 = (int)lab->labno1;
              }
              if (g_symbol_table[iVar5].sclass != '\x04') goto LAB_00414f38;
            }
          }
        }
      }
    }
    if ((((bVar1 == 2) && (dst_addr->base == 'l')) || ((bVar1 == 8 && (dst_addr->base == 'l')))) ||
       ((bVar1 == 0xd && (dst_addr->labels == (label_ref *)0x0)))) {
      iVar5 = dst_addr->disp;
    }
    else {
      iVar5 = 0;
      if (dst_addr->labels != (label_ref *)0x0) {
        iVar5 = (int)dst_addr->labels->labno1;
      }
      iVar5 = g_symbol_table[iVar5].frame_offset + dst_addr->disp;
    }
    if (iVar5 != 0) {
      if ((((bVar1 == 2) && (dst_addr->base == 'l')) || ((bVar1 == 8 && (dst_addr->base == 'l'))))
         || ((bVar1 == 0xd && (dst_addr->labels == (label_ref *)0x0)))) {
        uVar4 = dst_addr->disp;
      }
      else {
        if (dst_addr->labels == (label_ref *)0x0) {
          iVar2 = 0;
        }
        else {
          iVar2 = (int)dst_addr->labels->labno1;
        }
        uVar4 = g_symbol_table[iVar2].frame_offset + dst_addr->disp;
      }
      iVar2 = 0;
      if ((uVar4 & 3) != 0) {
        iVar2 = 4 - (uVar4 & 3);
      }
    }
  }
LAB_00414f38:
  move_size = '\x02';
  iVar5 = 4;
LAB_00414f7c:
  copy_len = node->val - iVar2;
  if (op == 0x2a00) {
    copy_len = copy_len & 0xfffffffc;
  }
  copied = 0;
  if (0 < (int)copy_len) {
    do {
      no_node = (gen_node *)0x0;
      opnd_a = copy_ea(*temps);
      opnd_b = copy_ea(src);
      emit_psd_for_node(0x40,-1,'\0',move_size,opnd_b,opnd_a,no_node);
      src->disp = src->disp + iVar5;
      no_node = (gen_node *)0x0;
      opnd_a = copy_ea(dst);
      opnd_b = copy_ea(*temps);
      emit_psd_for_node(0x40,-1,'\0',move_size,opnd_b,opnd_a,no_node);
      copied = copied + iVar5;
      dst->disp = dst->disp + iVar5;
    } while (copied < (int)copy_len);
  }
  return;
}



