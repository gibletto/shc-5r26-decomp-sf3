#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_aux_record_table
#define g_aux_record_table (*(aux_record * *)(g_sd + 0x6d50))


// entry: 0041b1e0
// name : frame_offset_to_sp_displacement
// size : 104
// sig  : int frame_offset_to_sp_displacement(int frame_offset, int sp_travel)


int __cdecl frame_offset_to_sp_displacement(int frame_offset,int sp_travel)

{
  short save_area;
  int iVar1;
  int frame_size;
  
  frame_size = g_aux_record_table[g_current_aux_index].frame_size;
  if (frame_offset < 0) {
    iVar1 = 0;
    frame_offset = frame_offset + 4;
  }
  else {
    save_area = count_saved_registers((short)g_current_aux_index);
    iVar1 = save_area * 4;
    if ((g_aux_record_table[g_current_aux_index].flags & 0x8000) == 0) {
      iVar1 = iVar1 + 4;
    }
  }
  return iVar1 + frame_size + sp_travel + frame_offset;
}



