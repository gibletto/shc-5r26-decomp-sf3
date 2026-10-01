#include "decls.h"
#include "imports.h"

// entry: 00414f9f
// name : compute_pipeline_opcode_masks_and_flags
// size : 1134
// sig  : void compute_pipeline_opcode_masks_and_flags(void)


int __cdecl compute_pipeline_opcode_masks_and_flags(void)

{
  unsigned char _frec_38[56];
#define set_mask0 (*(uint *)(_frec_38 + 0))
#define set_mask1 (*(uint *)(_frec_38 + 4))
#define op_code (*(ushort *)(_frec_38 + 8))
#define i (*(short *)(_frec_38 + 12))
#define ref_mask0 (*(uint *)(_frec_38 + 16))
#define ref_mask1 (*(uint *)(_frec_38 + 20))
#define memory_ref (*(short *)(_frec_38 + 28))
#define writes_memory (*(short *)(_frec_38 + 32))
#define last_index (*(int *)(_frec_38 + 44))
#define cur_entry (*(pipeline_entry * *)(_frec_38 + 48))
  int ix;
  
  last_index = g_pipeline_window_last_index;
  for (i = 0; i <= last_index; i = i + 1) {
    writes_memory = 0;
    memory_ref = 0;
    set_mask1 = 0;
    set_mask0 = 0;
    ref_mask1 = 0;
    ref_mask0 = 0;
    ix = (int)i;
    cur_entry = g_pipeline_window + ix;
    op_code = (ushort)(cur_entry->rec).op;
    if ((&g_pipeline_op_written_operand)[(short)op_code] == '\x01') {
      if ((((((g_pipeline_window[ix].rec.ea1)->type & 0x1f) == 1) ||
           (((g_pipeline_window[ix].rec.ea1)->type & 0x1f) == 5)) ||
          (((g_pipeline_window[ix].rec.ea1)->type & 0x1f) == 6)) ||
         (((((g_pipeline_window[ix].rec.ea1)->type & 0x1f) == 0xf ||
           (((g_pipeline_window[ix].rec.ea1)->type & 0x1f) == 0x10)) ||
          (((g_pipeline_window[ix].rec.ea1)->type & 0x1f) == 7)))) {
        accumulate_operand_register_mask(&set_mask0,g_pipeline_window[ix].rec.ea1);
      }
      else {
        writes_memory = 1;
        accumulate_operand_register_mask(&ref_mask0,g_pipeline_window[ix].rec.ea1);
        if (((((cur_entry->rec).ea1)->type & 0x1f) == 3) ||
           ((((cur_entry->rec).ea1)->type & 0x1f) == 4)) {
          set_mask0 = set_mask0 | ref_mask0;
          set_mask1 = set_mask1 | ref_mask1;
        }
      }
    }
    else if ((&g_pipeline_op_written_operand)[(short)op_code] == '\x02') {
      if (((((((g_pipeline_window[ix].rec.ea2)->type & 0x1f) == 1) ||
            (((g_pipeline_window[ix].rec.ea2)->type & 0x1f) == 5)) ||
           (((g_pipeline_window[ix].rec.ea2)->type & 0x1f) == 6)) ||
          ((((g_pipeline_window[ix].rec.ea2)->type & 0x1f) == 0xf ||
           (((g_pipeline_window[ix].rec.ea2)->type & 0x1f) == 0x10)))) ||
         (((g_pipeline_window[ix].rec.ea2)->type & 0x1f) == 7)) {
        accumulate_operand_register_mask(&set_mask0,g_pipeline_window[ix].rec.ea2);
      }
      else {
        writes_memory = 1;
        accumulate_operand_register_mask(&ref_mask0,g_pipeline_window[ix].rec.ea2);
        if (((((cur_entry->rec).ea2)->type & 0x1f) == 3) ||
           ((((cur_entry->rec).ea2)->type & 0x1f) == 4)) {
          set_mask0 = set_mask0 | ref_mask0;
          set_mask1 = set_mask1 | ref_mask1;
        }
      }
    }
    if ((((op_code == 0x6f) || (op_code == 0x70)) || (op_code == 0x71)) ||
       ((op_code == 0x72 || (op_code == 0x9b)))) {
      set_mask1 = set_mask1 | g_register_bit_masks[4] | g_register_bit_masks[3];
    }
    if ((((op_code == 0x9f) || (op_code == 0x86)) ||
        ((op_code == 0xa0 ||
         (((op_code == 0x11 || (op_code == 0x10)) || (((cur_entry->rec).flg & 0x80) != 0)))))) ||
       ((op_code == 0x8c &&
        ((((cur_entry->rec).ea2)->base == REG_SR || (((cur_entry->rec).ea2)->base == REG_VBR)))))) {
      set_mask1 = 0xffffffff;
      set_mask0 = 0xffffffff;
      writes_memory = 1;
    }
    if (((&g_pipeline_op_t_bit_use)[(short)op_code] & 1) != 0) {
      set_mask1 = set_mask1 | g_register_bit_masks[0];
    }
    if (((&g_pipeline_op_t_bit_use)[(short)op_code] & 2) != 0) {
      ref_mask1 = ref_mask1 | g_register_bit_masks[0];
    }
    if (((&g_pipeline_op_fpu_flags)[(short)op_code] & 1) != 0) {
      set_mask1 = set_mask1 | g_register_bit_masks[6];
    }
    g_pipeline_window[i].refreg[0] = g_pipeline_window[i].refreg[0] | ref_mask0;
    g_pipeline_window[i].refreg[1] = g_pipeline_window[i].refreg[1] | ref_mask1;
    g_pipeline_window[i].setreg[0] = g_pipeline_window[i].setreg[0] | set_mask0;
    g_pipeline_window[i].setreg[1] = g_pipeline_window[i].setreg[1] | set_mask1;
    if ((set_mask0 & g_register_bit_masks[0xf]) != 0) {
      g_pipeline_window[i].flags = g_pipeline_window[i].flags | 0x4000;
    }
    if (memory_ref != 0) {
      g_pipeline_window[i].flags = g_pipeline_window[i].flags | 0x8000;
    }
    if (writes_memory != 0) {
      g_pipeline_window[i].flags = g_pipeline_window[i].flags | 0x4000;
    }
  }
  return;
#undef set_mask0
#undef set_mask1
#undef op_code
#undef i
#undef ref_mask0
#undef ref_mask1
#undef memory_ref
#undef writes_memory
#undef last_index
#undef cur_entry
}
