#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_stage_flags
#define g_stage_flags (*(unsigned char *)(g_sd + 0x6d64))


// entry: 004174f0
// name : move_record_into_branch_slot
// size : 184
// sig  : void move_record_into_branch_slot(psd * cand, code_node * node, psd * branch)


int __cdecl move_record_into_branch_slot(psd *cand,code_node *node,psd *branch)

{
  psd *slot;
  code_node *next_node;
  int i;
  
  if (((byte)g_stage_flags & 2) != 0) {
    _printf(s_mvcode_start__00427bec);
  }
  if (((cand != (psd *)0x0) && (node != (code_node *)0x0)) && (branch != (psd *)0x0)) {
    next_node = node->next;
    while (next_node != (code_node *)0x0) {
      node = node->next;
      next_node = node->next;
    }
    slot = node->psd;
    i = 0;
    do {
      if ((slot == (psd *)0x0) || (slot == branch)) break;
      i = i + 1;
      slot = slot + 1;
    } while (i < 0xf);
    if (i < 0xe) {
      slot = branch + 1;
    }
    else {
      next_node = (code_node *)alloc_zeroed_flushing_blocks(0x178);
      node->next = next_node;
      slot = next_node->psd;
    }
    if (slot->op == OP_DUMMY) {
      copy_psd_record(branch,slot);
      copy_psd_record(cand,branch);
      delete_psd_record(cand);
      branch->flg = branch->flg | 0x40;
      slot->misc = slot->misc | 0x80;
    }
  }
  if (((byte)g_stage_flags & 2) != 0) {
    _printf(s_mvcode_end__00427bdc);
  }
  return;
}



