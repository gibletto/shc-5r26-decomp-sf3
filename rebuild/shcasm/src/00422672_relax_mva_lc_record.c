#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))


// entry: 00422672
// name : relax_mva_lc_record
// size : 336
// sig  : void __cdecl relax_mva_lc_record(layout_record *item,int pass)


int __cdecl relax_mva_lc_record(layout_record *item,int pass)

{
  uint value;
  char new_size;
  
  value = frame_offset_to_sp_displacement_for_pass(item->value,(int)item->labels,pass);
  if (((int)value < 0x80) && (-0x81 < (int)value)) {
    if (value == 0) {
      new_size = '\x02';
      if ((((g_current_request->flags_13d & 4) != 0) && ((item->flg & 0x40) == 0)) &&
         ((item->flg & 0x10) != 0)) {
        new_size = '\x04';
      }
    }
    else {
      new_size = '\x04';
    }
  }
  else {
    new_size = '\x04';
    if (((int)value < -0x8000) || (0x7fff < (int)value)) {
      add_literal_to_pool_table(value,(label_ref *)0x0,pass,1);
    }
    else {
      add_literal_to_pool_table(value,(label_ref *)0x0,pass,0);
    }
  }
  if ((item->flg & 0x40) != 0) {
    new_size = new_size + -2;
  }
  if (pass == 0) {
    g_layout_shrink_pass0 = g_layout_shrink_pass0 + ((int)item->size - (int)new_size);
  }
  else {
    g_layout_shrink_pass1 = g_layout_shrink_pass1 + ((int)item->size - (int)new_size);
  }
  item->size = new_size;
  return;
}
