#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_symbol_table
#define g_symbol_table (*(sym_entry * *)(g_sd + 0x1f9b0))


// entry: 00415030
// name : emit_symbol_sized_block_copy
// size : 1068
// sig  : void emit_symbol_sized_block_copy(gen_node * node, ea * src, ea * dst, ea * * temps)


int __cdecl emit_symbol_sized_block_copy(gen_node *node,ea *src,ea *dst,ea **temps)

{
  gen_node *right;
  uint uVar1;
  int iVar2;
  int n;
  ea *peVar3;
  ea *peVar4;
  uint uVar5;
  byte bVar6;
  gen_node *pgVar7;
  uchar move_size;
  void *block_size;
  label_ref *lab;
  
  pgVar7 = node->child;
  right = (gen_node *)0x0;
  if (pgVar7 != (gen_node *)0x0) {
    right = pgVar7->next;
  }
  if (right->desc->mem_ea == (ea *)0x0) {
    bVar6 = 0;
  }
  else {
    right = (gen_node *)0x0;
    if (pgVar7 != (gen_node *)0x0) {
      right = pgVar7->next;
    }
    bVar6 = right->desc->mem_ea->type & 0x1f;
  }
  if (bVar6 == 0) {
    right = (gen_node *)0x0;
    if (pgVar7 != (gen_node *)0x0) {
      right = pgVar7->next;
    }
    if (((right->desc->dest).type & 0x1f) == 0) {
      right = (gen_node *)0x0;
      if (pgVar7 != (gen_node *)0x0) {
        right = pgVar7->next;
      }
      if ((right->desc->flags2 & 8) == 0) {
        right = (gen_node *)0x0;
        if (pgVar7 != (gen_node *)0x0) {
          right = pgVar7->next;
        }
        peVar3 = &right->desc->value;
      }
      else {
        peVar3 = &g_ea_pop;
      }
    }
    else if (pgVar7 == (gen_node *)0x0) {
      peVar3 = (ea *)((*(int *)0x00000028) + 0x74);
    }
    else {
      peVar3 = &pgVar7->next->desc->dest;
    }
  }
  else if (pgVar7 == (gen_node *)0x0) {
    peVar3 = *(ea **)((*(int *)0x00000028) + 0x5c);
  }
  else {
    peVar3 = pgVar7->next->desc->mem_ea;
  }
  uVar1 = (int)pgVar7->symx + 0xb6;
  uVar5 = (int)uVar1 >> 0x1f;
  block_size = g_symbol_table[(uVar1 ^ uVar5) - uVar5].list_10;
  if (((int)block_size < 0x81) &&
     ((bVar6 = peVar3->type, (bVar6 & 0x40) != 0 || ((bVar6 & 0x1f) == 7)))) {
    bVar6 = bVar6 & 0x1f;
    if (((((bVar6 == 2) && (peVar3->base == 'l')) || ((bVar6 == 8 && (peVar3->base == 'l')))) &&
        (uVar1 = peVar3->disp >> 0x1f, ((peVar3->disp ^ uVar1) - uVar1 & 3 ^ uVar1) == uVar1)) ||
       ((((bVar6 == 0xd || (bVar6 == 7)) && (peVar3->labels == (label_ref *)0x0)) &&
        (uVar1 = peVar3->disp >> 0x1f, ((peVar3->disp ^ uVar1) - uVar1 & 3 ^ uVar1) == uVar1)))) {
LAB_00415245:
      move_size = '\x02';
      iVar2 = 4;
      goto LAB_00415261;
    }
    if (((bVar6 == 0xd) || (bVar6 == 7)) &&
       ((lab = peVar3->labels, lab != (label_ref *)0x0 && (lab->labno2 == 0)))) {
      iVar2 = 0;
      if (lab != (label_ref *)0x0) {
        iVar2 = (int)lab->labno1;
      }
      if (g_symbol_table[iVar2].sclass != '\x03') {
        iVar2 = 0;
        if (lab != (label_ref *)0x0) {
          iVar2 = (int)lab->labno1;
        }
        if (g_symbol_table[iVar2].sclass != '\x01') {
          iVar2 = 0;
          if (lab != (label_ref *)0x0) {
            iVar2 = (int)lab->labno1;
          }
          if (g_symbol_table[iVar2].sclass != '\t') {
            iVar2 = 0;
            if (lab != (label_ref *)0x0) {
              iVar2 = (int)lab->labno1;
            }
            if (g_symbol_table[iVar2].sclass != '\x04') goto LAB_00415254;
          }
        }
      }
      iVar2 = 0;
      if (lab != (label_ref *)0x0) {
        iVar2 = (int)lab->labno1;
      }
      if ((g_symbol_table[iVar2].frame_offset + peVar3->disp & 3U) == 0) goto LAB_00415245;
    }
  }
LAB_00415254:
  move_size = '\0';
  iVar2 = 1;
LAB_00415261:
  for (n = (int)block_size / iVar2; n != 0; n = n + -1) {
    peVar3 = copy_ea(src);
    pgVar7 = (gen_node *)0x0;
    peVar3->type = peVar3->type & 0xf4 | 4;
    peVar4 = copy_ea(*temps);
    emit_psd_for_node(0x40,-1,'\0',move_size,peVar3,peVar4,pgVar7);
    pgVar7 = (gen_node *)0x0;
    peVar3 = copy_ea(dst);
    peVar4 = copy_ea(*temps);
    emit_psd_for_node(0x40,-1,'\0',move_size,peVar4,peVar3,pgVar7);
    if ((n != 1) || ((iVar2 == 4 && (((uint)block_size & 3) != 0)))) {
      peVar3 = copy_ea(dst);
      pgVar7 = (gen_node *)0x0;
      peVar3->type = peVar3->type & 0xf1 | 1;
      peVar4 = new_ea_operand_with_flags('\a',-1,-1,iVar2,'\0',(label_ref *)0x0);
      emit_psd_for_node(0x60,-1,'\0','\x02',peVar4,peVar3,pgVar7);
    }
  }
  if (iVar2 == 4) {
    if (((uint)block_size & 2) != 0) {
      peVar3 = copy_ea(src);
      pgVar7 = (gen_node *)0x0;
      peVar3->type = peVar3->type & 0xf4 | 4;
      peVar4 = copy_ea(*temps);
      emit_psd_for_node(0x40,-1,'\0','\x01',peVar3,peVar4,pgVar7);
      pgVar7 = (gen_node *)0x0;
      peVar3 = copy_ea(dst);
      peVar4 = copy_ea(*temps);
      emit_psd_for_node(0x40,-1,'\0','\x01',peVar4,peVar3,pgVar7);
      if (((uint)block_size & 1) == 0) {
        return;
      }
      peVar3 = copy_ea(dst);
      pgVar7 = (gen_node *)0x0;
      peVar3->type = peVar3->type & 0xf1 | 1;
      peVar4 = new_ea_operand_with_flags('\a',-1,-1,2,'\0',(label_ref *)0x0);
      emit_psd_for_node(0x60,-1,'\0','\x02',peVar4,peVar3,pgVar7);
    }
    if (((uint)block_size & 1) != 0) {
      peVar3 = copy_ea(src);
      pgVar7 = (gen_node *)0x0;
      peVar3->type = peVar3->type & 0xf4 | 4;
      peVar4 = copy_ea(*temps);
      emit_psd_for_node(0x40,-1,'\0','\0',peVar3,peVar4,pgVar7);
      pgVar7 = (gen_node *)0x0;
      peVar3 = copy_ea(dst);
      peVar4 = copy_ea(*temps);
      emit_psd_for_node(0x40,-1,'\0','\0',peVar4,peVar3,pgVar7);
    }
  }
  return;
}



