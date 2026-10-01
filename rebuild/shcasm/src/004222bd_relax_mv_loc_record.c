#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))


// entry: 004222bd
// name : relax_mv_loc_record
// size : 929
// sig  : void __cdecl relax_mv_loc_record(layout_record *item,int pass)


int __cdecl relax_mv_loc_record(layout_record *item,int pass)

{
  byte operand_size;
  uint value;
  int disp_class;
  char new_size;
  int form_index;
  
  value = frame_offset_to_sp_displacement_for_pass(item->value,(int)item->labels,pass);
  if ((item->misc & 0x80) == 0) {
    operand_size = item->flg & 3;
    if (operand_size == 0) {
      form_index = 0;
    }
    else if (operand_size == 1) {
      form_index = 1;
    }
    else if (operand_size == 2) {
      if ((item->misc & 8) == 0) {
        form_index = 2;
      }
      else {
        form_index = 6;
      }
    }
  }
  else {
    operand_size = item->flg & 3;
    if (operand_size == 0) {
      form_index = 3;
    }
    else if (operand_size == 1) {
      form_index = 4;
    }
    else if (operand_size == 2) {
      if ((item->misc & 8) == 0) {
        form_index = 5;
      }
      else {
        form_index = 7;
      }
    }
  }
  if ((item->misc & 0x20) == 0) {
    if (value == 0) {
      disp_class = 3;
    }
    else if (((int)value < 1) || (0x10 << (item->flg & 3) <= (int)value)) {
      if (((int)value < -0x80) || (0x7f < (int)value)) {
        disp_class = 0;
      }
      else {
        disp_class = 1;
      }
    }
    else {
      disp_class = 2;
    }
  }
  else if (value == 0) {
    disp_class = 6;
  }
  else if (((int)value < 1) || (0x10 << (item->flg & 3) <= (int)value)) {
    if (((int)value < -0x80) || (0x7f < (int)value)) {
      disp_class = 7;
    }
    else {
      disp_class = 4;
    }
  }
  else {
    disp_class = 5;
  }
  new_size = *(char *)(form_index + SD(0x00441978) + disp_class * 8);
  if (((((g_current_request->flags_13d & 4) != 0) && (disp_class == 2)) &&
      ((form_index == 3 || (form_index == 4)))) &&
     (((item->misc & 0x20) == 0 && ((item->flg & 0x40) == 0)))) {
    new_size = new_size + '\x02';
  }
  if ((disp_class == 2) && (((form_index == 0 || (form_index == 1)) && ((item->misc & 0x10) != 0))))
  {
    new_size = new_size + -2;
  }
  if (((disp_class == 5) && ((form_index == 3 || (form_index == 4)))) && ((item->misc & 0x10) != 0))
  {
    new_size = new_size + -4;
  }
  if ((disp_class == 0) || (disp_class == 7)) {
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
