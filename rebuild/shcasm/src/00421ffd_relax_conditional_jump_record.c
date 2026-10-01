#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_layout_section_pass1
#define g_layout_section_pass1 (*(request_section * *)(g_sd + 0xcca4))


// entry: 00421ffd
// name : relax_conditional_jump_record
// size : 704
// sig  : void __cdecl relax_conditional_jump_record(layout_record *item,int pass)


int __cdecl relax_conditional_jump_record(layout_record *item,int pass)

{
  unsigned char _frec_54[84];
#define jump_item (*(layout_record *)(_frec_54 + 0))
#define orig_location (*(int *)(_frec_54 + 32))
#define labno_byte_hi (*(char *)(_frec_54 + 36))
#define labno_byte_lo (*(char *)(_frec_54 + 37))
#define new_labno (*(ushort (*)[2])(_frec_54 + 40))
#define displacement (*(int *)(_frec_54 + 44))
#define new_label_sym (*(symbol * *)(_frec_54 + 48))
#define jump_rec (*(psd *)(_frec_54 + 52))
#define new_size (*(char *)(_frec_54 + 76))
  short code_size;
  
  orig_location = item->location;
  new_size = '\0';
  if (pass == 0) {
    item->location = item->location - g_layout_shrink_pass0;
  }
  else {
    item->location = item->location - g_layout_shrink_pass1;
  }
  displacement = compute_branch_displacement(item,pass);
  if ((displacement < -0x100) || (0xfe < displacement)) {
    if ((item->misc & 0x80) == 0) {
      if (pass == 1) {
        record_size_decision_byte('\x01');
      }
      new_size = new_size + '\x02';
    }
    else {
      if (pass == 1) {
        record_size_decision_byte('\x03');
      }
      new_size = new_size + '\x04';
    }
    new_label_sym = (symbol *)0x0;
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
    jump_item.op = OP_JUMP;
    if (pass == 0) {
      jump_rec.op = OP_JUMP;
      jump_rec.flg = '\x02';
      code_size = compute_record_code_size(&jump_rec);
      item->part_size[0] = (char)code_size;
    }
    jump_item.size = item->part_size[0];
    jump_item.misc = '\x02';
    jump_item.location =
         (-(uint)(((int)(char)item->misc & 0x80U) == 0) & 0xfffffffe) + 4 + orig_location;
    jump_item.value = item->value;
    jump_item.labels = item->labels;
    jump_item.pool_size = 0;
    relax_jump_record(&jump_item,pass);
    item->size = item->size - (item->part_size[0] - jump_item.size);
    new_size = jump_item.size + new_size;
    item->part_size[0] = jump_item.size;
    if ((pass == 1) && (new_label_sym != (symbol *)0x0)) {
      new_label_sym->value = (int)new_size + item->location;
    }
  }
  else if ((item->misc & 0x80) == 0) {
    if (pass == 1) {
      record_size_decision_byte('\0');
    }
    new_size = new_size + '\x02';
  }
  else {
    if (pass == 1) {
      record_size_decision_byte('\x02');
    }
    new_size = new_size + '\x04';
  }
  if (pass == 0) {
    g_layout_shrink_pass0 = g_layout_shrink_pass0 + ((int)item->size - (int)new_size);
  }
  else {
    g_layout_shrink_pass1 = g_layout_shrink_pass1 + ((int)item->size - (int)new_size);
  }
  item->size = new_size;
  return;
#undef jump_item
#undef orig_location
#undef labno_byte_hi
#undef labno_byte_lo
#undef new_labno
#undef displacement
#undef new_label_sym
#undef jump_rec
#undef new_size
}
