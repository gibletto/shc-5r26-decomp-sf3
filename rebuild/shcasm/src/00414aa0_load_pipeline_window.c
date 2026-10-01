#include "decls.h"
#include "imports.h"

// entry: 00414aa0
// name : load_pipeline_window
// size : 1279
// sig  : pipeline_entry * load_pipeline_window(void)


pipeline_entry * load_pipeline_window(void)

{
  unsigned char _frec_28[40];
#define n_entries (*(short *)(_frec_28 + 0))
#define read_rec (*(psd * *)(_frec_28 + 4))
#define last_entry (*(pipeline_entry * *)(_frec_28 + 8))
#define cur_rec (*(psd *)(_frec_28 + 12))
  int got_lookahead;
  
  n_entries = 0;
  last_entry = (pipeline_entry *)0x0;
  stock_memcpy(&cur_rec,&g_zero_psd,0x18);
  reset_pipeline_state();
  if (g_pipeline_lookahead_valid == 1) {
    stock_memcpy(&cur_rec,&g_pipeline_lookahead_record,0x18);
    read_rec = &cur_rec;
    stock_memcpy(&g_pipeline_lookahead_record,&g_zero_psd,0x18);
    g_pipeline_lookahead_valid = 0;
  }
  else {
    read_rec = (psd *)read_next_backend_record(&cur_rec,1);
  }
  while ((((read_rec != (psd *)0x0 && (OP_BEND < cur_rec.op)) && (cur_rec.op < OP_DUMMY_1C)) &&
         (n_entries < 0x20))) {
    stock_memcpy(g_pipeline_window + n_entries,&cur_rec,0x18);
    stock_memcpy(&cur_rec,&g_zero_psd,0x18);
    last_entry = g_pipeline_window + n_entries;
    n_entries = n_entries + 1;
    read_rec = (psd *)read_next_backend_record(&cur_rec,1);
  }
  while ((((((read_rec != (psd *)0x0 && (cur_rec.op != OP_BRA)) &&
            ((cur_rec.op != OP_BT && ((cur_rec.op != OP_BF && (cur_rec.op != OP_JMP)))))) &&
           (cur_rec.op != OP_BSR)) &&
          ((((cur_rec.op != OP_BT_S && (cur_rec.op != OP_BF_S)) && (cur_rec.op != OP_BSRF)) &&
           ((cur_rec.op != OP_BRAF && (cur_rec.op != OP_JSR)))))) &&
         ((((cur_rec.op != OP_RTS && ((cur_rec.op != OP_RTE && (cur_rec.op != OP_TRAPA)))) &&
           (cur_rec.op != OP_C_JMP)) &&
          ((cur_rec.op != OP_B_ASM &&
           (((cur_rec.op < OP_LABEL || (OP_FLABEL < cur_rec.op)) && (n_entries < 0x20))))))))) {
    stock_memcpy(g_pipeline_window + n_entries,&cur_rec,0x18);
    stock_memcpy(&cur_rec,&g_zero_psd,0x18);
    last_entry = g_pipeline_window + n_entries;
    n_entries = n_entries + 1;
    read_rec = (psd *)read_next_backend_record(&cur_rec,1);
  }
  if (((read_rec == (psd *)0x0) ||
      (((((cur_rec.op != OP_BRA && (cur_rec.op != OP_BT)) &&
         ((cur_rec.op != OP_BF && ((cur_rec.op != OP_JMP && (cur_rec.op != OP_BSR)))))) &&
        ((cur_rec.op != OP_BT_S &&
         ((((cur_rec.op != OP_BF_S && (cur_rec.op != OP_BSRF)) && (cur_rec.op != OP_BRAF)) &&
          ((cur_rec.op != OP_B_ASM && (cur_rec.op != OP_JSR)))))))) &&
       ((cur_rec.op != OP_RTS && ((cur_rec.op != OP_RTE && (cur_rec.op != OP_TRAPA)))))))) ||
     (0x1f < n_entries)) {
    if ((n_entries < 0x20) && (cur_rec.op == OP_C_JMP)) {
      stock_memcpy(g_pipeline_window + n_entries,&cur_rec,0x18);
      stock_memcpy(&cur_rec,&g_zero_psd,0x18);
      last_entry = g_pipeline_window + n_entries;
      n_entries = n_entries + 1;
      g_pipeline_window_ended_at_c_jmp = 1;
    }
    else if (read_rec != (psd *)0x0) {
      stock_memcpy(&g_pipeline_lookahead_record,&cur_rec,0x18);
      g_pipeline_lookahead_valid = 1;
    }
  }
  else {
    stock_memcpy(g_pipeline_window + n_entries,&cur_rec,0x18);
    stock_memcpy(&cur_rec,&g_zero_psd,0x18);
    last_entry = g_pipeline_window + n_entries;
    n_entries = n_entries + 1;
    got_lookahead = read_next_backend_record(&g_pipeline_lookahead_record,1);
    if (got_lookahead == 0) {
      stock_memcpy(&g_pipeline_lookahead_record,&g_zero_psd,0x18);
    }
    else {
      g_pipeline_lookahead_valid = 1;
    }
  }
  if (n_entries == 0) {
    last_entry = (pipeline_entry *)0x0;
  }
  else {
    g_pipeline_window_last_index = n_entries + -1;
    compute_pipeline_operand_masks();
    compute_pipeline_opcode_masks_and_flags();
  }
  return last_entry;
#undef n_entries
#undef read_rec
#undef last_entry
#undef cur_rec
}



