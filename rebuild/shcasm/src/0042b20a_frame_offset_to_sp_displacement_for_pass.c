#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_aux_record_table
#define g_aux_record_table (*(aux_record * *)(g_sd + 0x10c74))


// entry: 0042b20a
// name : frame_offset_to_sp_displacement_for_pass
// size : 218
// sig  : int frame_offset_to_sp_displacement_for_pass(int frame_offset, int sp_travel, int pass)


int __cdecl frame_offset_to_sp_displacement_for_pass(int frame_offset,int sp_travel,int pass)

{
  short aux_index;
  short saved_count;
  symbol *func_sym;
  int save_area_bytes;
  short func_labno;
  int func_frame_size;
  
  if (pass == 2) {
    func_labno = g_function_label;
  }
  else if (pass == 0) {
    func_labno = g_function_label_pass0;
  }
  else {
    func_labno = g_function_label_pass1;
  }
  func_sym = find_symbol_by_id(func_labno);
  aux_index = func_sym->aux_index;
  func_frame_size = g_aux_record_table[aux_index].frame_size;
  if (frame_offset < 0) {
    save_area_bytes = 0;
    frame_offset = frame_offset + 4;
  }
  else {
    saved_count = count_saved_registers(aux_index);
    save_area_bytes = saved_count * 4;
    if (((int)(short)g_aux_record_table[aux_index].flags & 0x8000U) == 0) {
      save_area_bytes = save_area_bytes + 4;
    }
  }
  return save_area_bytes + func_frame_size + sp_travel + frame_offset;
}



