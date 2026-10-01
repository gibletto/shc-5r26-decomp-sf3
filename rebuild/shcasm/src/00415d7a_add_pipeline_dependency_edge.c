#include "decls.h"
#include "imports.h"

// entry: 00415d7a
// name : add_pipeline_dependency_edge
// size : 355
// sig  : void __cdecl add_pipeline_dependency_edge(short from,short to)


int __cdecl add_pipeline_dependency_edge(short from,short to)

{
  short edge_ix;
  bool already_linked;
  
  if ((-1 < from) && (g_pipeline_edge_count < 0x3e0)) {
    already_linked = false;
    for (edge_ix = g_pipeline_window[from].depend; edge_ix != -1;
        edge_ix = g_pipeline_edges[edge_ix].next) {
      if (g_pipeline_edges[edge_ix].entry == to) {
        already_linked = true;
        break;
      }
    }
    if (!already_linked) {
      if (g_pipeline_window[from].depend == -1) {
        g_pipeline_window[from].depend = (short)g_pipeline_edge_count;
      }
      else {
        edge_ix = g_pipeline_window[from].depend;
        while (g_pipeline_edges[edge_ix].next != -1) {
          edge_ix = g_pipeline_edges[edge_ix].next;
        }
        g_pipeline_edges[edge_ix].next = (short)g_pipeline_edge_count;
      }
      g_pipeline_edges[g_pipeline_edge_count].entry = to;
      g_pipeline_edges[g_pipeline_edge_count].next = -1;
      g_pipeline_window[to].count = g_pipeline_window[to].count + 1;
      g_pipeline_edge_count = g_pipeline_edge_count + 1;
    }
  }
  return;
}
