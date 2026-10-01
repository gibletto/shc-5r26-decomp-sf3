#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_section
#define g_current_section (*(request_section * *)(g_sd + 0x1f9b8))
#undef g_symbol_table
#define g_symbol_table (*(sym_entry * *)(g_sd + 0x1f9b0))


// entry: 00408ce0
// name : align_sud_location_counter
// size : 1000
// sig  : void align_sud_location_counter(void)


int __cdecl align_sud_location_counter(void)

{
  unsigned char _frec_8[8];
#define pad_header (*(char (*)[4])(_frec_8 + 0))
#define pad_repeat (*(char (*)[4])(_frec_8 + 4))
  ushort type_class;
  uint uVar1;
  uint *loc;
  uint old_loc;
  byte sym_attr;
  byte sym_type;
  
  pad_header[0] = '\n';
  uVar1 = (uint)g_sud_symx;
  sym_type = g_symbol_table[(uVar1 ^ (int)uVar1 >> 0x1f) - ((int)uVar1 >> 0x1f)].type;
  sym_attr = g_symbol_table[uVar1].attr;
  if (((((sym_attr & 1) == 0) && ((sym_attr & 2) == 0)) && (((short)(char)sym_type & 1U) != 0)) &&
     ((sym_type & 2) == 0)) {
    loc = &g_current_section->const_loc;
  }
  else {
    loc = &g_current_section->data_loc;
  }
  type_class = (short)(char)sym_type & 0xfc;
  old_loc = *loc;
  if (((type_class == 0) || (type_class == 4)) || ((type_class == 0x60 || (type_class == 0x80)))) {
    if ((sym_attr & 0x40) == 0) {
      if (g_symbol_table[uVar1].sclass != '\t') {
        return;
      }
      goto LAB_00408d6a;
    }
LAB_00408d72:
    switch(*loc & 7) {
    case 1:
      pad_repeat[0] = '\x01';
      pad_repeat[1] = '\0';
      pad_repeat[2] = '\0';
      pad_repeat[3] = '\0';
      pad_header[1] = 0;
      append_sud_bytes(pad_header,2,'\0');
      append_sud_bytes(pad_repeat,4,'\0');
      pad_header[1] = 1;
      pad_repeat[0] = '\x01';
      pad_repeat[1] = '\0';
      pad_repeat[2] = '\0';
      pad_repeat[3] = '\0';
      append_sud_bytes(pad_header,2,'\0');
      append_sud_bytes(pad_repeat,4,'\0');
      pad_repeat[0] = '\x01';
      pad_repeat[1] = '\0';
      pad_repeat[2] = '\0';
      pad_repeat[3] = '\0';
      pad_header[1] = 2;
      append_sud_bytes(pad_header,2,'\0');
      append_sud_bytes(pad_repeat,4,'\0');
      *loc = *loc + 7;
      break;
    case 2:
      pad_header[1] = 1;
      pad_repeat[0] = '\x01';
      pad_repeat[1] = '\0';
      pad_repeat[2] = '\0';
      pad_repeat[3] = '\0';
      append_sud_bytes(pad_header,2,'\0');
      append_sud_bytes(pad_repeat,4,'\0');
      pad_repeat[0] = '\x01';
      pad_repeat[1] = '\0';
      pad_repeat[2] = '\0';
      pad_repeat[3] = '\0';
      pad_header[1] = 2;
      append_sud_bytes(pad_header,2,'\0');
      append_sud_bytes(pad_repeat,4,'\0');
      *loc = *loc + 6;
      break;
    case 3:
      pad_repeat[0] = '\x01';
      pad_repeat[1] = '\0';
      pad_repeat[2] = '\0';
      pad_repeat[3] = '\0';
      pad_header[1] = 0;
      append_sud_bytes(pad_header,2,'\0');
      append_sud_bytes(pad_repeat,4,'\0');
      pad_repeat[0] = '\x01';
      pad_repeat[1] = '\0';
      pad_repeat[2] = '\0';
      pad_repeat[3] = '\0';
      pad_header[1] = 2;
      append_sud_bytes(pad_header,2,'\0');
      append_sud_bytes(pad_repeat,4,'\0');
      *loc = *loc + 5;
      break;
    case 4:
      pad_header[1] = 2;
      pad_repeat[0] = '\x01';
      pad_repeat[1] = '\0';
      pad_repeat[2] = '\0';
      pad_repeat[3] = '\0';
      append_sud_bytes(pad_header,2,'\0');
      append_sud_bytes(pad_repeat,4,'\0');
      *loc = *loc + 4;
      break;
    case 5:
      pad_repeat[0] = '\x01';
      pad_repeat[1] = '\0';
      pad_repeat[2] = '\0';
      pad_repeat[3] = '\0';
      pad_header[1] = 0;
      append_sud_bytes(pad_header,2,'\0');
      append_sud_bytes(pad_repeat,4,'\0');
      pad_header[1] = 1;
      pad_repeat[0] = '\x01';
      pad_repeat[1] = '\0';
      pad_repeat[2] = '\0';
      pad_repeat[3] = '\0';
      append_sud_bytes(pad_header,2,'\0');
      append_sud_bytes(pad_repeat,4,'\0');
      *loc = *loc + 3;
      break;
    case 6:
      pad_header[1] = 1;
      pad_repeat[0] = '\x01';
      pad_repeat[1] = '\0';
      pad_repeat[2] = '\0';
      pad_repeat[3] = '\0';
      append_sud_bytes(pad_header,2,'\0');
      append_sud_bytes(pad_repeat,4,'\0');
      *loc = *loc + 2;
      break;
    case 7:
      goto LAB_00409084;
    }
  }
  else {
LAB_00408d6a:
    if ((sym_attr & 0x40) != 0) goto LAB_00408d72;
    if (((type_class != 8) && (type_class != 0xc)) && ((type_class != 0x68 && (type_class != 0x88)))
       ) {
      uVar1 = *loc & 3;
      if (uVar1 == 1) {
        pad_header[1] = 0;
        pad_repeat[0] = '\x01';
        pad_repeat[1] = '\0';
        pad_repeat[2] = '\0';
        pad_repeat[3] = '\0';
        append_sud_bytes(pad_header,2,'\0');
        append_sud_bytes(pad_repeat,4,'\0');
        *loc = *loc + 1;
      }
      else if (uVar1 != 2) {
        if (uVar1 != 3) goto switchD_00408d81_default;
        goto LAB_00409084;
      }
      pad_header[1] = 1;
      pad_repeat[0] = '\x01';
      pad_repeat[1] = '\0';
      pad_repeat[2] = '\0';
      pad_repeat[3] = '\0';
      append_sud_bytes(pad_header,2,'\0');
      append_sud_bytes(pad_repeat,4,'\0');
      *loc = *loc + 2;
      goto switchD_00408d81_default;
    }
    if ((*loc & 1) == 0) goto switchD_00408d81_default;
LAB_00409084:
    pad_repeat[0] = '\x01';
    pad_repeat[1] = '\0';
    pad_repeat[2] = '\0';
    pad_repeat[3] = '\0';
    pad_header[1] = 0;
    append_sud_bytes(pad_header,2,'\0');
    append_sud_bytes(pad_repeat,4,'\0');
    *loc = *loc + 1;
  }
switchD_00408d81_default:
  if (*loc < old_loc) {
    report_codegen_message(0xc81,1,0,0,(char *)0x0);
  }
  return;
#undef pad_header
#undef pad_repeat
}



