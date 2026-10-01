#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_section
#define g_current_section (*(request_section * *)(g_sd + 0x5d0c))
#undef g_lit_output
#define g_lit_output (*(FILE * *)(g_sd + 0x6df8))
#undef g_ofb_output
#define g_ofb_output (*(FILE * *)(g_sd + 0x5cf8))
#undef g_sub_output
#define g_sub_output (*(FILE * *)(g_sd + 0x5bfc))
#undef g_switch_scan_block
#define g_switch_scan_block (*(code_node * *)(g_sd + 0x5c04))


// entry: 0040ea50
// name : flush_block_to_output
// size : 609
// sig  : void flush_block_to_output(code_node * block)


int __cdecl flush_block_to_output(code_node *block)

{
  unsigned char _frec_18[24];
#define line_rec (*(psd *)(_frec_18 + 0))
  short sVar1;
  int iVar2;
  uint uVar3;
  int *marker_pair;
  psd *rec;
  int i;
  undefined4 *src;
  psd *dst;
  psd_op op;
  ea *opnd;
  bool pool_after_transfer;
  undefined4 word_val;
  
  g_block_flushed_early = 1;
  g_location_counter = g_current_section->unknown_08;
  pool_after_transfer = false;
  do {
    if (block == (code_node *)0x0) {
      g_current_section->unknown_08 = g_location_counter;
      return;
    }
    if (g_switch_scan_block == (code_node *)0x0) {
      g_switch_scan_single_block = 1;
      delete_switch_markers_from_cursor();
      g_switch_scan_single_block = 0;
      g_switch_scan_block = (code_node *)0x0;
    }
    i = 0;
    rec = block->psd;
    do {
      op = rec->op;
      if ((op != OP_DUMMY) &&
         ((((op != OP_ADD || (opnd = rec->ea1, opnd->labels != (label_ref *)0x0)) ||
           ((opnd->type & 0x1f) != 7)) || (opnd->disp != 0)))) {
        if (((op == OP_SWBGN) || (op == OP_SWEND)) && (iVar2 = 0, 0 < g_switch_marker_depth)) {
          marker_pair = &g_switch_marker_pairs;
          do {
            if ((psd *)*marker_pair == rec) {
              (&g_switch_marker_pairs)[iVar2 * 2] = 0;
              break;
            }
            if ((psd *)marker_pair[1] == rec) {
              (&g_switch_brackets_end)[iVar2 * 2] = 0;
              break;
            }
            marker_pair = marker_pair + 2;
            iVar2 = iVar2 + 1;
          } while (iVar2 < g_switch_marker_depth);
        }
        delete_unreachable_record(rec);
        iVar2 = g_cur_sptravel;
        if (rec->op != OP_DUMMY) {
          track_stack_pointer_travel(block,rec);
          uVar3 = decide_literal_pool_placement(rec,g_lit_output);
          sVar1 = (short)uVar3;
          if (sVar1 != 0) {
            op = rec->op;
            if ((((op == OP_BRA) || (op == OP_JMP)) ||
                (((op == OP_RTS || (((op == OP_RTE || (op == OP_RETURN)) || (op == OP_EXIT)))) ||
                 ((op == OP_JUMP || (op == OP_BRAF)))))) || (op == OP_CASEJMP)) {
              pool_after_transfer = true;
            }
            else {
              emit_branch_around_literal_pool(rec,sVar1,iVar2);
            }
          }
          write_ofb_record(g_ofb_output,rec,g_location_counter,(int)sVar1);
          if (rec->op == OP_FLABEL) {
            src = &g_empty_psd;
            dst = &line_rec;
            for (iVar2 = 6; iVar2 != 0; iVar2 = iVar2 + -1) {
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
          if (((op == OP_LABEL) || (op == OP_CLABEL)) || ((op == OP_DLABEL || (op == OP_FLABEL)))) {
            define_label_at_location_counter(rec);
          }
          if (pool_after_transfer) {
            pool_after_transfer = false;
            g_location_counter = g_location_counter + sVar1;
          }
          sVar1 = compute_record_code_size(rec);
          g_location_counter = g_location_counter + sVar1;
        }
        op = rec->op;
        if (((((((OP_CALL < op) && (op < OP_MOV_LOC)) || (op == OP_EXIT)) ||
              ((op == OP_RETURN || ((OP_SETT < op && (op < OP_BSR)))))) || (op == OP_JMP)) ||
            ((OP_JSR < op && (op < OP_BSRF)))) || ((op == OP_BRAF || (op == OP_RTE)))) break;
      }
      i = i + 1;
      rec = rec + 1;
    } while (i < 0xf);
    block = block->next;
  } while( true );
#undef line_rec
}



