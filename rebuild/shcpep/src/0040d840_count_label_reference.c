#include "decls.h"
#include "imports.h"

// entry: 0040d840
// name : count_label_reference
// size : 91
// sig  : void count_label_reference(int labno)


int __cdecl count_label_reference(int labno)

{
  symbol *sym;
  short sym_number;
  
  if ((labno < 0) && (labno != -0x8000)) {
    labno = -labno;
  }
  if (0xb6 < labno) {
    sym = g_symbol_hash[labno % 0x3fd];
    sym_number = sym->number;
    while (sym_number != (short)labno) {
      sym = sym->hash_next;
      if (sym == (symbol *)0x0) {
        report_fatal_message(0,0,0x1267);
      }
      sym_number = sym->number;
    }
    sym->ref_count = sym->ref_count + 1;
    sym->flags = sym->flags | 0x20;
  }
  return;
}



