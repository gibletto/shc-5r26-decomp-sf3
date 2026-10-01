#include "decls.h"
#include "imports.h"

// entry: 00404c54
// name : drain_next_superscalar_scheduled_record
// size : 146
// sig  : psd * drain_next_superscalar_scheduled_record(psd * rec)


psd * __cdecl drain_next_superscalar_scheduled_record(psd *rec)

{
  g_superscalar_draining = 1;
  sort_array(g_superscalar_window,g_pipeline_window_last_index + 1,0xe0,
             compare_superscalar_entries_by_issue_order);
  stock_memcpy(rec,g_superscalar_window + g_superscalar_drain_index,0x18);
  g_superscalar_drain_index = g_superscalar_drain_index + 1;
  if (g_superscalar_drain_count == g_superscalar_drain_index) {
    g_superscalar_draining = 0;
    g_superscalar_drain_index = 0;
  }
  return rec;
}



