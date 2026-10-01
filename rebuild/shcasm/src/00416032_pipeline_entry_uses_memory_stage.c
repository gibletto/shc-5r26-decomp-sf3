#include "decls.h"
#include "imports.h"

// entry: 00416032
// name : pipeline_entry_uses_memory_stage
// size : 462
// sig  : int pipeline_entry_uses_memory_stage(int index)


int __cdecl pipeline_entry_uses_memory_stage(int index)

{
  int uses_memory;
  
  uses_memory = 0;
  if (((g_pipeline_window[index].rec.op == OP_MUL) || (g_pipeline_window[index].rec.op == OP_MULS))
     || (g_pipeline_window[index].rec.op == OP_MULU)) {
    uses_memory = 1;
  }
  if ((((g_pipeline_window[index].rec.ea1 != (ea *)0x0) &&
       (((g_pipeline_window[index].rec.ea1)->type & 0x1f) != 1)) &&
      ((((g_pipeline_window[index].rec.ea1)->type & 0x1f) != 5 &&
       ((((g_pipeline_window[index].rec.ea1)->type & 0x1f) != 6 &&
        (((g_pipeline_window[index].rec.ea1)->type & 0x1f) != 0xf)))))) &&
     ((((g_pipeline_window[index].rec.ea1)->type & 0x1f) != 0x10 &&
      (((g_pipeline_window[index].rec.ea1)->type & 0x1f) != 7)))) {
    uses_memory = 1;
  }
  if (((((g_pipeline_window[index].rec.ea2 != (ea *)0x0) &&
        (((g_pipeline_window[index].rec.ea2)->type & 0x1f) != 1)) &&
       (((g_pipeline_window[index].rec.ea2)->type & 0x1f) != 5)) &&
      ((((g_pipeline_window[index].rec.ea2)->type & 0x1f) != 6 &&
       (((g_pipeline_window[index].rec.ea2)->type & 0x1f) != 0xf)))) &&
     ((((g_pipeline_window[index].rec.ea2)->type & 0x1f) != 0x10 &&
      (((g_pipeline_window[index].rec.ea2)->type & 0x1f) != 7)))) {
    uses_memory = 1;
  }
  return uses_memory;
}



