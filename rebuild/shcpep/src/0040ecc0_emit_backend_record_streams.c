#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_node_list
#define g_current_node_list (*(code_node * *)(g_sd + 0x6d70))
#undef g_current_section
#define g_current_section (*(request_section * *)(g_sd + 0x5d0c))
#undef g_lit_output
#define g_lit_output (*(FILE * *)(g_sd + 0x6df8))
#undef g_ofb_output
#define g_ofb_output (*(FILE * *)(g_sd + 0x5cf8))
#undef g_stage_flags
#define g_stage_flags (*(unsigned char *)(g_sd + 0x6d64))
#undef g_sub_output
#define g_sub_output (*(FILE * *)(g_sd + 0x5bfc))


// entry: 0040ecc0
// name : emit_backend_record_streams
// size : 562
// sig  : void emit_backend_record_streams(void)


int __cdecl emit_backend_record_streams(void)

{
  unsigned char _frec_18[24];
#define line_rec (*(psd *)(_frec_18 + 0))
  code_node *pcVar1;
  code_node *node;
  short sVar2;
  uint uVar3;
  int iVar4;
  psd *rec;
  int i;
  undefined4 *src;
  psd *dst;
  psd_op op;
  ea *opnd;
  bool pool_after_transfer;
  undefined4 word_val;
  
  if (((*(unsigned char *)((char *)&g_stage_flags + 1)) & 0x20) != 0) {
    dump_node_list_debug(g_current_node_list);
  }
  pool_after_transfer = false;
  g_location_counter = g_current_section->unknown_08;
  node = g_current_node_list;
  do {
    pcVar1 = node;
    if (node == (code_node *)0x0) {
      g_current_section->unknown_08 = g_location_counter;
      return;
    }
    for (; pcVar1 != (code_node *)0x0; pcVar1 = pcVar1->next) {
      i = 0;
      rec = pcVar1->psd;
      do {
        if ((rec->op != OP_DUMMY) &&
           ((((rec->op != OP_ADD || (opnd = rec->ea1, (opnd->type & 0x1f) != 7)) ||
             (opnd->labels != (label_ref *)0x0)) || (opnd->disp != 0)))) {
          delete_unreachable_record(rec);
          iVar4 = g_cur_sptravel;
          if (rec->op != OP_DUMMY) {
            track_stack_pointer_travel(node,rec);
            uVar3 = decide_literal_pool_placement(rec,g_lit_output);
            sVar2 = (short)uVar3;
            if (sVar2 != 0) {
              op = rec->op;
              if ((((op == OP_BRA) || (op == OP_JMP)) ||
                  ((op == OP_RTS || ((op == OP_RTE || (op == OP_RETURN)))))) ||
                 ((op == OP_EXIT || (((op == OP_JUMP || (op == OP_BRAF)) || (op == OP_CASEJMP))))))
              {
                pool_after_transfer = true;
              }
              else {
                emit_branch_around_literal_pool(rec,sVar2,iVar4);
              }
            }
            write_ofb_record(g_ofb_output,rec,g_location_counter,(int)sVar2);
            if (rec->op == OP_FLABEL) {
              src = &g_empty_psd;
              dst = &line_rec;
              for (iVar4 = 6; iVar4 != 0; iVar4 = iVar4 + -1) {
                word_val = *src;
                dst->op = (char)word_val;
                dst->flg = (char)((uint)word_val >> 8);
                dst->misc = (char)((uint)word_val >> 0x10);
                dst->tmp = (char)((uint)word_val >> 0x18);
                src = src + 1;
                dst = (psd *)&dst->sptravel;
              }
              line_rec.op = OP_LINE;
              line_rec.filno = rec->filno;
              line_rec.linno = rec->linno;
              write_sub_record(g_sub_output,&line_rec);
            }
            write_sub_record(g_sub_output,rec);
            op = rec->op;
            if (((op == OP_LABEL) || (op == OP_CLABEL)) || ((op == OP_DLABEL || (op == OP_FLABEL))))
            {
              define_label_at_location_counter(rec);
            }
            if (pool_after_transfer) {
              pool_after_transfer = false;
              g_location_counter = g_location_counter + sVar2;
            }
            sVar2 = compute_record_code_size(rec);
            g_location_counter = g_location_counter + sVar2;
          }
          op = rec->op;
          if (((((OP_CALL < op) && (op < OP_MOV_LOC)) || ((op == OP_EXIT || (op == OP_RETURN)))) ||
              (((((OP_SETT < op && (op < OP_BSR)) || (op == OP_JMP)) ||
                ((OP_JSR < op && (op < OP_BSRF)))) || (op == OP_BRAF)))) || (op == OP_RTE)) break;
        }
        i = i + 1;
        rec = rec + 1;
      } while (i < 0xf);
    }
    pcVar1 = node->next_block;
    free_node_list(node);
    node = pcVar1;
  } while( true );
#undef line_rec
}



