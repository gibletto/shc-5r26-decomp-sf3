#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_pipeline_opcode_name_table
#define g_pipeline_opcode_name_table (*(unsigned char * *)(g_sd + 0x5d88))


// entry: 00416c6e
// name : dump_pipeline_table
// size : 396
// sig  : void dump_pipeline_table(void)


int __cdecl dump_pipeline_table(void)

{
  int first_edge;
  int i;
  int edge_ix;
  
  for (i = 0; i <= g_pipeline_window_last_index; i = i + 1) {
    _printf(s_tbl__d___s__refreg__08x__08x__se_004418c8,i,
            (&g_pipeline_opcode_name_table)[g_pipeline_window[i].rec.op],
            g_pipeline_window[i].refreg[0],g_pipeline_window[i].refreg[1],
            g_pipeline_window[i].setreg[0],g_pipeline_window[i].setreg[1],
            (int)(short)g_pipeline_window[i].flags);
    _printf(s_flags__04x__count__d__next__d_004418f8,(uint)g_pipeline_window[i].flags,
            (int)g_pipeline_window[i].count,(int)g_pipeline_window[i].next);
    _printf(s_depend___00441928);
    first_edge = (int)g_pipeline_window[i].depend;
    if (first_edge == -1) {
      _printf(&s_NON_00441940);
      edge_ix = -1;
    }
    else {
      _printf(&s_pct_2d_00441944,(int)g_pipeline_edges[first_edge].entry);
      edge_ix = (int)g_pipeline_edges[first_edge].next;
    }
    for (; edge_ix != -1; edge_ix = (int)g_pipeline_edges[edge_ix].next) {
      _printf(s____2d_00441948,(int)g_pipeline_edges[edge_ix].entry);
    }
    _printf(&s_nl_00441950);
  }
  return;
}
