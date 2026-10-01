#include "decls.h"
#include "imports.h"
#include "pep_rules.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_node_list
#define g_current_node_list (*(code_node * *)(g_sd + 0x6d70))
#undef g_current_section
#define g_current_section (*(request_section * *)(g_sd + 0x5d0c))
#undef g_stage_flags
#define g_stage_flags (*(unsigned char *)(g_sd + 0x6d64))


// entry: 00413ce0
// name : make_common_code_block
// size : 886
// sig  : code_node * make_common_code_block(code_node * block_a, code_node * block_b, psd * common_a, psd * common_b, short mode)


code_node * __cdecl
make_common_code_block(code_node *block_a,code_node *block_b,psd *common_a,psd *common_b,short mode)

{
  code_node *new_block;
  int new_labno;
  symbol *label_sym;
  psd *rec;
  short *labno_ptr;
  short node_count;
  short n;
  psd *src;
  short node_index;
  short slot_count;
  code_node *cur_node;
  code_node *node;
  psd_op op;
  
  node_index = 0;
  node_count = (short)((mode + -1 + g_common_tail_count) / 0xf) + 1;
  if (((byte)g_stage_flags & 0x20) != 0) {
    _printf(s_make_node_number___d_00427844,(int)node_count);
  }
  node = (code_node *)0x0;
  new_block = cur_node;
  for (n = node_count; n != 0; n = n + -1) {
    new_block = (code_node *)alloc_zeroed_flushing_blocks(0x178);
    new_block->next = node;
    node = new_block;
  }
  n = 0;
  for (node = g_current_node_list; node != (code_node *)0x0; node = node->next_block) {
    if (block_a == node) {
      n = n + 1;
    }
    if (block_b == node) {
      n = n + 1;
    }
  }
  if (n < 1) {
    while (new_block != (code_node *)0x0) {
      node = new_block->next;
      pool_free(new_block,0x178);
      new_block = node;
    }
    return (code_node *)0x0;
  }
  labno_ptr = &new_block->labno;
  new_labno = make_new_label_number();
  *labno_ptr = (short)new_labno;
#if SHC_REBUILD_UPDATED
  pep_xj_label_mark((short)new_labno);
#endif
  if ((short)new_labno == 0) {
    report_fatal_message(0,0,0xbc8);
  }
  label_sym = create_symbol_record('\x02',' ',*labno_ptr);
  label_sym->header_word = g_current_section->id;
  new_block->psd[0].op = OP_LABEL;
  *(short *)&new_block->psd[0].ea1 = *labno_ptr;
  new_block->psd[0].tmp = -1;
  new_block->psd[0].sptravel = g_cur_sptravel;
  label_sym->label_psd = new_block->psd;
  rec = new_block->psd + 1;
  cur_node = new_block;
  if (0 < node_count) {
    do {
      if (node_count == 1) {
LAB_00413e5c:
        slot_count = 0xe;
      }
      else if (1 < node_count) {
        if (node_index == 0) goto LAB_00413e5c;
        slot_count = 0xf;
        cur_node = cur_node->next;
        rec = cur_node->psd;
      }
      if (((byte)g_stage_flags & 0x20) != 0) {
        _printf(s_node_number___d_00427830,(int)node_count);
        _printf(s_code_counter___d_0042781c,(int)slot_count);
      }
      n = 0;
      src = common_a;
      if (0 < slot_count) {
        do {
          common_a = src;
          if (src == (psd *)0x0) break;
          op = src->op;
          if (((op == OP_JUMP) || (op == OP_RETURN)) && (src->ea1->labels != (label_ref *)0x0)) {
            if (mode == 2) {
              common_a = (psd *)0x0;
              copy_psd_record(src,rec);
              break;
            }
          }
          else {
            if ((op != OP_SWBGN) && (op != OP_SWEND)) {
              copy_psd_record(src,rec);
            }
            op = rec->op;
            if (((op == OP_CALL) || (op == OP_MOVI)) || ((op == OP_MOVA_PC || (op == OP_MOVA_FC))))
            {
              release_label_refs_of_record(rec,0);
            }
            delete_psd_record(src);
            delete_psd_record(common_b);
          }
          n = n + 1;
          rec = rec + 1;
          common_a = find_next_psd_record(block_a,src);
          common_b = find_next_psd_record(block_b,common_b);
          src = common_a;
        } while (n < slot_count);
      }
      node_index = node_index + 1;
    } while (node_index < node_count);
  }
  if (mode == 1) {
    rec = find_block_final_record(block_a);
    release_label_refs_of_record(rec,1);
    rec->ea1->labels->labno1 = *labno_ptr;
    if (rec->op == OP_RETURN) {
      rec->op = OP_JUMP;
    }
    block_a->target_labno = *labno_ptr;
    increment_label_ref_count(*labno_ptr);
  }
  if (mode == 2) {
    new_block->target_labno = block_a->target_labno;
    rec = find_block_final_record(block_a);
    release_label_refs_of_record(rec,1);
    delete_psd_record(rec);
    block_a->target_labno = 0;
    rec = find_block_final_record(block_b);
    rec->ea1->labels->labno1 = *labno_ptr;
    if (rec->op == OP_RETURN) {
      rec->op = OP_JUMP;
    }
    new_block->target_labno = block_b->target_labno;
    block_b->target_labno = *labno_ptr;
    increment_label_ref_count(*labno_ptr);
  }
  return new_block;
}



