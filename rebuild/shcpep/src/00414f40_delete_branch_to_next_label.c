#include "decls.h"
#include "imports.h"
#include "pep_rules.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_stage_flags
#define g_stage_flags (*(unsigned char *)(g_sd + 0x6d64))


// entry: 00414f40
// name : delete_branch_to_next_label
// size : 377
// sig  : void delete_branch_to_next_label(psd * label_rec)


int __cdecl delete_branch_to_next_label(psd *label_rec)

{
  code_node *block;
  char has_code;
  psd *rec;
  code_node *prev_block;
  label_block_ref *prev_ref;
  int release_mode;
  short dest_labno;
  label_block_ref *next_ref;
  psd_op op;
  label_block_ref *ref;
  label_block_ref *ref_list;
  symbol *sym;
  short sym_labno;
  
  release_mode = 2;
  rec = (psd *)0x0;
  prev_block = (code_node *)0x0;
  prev_ref = (label_block_ref *)0x0;
  if (label_rec->op == OP_LABEL) {
    if (((byte)g_stage_flags & 8) != 0) {
      _printf(s_nxtbrdel_start__code_pointer___0_00427b7c,label_rec);
    }
    block = (code_node *)&label_rec[-1].expno;
    while ((block != (code_node *)0x0 &&
           (has_code = block_has_code_records(prev_block), has_code == '\0'))) {
      prev_block = find_preceding_nonempty_block(block);
      block = prev_block;
    }
    if (prev_block != (code_node *)0x0) {
      rec = find_block_final_record(prev_block);
    }
    if ((rec != (psd *)0x0) &&
       ((((op = rec->op, op == OP_JUMP || (op == OP_JUMPT)) || (op == OP_JUMPF)) ||
        (op == OP_RETURN)))) {
      if (op == OP_RETURN) {
        release_mode = 0;
      }
      dest_labno = rec->ea1->labels->labno1;
      if (*(short *)&label_rec->ea1 == dest_labno) {
        if (op == OP_JUMP) {
          sym = g_symbol_hash[(int)dest_labno % 0x3fd];
          sym_labno = sym->number;
          while ((int)sym_labno != (int)dest_labno) {
            sym = sym->hash_next;
            sym_labno = sym->number;
          }
          ref_list = sym->ref_blocks;
          if (ref_list != (label_block_ref *)0x0) {
            if (ref_list->block == prev_block) {
              ref_list->block = (code_node *)0x0;
            }
            next_ref = ref_list->next;
            while (ref = next_ref, ref != (label_block_ref *)0x0) {
              if ((ref->block != (code_node *)0x0) && (ref->block == prev_block)) {
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
#if SHC_REBUILD_UPDATED
        pep_log_xj_next((int *)prev_block, rec->op);
#endif
        release_label_refs_of_record(rec,release_mode);
        delete_psd_record(rec);
        prev_block->target_labno = 0;
        if (((byte)g_stage_flags & 8) != 0) {
          _printf(s_delete_code___08lx__exit_number__00427b54,rec,0);
        }
      }
    }
    if (prev_block != (code_node *)0x0) {
      delete_trailing_branches_to_label(prev_block,label_rec);
    }
  }
  return;
}



