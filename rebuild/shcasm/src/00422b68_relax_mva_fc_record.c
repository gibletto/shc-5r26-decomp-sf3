#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_layout_section_pass1
#define g_layout_section_pass1 (*(request_section * *)(g_sd + 0xcca4))


// entry: 00422b68
// name : relax_mva_fc_record
// size : 461
// sig  : void __cdecl relax_mva_fc_record(layout_record *item,int pass)


int __cdecl relax_mva_fc_record(layout_record *item,int pass)

{
  unsigned char _frec_18[24];
#define labno_byte_hi (*(char *)(_frec_18 + 0))
#define labno_byte_lo (*(char *)(_frec_18 + 1))
#define new_labno (*(ushort (*)[2])(_frec_18 + 4))
#define new_label_sym (*(symbol * *)(_frec_18 + 8))
#define new_size (*(char *)(_frec_18 + 12))
#define lit_ref (*(label_ref * *)(_frec_18 + 16))
  
  new_size = '\0';
  if (pass == 0) {
    item->location = item->location - g_layout_shrink_pass0;
  }
  else {
    item->location = item->location - g_layout_shrink_pass1;
  }
  if (pass == 1) {
    if (g_last_label_number == 0x7fff) {
      report_message_at_source_line(0,0,0xbc8,(char *)0x0);
    }
    g_last_label_number = g_last_label_number + 1;
    new_labno[0] = g_last_label_number;
    new_label_sym = create_symbol_entry('\x02','\0',g_last_label_number);
    new_label_sym->section_id = g_layout_section_pass1->id;
    store_u16_big_endian(new_labno,(ushort *)&labno_byte_hi);
    record_size_decision_byte(labno_byte_hi);
    record_size_decision_byte(labno_byte_lo);
  }
  else {
    new_labno[0] = g_literal_label_serial;
    g_literal_label_serial = g_literal_label_serial + 1;
  }
  new_size = new_size + '\x06';
  if ((pass == 1) && (new_label_sym != (symbol *)0x0)) {
    if (((int)new_size + item->location & 3U) == 0) {
      record_size_decision_byte('\x01');
    }
    else {
      record_size_decision_byte('\0');
    }
    new_label_sym->value = (int)new_size + item->location & 0xfffffffc;
  }
  lit_ref = pool_alloc(8);
  lit_ref->labno1 = item->labels->labno1;
  lit_ref->labno2 = -new_labno[0];
  add_literal_to_pool_table(0,lit_ref,pass,1);
  pool_free(lit_ref,8);
  if (pass == 0) {
    g_layout_shrink_pass0 = g_layout_shrink_pass0 + ((int)item->size - (int)new_size);
  }
  else {
    g_layout_shrink_pass1 = g_layout_shrink_pass1 + ((int)item->size - (int)new_size);
  }
  item->size = new_size;
  return;
#undef labno_byte_hi
#undef labno_byte_lo
#undef new_labno
#undef new_label_sym
#undef new_size
#undef lit_ref
}
