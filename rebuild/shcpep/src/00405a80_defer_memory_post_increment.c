#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_rec_def_mask_hi
#define g_rec_def_mask_hi (*(unsigned int *)(g_sd + 0x6d5c))
#undef g_rec_def_mask_lo
#define g_rec_def_mask_lo (*(unsigned int *)(g_sd + 0x6d58))
#undef g_rec_use_mask_hi
#define g_rec_use_mask_hi (*(unsigned int *)(g_sd + 0x5c44))
#undef g_rec_use_mask_lo
#define g_rec_use_mask_lo (*(psd * *)(g_sd + 0x5c40))


// entry: 00405a80
// name : defer_memory_post_increment
// size : 2091
// sig  : char defer_memory_post_increment(code_node * node, psd * load, int index)


char __cdecl defer_memory_post_increment(code_node *node,psd *load,int index)

{
  unsigned char _frec_71[113];
#define movi_reg (*(char *)(_frec_71 + 0))
#define cur_node (*(code_node * *)(_frec_71 + 1))
#define local_6c (*(psd * *)(_frec_71 + 5))
#define add (*(psd * *)(_frec_71 + 9))
#define store (*(psd * *)(_frec_71 + 13))
#define local_60 (*(psd * *)(_frec_71 + 17))
#define local_58 (*(psd * *)(_frec_71 + 25))
#define use_rec (*(psd * *)(_frec_71 + 33))
#define movi (*(psd * *)(_frec_71 + 37))
#define saved_movi (*(psd *)(_frec_71 + 41))
#define saved_add (*(psd *)(_frec_71 + 65))
#define saved_store (*(psd *)(_frec_71 + 89))
  uchar reg;
  char ok;
  uint uVar1;
  psd *overwrite;
  int n;
  psd *rec;
  undefined4 *src_word;
  int pos;
  int rec_pos;
  psd *ppVar2;
  bool in_mask;
  psd_op add_op;
  bool blocked;
  undefined4 init_word;
  ea *operand;
  code_node *src_node;
  bool via_movi;
  
  blocked = false;
  cur_node = node;
  pos = index + 1;
  if (index + 1 < 0xf) {
    local_58 = load + 1;
  }
  else {
    cur_node = node->next;
    if ((cur_node == (code_node *)0x0) || (local_58 = cur_node->psd, local_58 == (psd *)0x0)) {
      return '\0';
    }
    pos = 0;
  }
  if (((local_58->ea1->type & 0x1f) != 7) || (local_58->ea1->labels != (label_ref *)0x0)) {
    return '\0';
  }
  if (local_58->op == OP_ADD) {
    via_movi = false;
    add_op = OP_ADD;
    add = local_58;
  }
  else {
    if (local_58->op != OP_MOVI) {
      return '\0';
    }
    via_movi = true;
    pos = pos + 1;
    if (pos < 0xf) {
      add = local_58 + 1;
    }
    else {
      cur_node = cur_node->next;
      if ((cur_node == (code_node *)0x0) || (add = cur_node->psd, add == (psd *)0x0)) {
        return '\0';
      }
      pos = 0;
    }
    if (((add->misc & 0x20U) == 0) ||
       (((add_op = add->op, add_op != OP_ADD && (add_op != OP_SUB)) ||
        (ok = operands_equal(local_58->ea2,add->ea1), movi = local_58, ok == '\0')))) {
      return '\0';
    }
  }
  ok = operands_equal(load->ea2,add->ea2);
  if (ok == '\0') {
    return '\0';
  }
  pos = pos + 1;
  if (pos < 0xf) {
    store = add + 1;
  }
  else {
    cur_node = cur_node->next;
    if ((cur_node == (code_node *)0x0) || (store = cur_node->psd, store == (psd *)0x0)) {
      return '\0';
    }
    pos = 0;
  }
  if ((((store->misc & 0x20U) != 0) && (store->op == OP_MOV)) &&
     ((((store->flg ^ load->flg) & 3U) == 0 &&
      ((ok = operands_equal(store->ea1,load->ea2), ok != '\0' &&
       (ok = operands_equal(store->ea2,load->ea1), ok != '\0')))))) {
    reg = store->ea1->base;
    ok = operand_uses_register(store,reg,'\x02');
    if (ok == '\0') {
      pos = pos + 1;
      if (pos < 0xf) {
        local_6c = store + 1;
      }
      else {
        cur_node = cur_node->next;
        if ((cur_node == (code_node *)0x0) || (local_6c = cur_node->psd, local_6c == (psd *)0x0)) {
          return '\0';
        }
        pos = 0;
      }
      if ((((local_6c->misc & 0x20U) == 0) || (uVar1 = is_record_volatile(local_6c), uVar1 != 0)) ||
         (ok = operands_equal(local_6c->ea2,add->ea2), ok == '\0')) {
        return '\0';
      }
      if (via_movi) {
        if ((((add_op != OP_ADD) || (local_6c->op != OP_SUB)) &&
            ((add_op != OP_SUB || (local_6c->op != OP_ADD)))) || ((local_6c->ea1->type & 0x1f) != 1)
           ) {
          return '\0';
        }
        movi_reg = add->ea1->base;
        if (local_6c->ea1->base != movi_reg) {
          return '\0';
        }
      }
      else if (((local_6c->op != OP_ADD) || (operand = local_6c->ea1, (operand->type & 0x1f) != 7))
              || ((operand->labels != (label_ref *)0x0 || (add->ea1->disp + operand->disp != 0)))) {
        return '\0';
      }
      g_rec_use_mask_lo = (psd *)0x0;
      g_rec_use_mask_hi = 0;
      g_rec_def_mask_lo = 0;
      g_rec_def_mask_hi = 0;
      accumulate_operand_register_masks(load,1);
      uVar1 = g_rec_use_mask_hi;
      ppVar2 = g_rec_use_mask_lo;
      local_60 = g_rec_use_mask_lo;
      pos = pos + 1;
      if (pos < 0xf) {
        local_58 = local_6c + 1;
      }
      else {
        cur_node = cur_node->next;
        if ((cur_node != (code_node *)0x0) && (local_58 = cur_node->psd, local_58 != (psd *)0x0)) {
          pos = 0;
        }
      }
      src_node = cur_node;
      use_rec = (psd *)0x0;
      rec = local_58;
      rec_pos = pos;
      while (cur_node != (code_node *)0x0) {
        for (; rec != (psd *)0x0; rec = rec + 1) {
          if (0xe < rec_pos) goto LAB_0040601c;
          if (rec->op == OP_CALL) {
            return '\0';
          }
          if (rec->op == OP_CASEJMP) {
            if (reg == '\0') {
              return '\0';
            }
            break;
          }
          ok = compute_record_register_masks(rec);
          if (ok != '\0') {
            return '\0';
          }
          if (((char)reg < '\0') || ('_' < (char)reg)) {
            if ((char)reg < '`') {
              in_mask = false;
            }
            else {
              in_mask = (g_reg_mask_table[(char)reg] & g_rec_def_mask_hi) != 0;
            }
          }
          else {
            in_mask = (g_reg_mask_table[(char)reg] & g_rec_def_mask_lo) != 0;
          }
          if (in_mask) {
            overwrite = psd_overwrites_register(rec,reg);
            if (overwrite == (psd *)0x0) {
              return '\0';
            }
            break;
          }
          if ((g_rec_use_mask_hi & g_reg_mask_table[0x7f]) != 0) {
            blocked = true;
          }
          if (((g_rec_def_mask_lo & (uint)ppVar2) != 0) || ((g_rec_def_mask_hi & uVar1) != 0)) {
            blocked = true;
          }
          if (via_movi) {
            if ((movi_reg < '\0') || ('_' < movi_reg)) {
              if (movi_reg < '`') {
                in_mask = false;
              }
              else {
                in_mask = (g_reg_mask_table[movi_reg] & g_rec_def_mask_hi) != 0;
              }
            }
            else {
              in_mask = (g_reg_mask_table[movi_reg] & g_rec_def_mask_lo) != 0;
            }
            if (in_mask) {
              blocked = true;
            }
          }
          if (((char)reg < '\0') || ('_' < (char)reg)) {
            if ((char)reg < '`') {
              in_mask = false;
            }
            else {
              in_mask = (g_reg_mask_table[(char)reg] & g_rec_use_mask_hi) != 0;
            }
          }
          else {
            in_mask = (g_reg_mask_table[(char)reg] & (uint)g_rec_use_mask_lo) != 0;
          }
          if ((in_mask) && (use_rec = rec, blocked)) {
            use_rec = (psd *)0x0;
            break;
          }
          rec_pos = rec_pos + 1;
        }
        if (rec_pos < 0xf) break;
LAB_0040601c:
        cur_node = cur_node->next;
        if ((cur_node != (code_node *)0x0) && (rec = cur_node->psd, rec != (psd *)0x0)) {
          rec_pos = 0;
        }
      }
      if (use_rec == (psd *)0x0) {
        return '\0';
      }
      rec_pos = index + 1;
      cur_node = node;
      if (index + 1 < 0xf) {
        rec = load + 1;
      }
      else {
        cur_node = node->next;
        if ((cur_node != (code_node *)0x0) && (rec = cur_node->psd, rec != (psd *)0x0)) {
          rec_pos = 0;
        }
      }
      if (via_movi) {
        src_word = &g_empty_psd;
        ppVar2 = &saved_movi;
        for (n = 6; n != 0; n = n + -1) {
          init_word = *src_word;
          ppVar2->op = (char)init_word;
          ppVar2->flg = (char)((uint)init_word >> 8);
          ppVar2->misc = (char)((uint)init_word >> 0x10);
          ppVar2->tmp = (char)((uint)init_word >> 0x18);
          src_word = src_word + 1;
          ppVar2 = (psd *)&ppVar2->sptravel;
        }
        local_60 = &saved_movi;
        move_psd_record(movi,local_60);
      }
      src_word = &g_empty_psd;
      ppVar2 = &saved_add;
      for (n = 6; n != 0; n = n + -1) {
        init_word = *src_word;
        ppVar2->op = (char)init_word;
        ppVar2->flg = (char)((uint)init_word >> 8);
        ppVar2->misc = (char)((uint)init_word >> 0x10);
        ppVar2->tmp = (char)((uint)init_word >> 0x18);
        src_word = src_word + 1;
        ppVar2 = (psd *)&ppVar2->sptravel;
      }
      move_psd_record(add,&saved_add);
      src_word = &g_empty_psd;
      ppVar2 = &saved_store;
      for (n = 6; n != 0; n = n + -1) {
        init_word = *src_word;
        ppVar2->op = (char)init_word;
        ppVar2->flg = (char)((uint)init_word >> 8);
        ppVar2->misc = (char)((uint)init_word >> 0x10);
        ppVar2->tmp = (char)((uint)init_word >> 0x18);
        src_word = src_word + 1;
        ppVar2 = (psd *)&ppVar2->sptravel;
      }
      move_psd_record(store,&saved_store);
      local_6c = (psd *)pos;
      while (src_node != (code_node *)0x0) {
        if (rec != (psd *)0x0) {
          while (local_58 != (psd *)0x0) {
            if (0xe < rec_pos) goto LAB_00406170;
            if ((0xe < (int)local_6c) || (move_psd_record(local_58,rec), local_58 == use_rec))
            break;
            rec = rec + 1;
            rec_pos = rec_pos + 1;
            local_58 = local_58 + 1;
            local_6c = (psd *)((int)local_6c + 1);
            if (rec == (psd *)0x0) break;
          }
        }
        if ((rec_pos < 0xf) && ((int)local_6c < 0xf)) break;
LAB_00406170:
        if ((rec_pos == 0xf) &&
           ((cur_node = cur_node->next, cur_node != (code_node *)0x0 &&
            (rec = cur_node->psd, rec != (psd *)0x0)))) {
          rec_pos = 0;
        }
        if (((local_6c == (psd *)0xf) && (src_node = src_node->next, src_node != (code_node *)0x0))
           && (local_58 = src_node->psd, local_58 != (psd *)0x0)) {
          local_6c = (psd *)0x0;
        }
      }
      if (via_movi) {
        rec_pos = rec_pos + 1;
        if (rec_pos < 0xf) {
          rec = rec + 1;
        }
        else {
          cur_node = cur_node->next;
          if ((cur_node != (code_node *)0x0) && (rec = cur_node->psd, rec != (psd *)0x0)) {
            rec_pos = 0;
          }
        }
        move_psd_record(local_60,rec);
      }
      rec_pos = rec_pos + 1;
      if (rec_pos < 0xf) {
        rec = rec + 1;
      }
      else {
        cur_node = cur_node->next;
        if ((cur_node != (code_node *)0x0) && (rec = cur_node->psd, rec != (psd *)0x0)) {
          rec_pos = 0;
        }
      }
      move_psd_record(&saved_add,rec);
      if (rec_pos + 1 < 0xf) {
        rec = rec + 1;
      }
      else if (cur_node->next != (code_node *)0x0) {
        rec = cur_node->next->psd;
      }
      move_psd_record(&saved_store,rec);
      delete_psd_record(use_rec);
      return '\x01';
    }
  }
  return '\0';
#undef movi_reg
#undef cur_node
#undef local_6c
#undef add
#undef store
#undef local_60
#undef local_58
#undef use_rec
#undef movi
#undef saved_movi
#undef saved_add
#undef saved_store
}



