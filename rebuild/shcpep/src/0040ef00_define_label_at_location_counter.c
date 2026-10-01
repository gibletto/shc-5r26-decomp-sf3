#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_symbol
#define g_current_symbol (*(symbol * *)(g_sd + 0x6d4c))


// entry: 0040ef00
// name : define_label_at_location_counter
// size : 175
// sig  : void define_label_at_location_counter(psd * rec)


int __cdecl define_label_at_location_counter(psd *rec)

{
  short sym_number;
  
  g_current_symbol = g_symbol_hash[*(short *)&rec->ea1 % 0x3fd];
  sym_number = g_current_symbol->number;
  while (sym_number != *(short *)&rec->ea1) {
    g_current_symbol = g_current_symbol->hash_next;
    sym_number = g_current_symbol->number;
  }
  g_current_symbol->value = g_location_counter;
  switch(g_current_symbol->type & 0x1f) {
  case 0:
  case 7:
  case 8:
  case 9:
  case 10:
  case 0xb:
  case 0xc:
  case 0xd:
  case 0xe:
    break;
  case 1:
  case 2:
  case 3:
  case 4:
    write_asb_symbol_record();
    break;
  case 5:
    write_asb_symbol_record();
    write_asb_symbol_name();
    break;
  case 6:
    write_asb_tag6_record();
    break;
  default:
    report_fatal_message(0,0,0x1266);
  }
  g_current_symbol->type = '\0';
  g_current_symbol->label_psd = (psd *)0x0;
  return;
}



