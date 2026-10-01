#include "decls.h"
#include "imports.h"

// entry: 0041664d
// name : clear_pipeline_entry_and_dependencies
// size : 263
// sig  : void __cdecl clear_pipeline_entry_and_dependencies(short index)


int __cdecl clear_pipeline_entry_and_dependencies(short index)

{
  short edge_ix;
  short next_edge;
  
  edge_ix = g_pipeline_window[index].depend;
  while (edge_ix != -1) {
    g_pipeline_edges[edge_ix].entry = -1;
    next_edge = g_pipeline_edges[edge_ix].next;
    g_pipeline_edges[edge_ix].next = -1;
    edge_ix = next_edge;
  }
  g_pipeline_window[index].rec.op = OP_DUMMY_00;
  g_pipeline_window[index].setreg[0] = 0;
  g_pipeline_window[index].setreg[1] = 0;
  g_pipeline_window[index].refreg[0] = 0;
  g_pipeline_window[index].refreg[1] = 0;
  g_pipeline_window[index].flags = 0;
  g_pipeline_window[index].depend = -1;
  g_pipeline_window[index].next = -1;
  g_pipeline_window[index].count = 0;
  return;
}
