#include "decls.h"
#include "imports.h"

// entry: 00404870
// name : read_next_superscalar_scheduled_record
// size : 996
// sig  : psd * read_next_superscalar_scheduled_record(psd * rec)


psd * __cdecl read_next_superscalar_scheduled_record(psd *rec)

{
  int got_record;
  psd *ppVar1;
  psd *result_rec;
  bool can_add;
  
  do {
    can_add = true;
    if (g_superscalar_records_read == 0) {
      g_pipeline_window_last_index = 0;
      g_pipeline_reload_pending = 0;
      g_superscalar_drain_index = 0;
      g_superscalar_lookahead_valid = '\0';
    }
    if (g_superscalar_lookahead_valid != '\0') {
      stock_memcpy(g_superscalar_window + g_pipeline_window_last_index,
                   &g_superscalar_lookahead_record,0x18);
      g_superscalar_lookahead_valid = '\0';
LAB_00404be1:
      g_pipeline_window_last_index = 0;
      stock_memcpy(rec,&g_superscalar_lookahead_record,0x18);
      g_superscalar_drain_count = 0x20;
      return rec;
    }
    stock_memcpy(&g_superscalar_lookahead_record,&g_zero_psd,0x18);
    got_record = read_next_backend_record(&g_superscalar_lookahead_record,1);
    if (got_record == 0) {
      if (g_pipeline_window_last_index != 0) {
        g_superscalar_stream_ended = 1;
        g_superscalar_drain_count = g_pipeline_window_last_index;
        g_pipeline_reload_pending = 0;
        ppVar1 = drain_next_superscalar_scheduled_record(rec);
        g_pipeline_window_last_index = 0;
        return ppVar1;
      }
      return (psd *)0x0;
    }
    g_superscalar_records_read = g_superscalar_records_read + 1;
    if ((((((((g_superscalar_lookahead_record.op == OP_RTE) ||
             (g_superscalar_lookahead_record.op == OP_BRA)) ||
            (g_superscalar_lookahead_record.op == OP_BT_S)) ||
           ((g_superscalar_lookahead_record.op == OP_BF_S ||
            (g_superscalar_lookahead_record.op == OP_BSRF)))) ||
          ((g_superscalar_lookahead_record.op == OP_BRAF ||
           ((g_superscalar_lookahead_record.op == OP_BSR ||
            (g_superscalar_lookahead_record.op == OP_JMP)))))) ||
         ((g_superscalar_lookahead_record.op == OP_JSR ||
          (((g_superscalar_lookahead_record.op == OP_RTS ||
            (g_superscalar_lookahead_record.op == OP_TRAPA)) ||
           (g_superscalar_lookahead_record.op == OP_BT)))))) ||
        ((((g_superscalar_lookahead_record.op == OP_BF ||
           (g_superscalar_lookahead_record.op < OP_MOV)) ||
          ((g_superscalar_lookahead_record.op == OP_SLEEP ||
           ((g_superscalar_lookahead_record.op == OP_TAS ||
            (g_superscalar_lookahead_record.op == OP_PREF)))))) ||
         (((int)(char)g_superscalar_lookahead_record.flg & 0x80U) != 0)))) ||
       ((g_superscalar_lookahead_record.op == OP_LDC &&
        (((g_superscalar_lookahead_record.ea2)->base == REG_SR ||
         ((g_superscalar_lookahead_record.ea2)->base == REG_VBR)))))) {
      can_add = false;
      if (g_pipeline_window_last_index == 0) goto LAB_00404be1;
      g_superscalar_lookahead_valid = '\x01';
      g_pipeline_reload_pending = 1;
    }
    if (g_pipeline_window_last_index == 0x1f) {
      g_pipeline_reload_pending = 1;
    }
    if (!can_add) break;
    stock_memcpy(g_superscalar_window + g_pipeline_window_last_index,&g_superscalar_lookahead_record
                 ,0x18);
    record_superscalar_entry_operands(&g_superscalar_window[g_pipeline_window_last_index].rec,'\0');
    g_pipeline_window_last_index = g_pipeline_window_last_index + 1;
  } while (g_pipeline_reload_pending == 0);
  if (g_pipeline_reload_pending == 1) {
    g_pipeline_window_last_index = g_pipeline_window_last_index + -1;
    g_pipeline_reload_pending = 0;
    if (g_pipeline_window_last_index == 0) {
      g_pipeline_window_last_index = 0;
      stock_memcpy(rec,g_superscalar_window,0x18);
      g_superscalar_drain_count = 0x20;
      g_superscalar_lookahead_valid = '\x01';
      result_rec = rec;
    }
    else {
      run_superscalar_scheduler();
      g_superscalar_drain_count = g_pipeline_window_last_index + 1;
      result_rec = drain_next_superscalar_scheduled_record(rec);
      g_pipeline_window_last_index = 0;
    }
  }
  return result_rec;
}



