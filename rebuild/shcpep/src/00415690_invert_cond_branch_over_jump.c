#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_stage_flags
#define g_stage_flags (*(unsigned char *)(g_sd + 0x6d64))


// entry: 00415690
// name : invert_cond_branch_over_jump
// size : 456
// sig  : void invert_cond_branch_over_jump(psd * label_rec)


int __cdecl invert_cond_branch_over_jump(psd *label_rec)

{
  short labno;
  char has_code;
  code_node *block;
  psd *rec;
  psd *cond_rec;
  code_node *cond_block;
  symbol *sym;
  short label_no;
  psd_op op;
  label_block_ref *prev_ref;
  label_block_ref *ref;
  
  if (((byte)g_stage_flags & 2) != 0) {
    _printf(s_d_condbr_start__00427ba4);
  }
  if ((label_rec != (psd *)0x0) && (label_rec->op == OP_LABEL)) {
    label_no = *(short *)&label_rec->ea1;
    if ((&label_rec[-1].expno != (int *)0x0) &&
       (block = find_preceding_nonempty_block((code_node *)&label_rec[-1].expno),
       block != (code_node *)0x0)) {
      do {
        has_code = block_has_code_records(block);
        if (has_code != '\0') break;
        block = find_preceding_nonempty_block(block);
      } while (block != (code_node *)0x0);
      if (((((((block != (code_node *)0x0) && (labno = block->target_labno, block->labno == 0)) &&
             (labno != 0)) && (rec = find_block_final_record(block), rec != (psd *)0x0)) &&
           (((rec->op == OP_JUMP || (rec->op == OP_RETURN)) &&
            ((cond_rec = find_previous_psd_record(block,rec), cond_rec == (psd *)0x0 &&
             ((cond_block = find_preceding_nonempty_block(block), cond_block != (code_node *)0x0 &&
              (cond_rec = find_block_final_record(cond_block), cond_rec != (psd *)0x0)))))))) &&
          ((op = cond_rec->op, op == OP_JUMPT || (op == OP_JUMPF)))) &&
         ((cond_block->target_labno != 0 && (cond_block->target_labno == label_no)))) {
        if (op == OP_JUMPT) {
          cond_rec->op = OP_JUMPF;
        }
        else if (op == OP_JUMPF) {
          cond_rec->op = OP_JUMPT;
        }
        release_label_refs_of_record(cond_rec,2);
        cond_rec->ea1->labels->labno1 = labno;
        cond_block->target_labno = block->target_labno;
        sym = find_label_symbol(labno);
        prev_ref = (label_block_ref *)0x0;
        for (ref = sym->ref_blocks; ref != (label_block_ref *)0x0; ref = ref->next) {
          if ((ref->block == block) &&
             (ref->block = (code_node *)0x0, prev_ref != (label_block_ref *)0x0)) {
            prev_ref->next = ref->next;
            pool_free(ref,8);
            break;
          }
          prev_ref = ref;
        }
        delete_psd_record(rec);
        block->target_labno = 0;
        if (((byte)g_stage_flags & 2) != 0) {
          block->target_labno = 0;
          _printf(s_delete_code___08lx__exit_number__00427b54,rec,0);
        }
      }
    }
  }
  return;
}



