#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_node_list
#define g_current_node_list (*(code_node * *)(g_sd + 0x6d70))


// entry: 004152f0
// name : clean_records_and_merge_common_code
// size : 285
// sig  : void clean_records_and_merge_common_code(void)


int __cdecl clean_records_and_merge_common_code(void)

{
  unsigned char _frec_18[24];
#define end_label (*(psd *)(_frec_18 + 0))
  undefined4 uVar1;
  code_node *block;
  short labno;
  int i;
  undefined4 *src_word;
  psd *rec;
  code_node *node;
  psd_op op;
  
  src_word = &g_empty_psd;
  rec = &end_label;
  for (i = 6; i != 0; i = i + -1) {
    uVar1 = *src_word;
    rec->op = (char)uVar1;
    rec->flg = (char)((uint)uVar1 >> 8);
    rec->misc = (char)((uint)uVar1 >> 0x10);
    rec->tmp = (char)((uint)uVar1 >> 0x18);
    src_word = src_word + 1;
    rec = (psd *)&rec->sptravel;
  }
  delete_switch_markers_from_cursor();
  block = g_current_node_list;
  do {
    node = block;
    if (block == (code_node *)0x0) {
      end_label.op = OP_LABEL;
      delete_unreachable_record(&end_label);
      return;
    }
    for (; node != (code_node *)0x0; node = node->next) {
      i = 0;
      rec = node->psd;
      while (rec != (psd *)0x0) {
        if (rec->op != OP_DUMMY) {
          labno = get_record_source_labno(rec);
          delete_unreachable_record(rec);
          if (((labno != 0) && (rec->op == OP_DUMMY)) &&
             (decrement_label_ref_count(labno), block->target_labno == labno)) {
            unlink_block_from_target_label_refs(block);
            clear_block_flags_and_labels(block);
          }
          if (rec->op == OP_LABEL) {
            merge_common_block_tails(rec);
            delete_branch_to_next_label(rec);
          }
          op = rec->op;
          if ((((OP_CALL < op) && (op < OP_MOV_LOC)) || ((op == OP_EXIT || (op == OP_RETURN)))) ||
             (((OP_SETT < op && (op < OP_BSR)) ||
              ((op == OP_JMP ||
               ((((OP_JSR < op && (op < OP_BSRF)) || (op == OP_BRAF)) || (op == OP_RTE))))))))
          break;
        }
        i = i + 1;
        rec = rec + 1;
        if (0xe < i) break;
      }
    }
    block = block->next_block;
  } while( true );
#undef end_label
}



