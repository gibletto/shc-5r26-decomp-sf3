#include "decls.h"
#include "imports.h"

// entry: 00415a50
// name : build_pipeline_dependency_graph
// size : 810
// sig  : void build_pipeline_dependency_graph(void)


int __cdecl build_pipeline_dependency_graph(void)

{
  unsigned char _frec_18[24];
#define to_ix (*(short *)(_frec_18 + 0))
#define used_regs (*(uint (*)[2])(_frec_18 + 4))
#define reg_no (*(short *)(_frec_18 + 12))
#define from_ix (*(short *)(_frec_18 + 16))
  uint uVar1;
  
  g_pipeline_edge_count = 0;
  for (to_ix = (short)g_pipeline_window_last_index; -1 < to_ix; to_ix = to_ix + -1) {
    used_regs[0] = g_pipeline_window[to_ix].setreg[0] | g_pipeline_window[to_ix].refreg[0];
    used_regs[1] = g_pipeline_window[to_ix].setreg[1] | g_pipeline_window[to_ix].refreg[1];
    for (reg_no = 0; reg_no < 0x2a; reg_no = reg_no + 1) {
      uVar1 = (int)reg_no >> 0x1f;
      if ((g_register_bit_masks[(((int)reg_no ^ uVar1) - uVar1 & 0x1f ^ uVar1) - uVar1] &
          used_regs[(int)((int)reg_no + ((int)reg_no >> 0x1f & 0x1fU)) >> 5]) != 0) {
        from_ix = to_ix + -1;
        while ((-1 < from_ix &&
               (uVar1 = (int)reg_no >> 0x1f,
               (g_register_bit_masks[(((int)reg_no ^ uVar1) - uVar1 & 0x1f ^ uVar1) - uVar1] &
               *(uint *)(from_ix * 0x30 + SD(0x00448ca8) +
                        ((int)((int)reg_no + ((int)reg_no >> 0x1f & 0x1fU)) >> 5) * 4)) == 0))) {
          from_ix = from_ix + -1;
        }
        if (-1 < from_ix) {
          add_pipeline_dependency_edge(from_ix,to_ix);
        }
      }
    }
    used_regs[0] = g_pipeline_window[to_ix].setreg[0];
    used_regs[1] = g_pipeline_window[to_ix].setreg[1];
    for (reg_no = 0; reg_no < 0x2a; reg_no = reg_no + 1) {
      uVar1 = (int)reg_no >> 0x1f;
      if ((g_register_bit_masks[(((int)reg_no ^ uVar1) - uVar1 & 0x1f ^ uVar1) - uVar1] &
          used_regs[(int)((int)reg_no + ((int)reg_no >> 0x1f & 0x1fU)) >> 5]) != 0) {
        for (from_ix = to_ix + -1; -1 < from_ix; from_ix = from_ix + -1) {
          uVar1 = (int)reg_no >> 0x1f;
          if ((g_register_bit_masks[(((int)reg_no ^ uVar1) - uVar1 & 0x1f ^ uVar1) - uVar1] &
              *(uint *)(from_ix * 0x30 + SD(0x00448cb0) +
                       ((int)((int)reg_no + ((int)reg_no >> 0x1f & 0x1fU)) >> 5) * 4)) != 0) {
            add_pipeline_dependency_edge(from_ix,to_ix);
          }
        }
      }
    }
    if ((((uint)(int)(short)g_pipeline_window[to_ix].flags >> 0xf & 1) != 0) ||
       (((uint)(int)(short)g_pipeline_window[to_ix].flags >> 0xe & 1) != 0)) {
      from_ix = to_ix + -1;
      while ((-1 < from_ix && (((uint)(int)(short)g_pipeline_window[from_ix].flags >> 0xe & 1) == 0)
             )) {
        from_ix = from_ix + -1;
      }
      if (-1 < from_ix) {
        add_pipeline_dependency_edge(from_ix,to_ix);
      }
    }
    if (((uint)(int)(short)g_pipeline_window[to_ix].flags >> 0xe & 1) != 0) {
      for (from_ix = to_ix + -1; -1 < from_ix; from_ix = from_ix + -1) {
        if (((uint)(int)(short)g_pipeline_window[from_ix].flags >> 0xf & 1) != 0) {
          add_pipeline_dependency_edge(from_ix,to_ix);
        }
      }
    }
  }
  return;
#undef to_ix
#undef used_regs
#undef reg_no
#undef from_ix
}
