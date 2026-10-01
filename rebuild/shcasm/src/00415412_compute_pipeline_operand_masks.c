#include "decls.h"
#include "imports.h"

// entry: 00415412
// name : compute_pipeline_operand_masks
// size : 722
// sig  : void compute_pipeline_operand_masks(void)


int __cdecl compute_pipeline_operand_masks(void)

{
  unsigned char _frec_30[48];
#define set_mask0 (*(uint *)(_frec_30 + 0))
#define set_mask1 (*(uint *)(_frec_30 + 4))
#define i (*(short *)(_frec_30 + 12))
#define ref_mask0 (*(uint *)(_frec_30 + 16))
#define ref_mask1 (*(uint *)(_frec_30 + 20))
#define memory_ref (*(short *)(_frec_30 + 28))
#define last_index (*(int *)(_frec_30 + 36))
#define cur_entry (*(pipeline_entry * *)(_frec_30 + 40))
  ushort op_code;
  
  last_index = g_pipeline_window_last_index;
  i = 0;
  do {
    if (last_index < i) {
      return;
    }
    memory_ref = 0;
    set_mask1 = 0;
    set_mask0 = 0;
    ref_mask1 = 0;
    ref_mask0 = 0;
    cur_entry = g_pipeline_window + i;
    op_code = (ushort)(cur_entry->rec).op;
    if ((&g_pipeline_op_read_operands)[(short)op_code] == '\x01') {
LAB_0041554f:
      accumulate_operand_register_mask(&ref_mask0,(cur_entry->rec).ea1);
      if (((((((cur_entry->rec).ea1)->type & 0x1f) != 1) &&
           ((((cur_entry->rec).ea1)->type & 0x1f) != 5)) &&
          ((((cur_entry->rec).ea1)->type & 0x1f) != 6)) &&
         ((((((cur_entry->rec).ea1)->type & 0x1f) != 0xf &&
           ((((cur_entry->rec).ea1)->type & 0x1f) != 0x10)) &&
          (((((cur_entry->rec).ea1)->type & 0x1f) != 7 && (op_code != 0x44)))))) {
        memory_ref = 1;
        if (((((cur_entry->rec).ea1)->type & 0x1f) == 3) ||
           ((((cur_entry->rec).ea1)->type & 0x1f) == 4)) {
          set_mask0 = set_mask0 | ref_mask0;
          set_mask1 = set_mask1 | ref_mask1;
        }
        if ((((cur_entry->rec).ea1)->type & 0x1f) == 10) {
          memory_ref = 0;
        }
      }
    }
    else if ((&g_pipeline_op_read_operands)[(short)op_code] == '\x02') {
      accumulate_operand_register_mask(&ref_mask0,g_pipeline_window[i].rec.ea2);
      if ((((((((cur_entry->rec).ea2)->type & 0x1f) != 1) &&
            ((((cur_entry->rec).ea2)->type & 0x1f) != 5)) &&
           ((((cur_entry->rec).ea2)->type & 0x1f) != 6)) &&
          (((((cur_entry->rec).ea2)->type & 0x1f) != 0xf &&
           ((((cur_entry->rec).ea2)->type & 0x1f) != 0x10)))) &&
         (((((cur_entry->rec).ea2)->type & 0x1f) != 7 &&
          ((memory_ref = 1, (((cur_entry->rec).ea2)->type & 0x1f) == 3 ||
           ((((cur_entry->rec).ea2)->type & 0x1f) == 4)))))) {
        set_mask0 = ref_mask0;
        set_mask1 = ref_mask1;
      }
      goto LAB_0041554f;
    }
    if (op_code == 0xcc) {
      ref_mask0 = ref_mask0 | g_register_bit_masks[0x10];
    }
    g_pipeline_window[i].refreg[0] = g_pipeline_window[i].refreg[0] | ref_mask0;
    g_pipeline_window[i].refreg[1] = g_pipeline_window[i].refreg[1] | ref_mask1;
    g_pipeline_window[i].setreg[0] = g_pipeline_window[i].setreg[0] | set_mask0;
    g_pipeline_window[i].setreg[1] = g_pipeline_window[i].setreg[1] | set_mask1;
    if (memory_ref != 0) {
      g_pipeline_window[i].flags = g_pipeline_window[i].flags | 0x8000;
    }
    i = i + 1;
  } while( true );
#undef set_mask0
#undef set_mask1
#undef i
#undef ref_mask0
#undef ref_mask1
#undef memory_ref
#undef last_index
#undef cur_entry
}
