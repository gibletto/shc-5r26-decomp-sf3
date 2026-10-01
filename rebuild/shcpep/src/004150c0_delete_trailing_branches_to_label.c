#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_node_list
#define g_current_node_list (*(code_node * *)(g_sd + 0x6d70))


// entry: 004150c0
// name : delete_trailing_branches_to_label
// size : 360
// sig  : void delete_trailing_branches_to_label(code_node * block, psd * label_rec)


int __cdecl delete_trailing_branches_to_label(code_node *block,psd *label_rec)

{
  char has_code;
  psd *rec;
  label_block_ref *prev_ref;
  int release_mode;
  code_node *prev_block;
  short dest_labno;
  label_block_ref *next_ref;
  code_node *node;
  psd_op op;
  label_block_ref *ref;
  label_block_ref *ref_list;
  symbol *sym;
  short sym_labno;
  
  do {
    if (block == (code_node *)0x0) {
      return;
    }
    release_mode = 2;
    prev_ref = (label_block_ref *)0x0;
    rec = (psd *)0x0;
    has_code = block_has_code_records(block);
    while (has_code == '\0') {
      node = g_current_node_list;
      if (g_current_node_list == block) {
        return;
      }
      for (; (node != (code_node *)0x0 && (node != block)); node = node->next_block) {
        prev_block = node;
      }
      has_code = block_has_code_records(prev_block);
      block = prev_block;
    }
    if (block != (code_node *)0x0) {
      rec = find_block_final_record(block);
    }
    if (rec == (psd *)0x0) {
      return;
    }
    op = rec->op;
    if ((((op != OP_JUMP) && (op != OP_JUMPT)) && (op != OP_JUMPF)) && (op != OP_RETURN)) {
      return;
    }
    if (op == OP_RETURN) {
      release_mode = 0;
    }
    dest_labno = rec->ea1->labels->labno1;
    if (*(short *)&label_rec->ea1 != dest_labno) {
      return;
    }
    if (op == OP_JUMP) {
      sym = g_symbol_hash[(int)dest_labno % 0x3fd];
      sym_labno = sym->number;
      while ((int)sym_labno != (int)dest_labno) {
        sym = sym->hash_next;
        sym_labno = sym->number;
      }
      ref_list = sym->ref_blocks;
      if (ref_list != (label_block_ref *)0x0) {
        if (ref_list->block == block) {
          ref_list->block = (code_node *)0x0;
        }
        next_ref = ref_list->next;
        while (ref = next_ref, ref != (label_block_ref *)0x0) {
          if ((ref->block != (code_node *)0x0) && (block == ref->block)) {
            ref->block = (code_node *)0x0;
            if (prev_ref == (label_block_ref *)0x0) {
              prev_ref = ref_list;
            }
            prev_ref->next = ref->next;
            pool_free(ref,8);
            break;
          }
          prev_ref = ref;
          next_ref = ref->next;
        }
      }
    }
    release_label_refs_of_record(rec,release_mode);
    delete_psd_record(rec);
    block->target_labno = 0;
  } while( true );
}



