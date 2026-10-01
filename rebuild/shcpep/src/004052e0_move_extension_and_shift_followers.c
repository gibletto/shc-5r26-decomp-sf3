#include "decls.h"
#include "imports.h"

// entry: 004052e0
// name : move_extension_and_shift_followers
// size : 380
// sig  : psd * move_extension_and_shift_followers(code_node * node, psd * ext, psd * slot, int ext_index, int slot_index)


psd * __cdecl
move_extension_and_shift_followers(code_node *node,psd *ext,psd *slot,int ext_index,int slot_index)

{
  psd *ppVar1;
  psd *ppVar2;
  byte uses;
  psd *rec;
  int pos;
  int dst_index;
  psd *dst;
  byte uses_src;
  byte uses_dst;
  psd *src_use;
  psd *dst_use;
  uchar dst_reg;
  uchar src_reg;
  
  dst_use = (psd *)0x0;
  src_use = (psd *)0x0;
  uses_dst = 0;
  uses_src = 0;
  copy_psd_record(ext,slot);
  dst_index = slot_index + 1;
  if (dst_index == 0xf) {
    dst_index = 0;
    dst = node->psd;
  }
  else {
    dst = slot + 1;
  }
  dst_reg = ext->ea2->base;
  src_reg = ext->ea1->base;
  for (rec = find_next_psd_record(node,ext); ppVar1 = src_use, ppVar2 = dst_use, rec != (psd *)0x0;
      rec = find_next_psd_record(node,rec)) {
    if (rec->ea1 != (ea *)0x0) {
      uses_dst = operand_uses_register(rec,dst_reg,'\x01');
      uses_src = operand_uses_register(rec,src_reg,'\x01');
    }
    if (rec->ea2 != (ea *)0x0) {
      uses = operand_uses_register(rec,dst_reg,'\x02');
      uses_dst = uses_dst | uses;
      uses = operand_uses_register(rec,src_reg,'\x02');
      uses_src = uses_src | uses;
    }
    ppVar1 = rec;
    if ((uses_src != 0) || (ppVar1 = src_use, ppVar2 = rec, uses_dst != 0)) break;
  }
  dst_use = ppVar2;
  src_use = ppVar1;
  if (uses_dst != 0) {
    rec = ext + 1;
    pos = ext_index + 1;
    while (node != (code_node *)0x0) {
      for (; rec != (psd *)0x0; rec = rec + 1) {
        if (0xe < pos) goto LAB_00405437;
        if (src_use == rec) break;
        dst_index = dst_index + 1;
        copy_psd_record(rec,dst);
        if (dst_index == 0xf) {
          dst_index = 0;
          dst = node->psd;
        }
        else {
          dst = dst + 1;
        }
        if (dst_use == rec) break;
        pos = pos + 1;
      }
      if (pos < 0xf) {
        return dst;
      }
LAB_00405437:
      node = node->next;
      if (node != (code_node *)0x0) {
        rec = node->psd;
        pos = 0;
      }
    }
  }
  return dst;
}



