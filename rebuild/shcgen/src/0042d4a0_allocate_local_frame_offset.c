#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_symbol_table
#define g_symbol_table (*(sym_entry * *)(g_sd + 0x1f9b0))


// entry: 0042d4a0
// name : allocate_local_frame_offset
// size : 283
// sig  : int allocate_local_frame_offset(int sym_index, int frame_offset)


int __cdecl allocate_local_frame_offset(int sym_index,int frame_offset)

{
  int sym;
  byte type_class;
  uint uVar1;
  uint sign;
  int var_size;
  int align;
  
  sym = (sym_index ^ sym_index >> 0x1f) - (sym_index >> 0x1f);
  switch(g_symbol_table[sym].type & 0xfc) {
  case 0:
  case 4:
    var_size = 1;
    align = 1;
    break;
  case 8:
  case 0xc:
    align = 2;
    var_size = 2;
    break;
  case 0x10:
  case 0x14:
  case 0x18:
  case 0x1c:
  case 0x28:
  case 0x40:
    align = 4;
    var_size = 4;
    break;
  default:
    var_size = align;
    break;
  case 0x30:
  case 0x38:
    var_size = 8;
    align = 4;
    break;
  case 0x60:
  case 0x80:
    var_size = g_symbol_table[sym].size;
    align = 1;
    break;
  case 0x68:
  case 0x88:
    var_size = g_symbol_table[sym].size;
    align = 2;
    break;
  case 0x70:
  case 0x90:
    var_size = g_symbol_table[sym].size;
    align = 4;
  }
  if (align != 1) {
    uVar1 = frame_offset >> 0x1f;
    if (align == 2) {
      if (((frame_offset ^ uVar1) - uVar1 & 1 ^ uVar1) != uVar1) {
        frame_offset = frame_offset & 0xfffffffe;
      }
    }
    else if (((frame_offset ^ uVar1) - uVar1 & 3 ^ uVar1) != uVar1) {
      frame_offset = frame_offset & 0xfffffffc;
    }
  }
  uVar1 = frame_offset - var_size;
  type_class = g_symbol_table[sym].type & 0xe0;
  if (((type_class == 0x60) || (type_class == 0x80)) &&
     (sign = (int)uVar1 >> 0x1f, ((uVar1 ^ sign) - sign & 3 ^ sign) != sign)) {
    uVar1 = uVar1 & 0xfffffffc;
  }
  if (-1 < (int)uVar1) {
    report_codegen_message(0xc84,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
  }
  return uVar1;
}



