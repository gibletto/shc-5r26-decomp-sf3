#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_aux_record_table
#define g_aux_record_table (*(aux_record * *)(g_sd + 0x10c74))
#undef g_current_aux_index
#define g_current_aux_index (*(int *)(g_sd + 0xf8ec))


// entry: 0042ee05
// name : frame_offset_to_sp_displacement
// size : 142
// sig  : int frame_offset_to_sp_displacement(int frame_offset, int sp_travel)


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl frame_offset_to_sp_displacement(int frame_offset,int sp_travel)

{
  short saved_count;
  int save_area_bytes;
  int frame_bytes;
  
  frame_bytes = g_aux_record_table[_g_current_aux_index].frame_size;
  if (frame_offset < 0) {
    save_area_bytes = 0;
    frame_offset = frame_offset + 4;
  }
  else {
    saved_count = count_saved_registers(g_current_aux_index);
    save_area_bytes = saved_count * 4;
    if (((int)(short)g_aux_record_table[_g_current_aux_index].flags & 0x8000U) == 0) {
      save_area_bytes = save_area_bytes + 4;
    }
  }
  return save_area_bytes + frame_bytes + sp_travel + frame_offset;
}



