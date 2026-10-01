#include "decls.h"
#include "imports.h"

// entry: 00416574
// name : release_pipeline_entry_successors
// size : 217
// sig  : void __cdecl release_pipeline_entry_successors(short index)


int __cdecl release_pipeline_entry_successors(short index)

{
  short edge_ix;
  short succ;
  
  if (g_pipeline_window[index].depend != -1) {
    for (edge_ix = g_pipeline_window[index].depend; edge_ix != -1;
        edge_ix = g_pipeline_edges[edge_ix].next) {
      succ = g_pipeline_edges[edge_ix].entry;
      g_pipeline_window[succ].count = g_pipeline_window[succ].count + -1;
      if (g_pipeline_window[succ].count < 0) {
        report_message_at_source_line
                  (g_pipeline_window[succ].rec.filno,(uint)g_pipeline_window[succ].rec.linno,0x1342,
                   (char *)0x0);
      }
    }
  }
  return;
}
