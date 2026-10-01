#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))
#undef g_layout_section_pass1
#define g_layout_section_pass1 (*(request_section * *)(g_sd + 0xcca4))
#undef g_layout_symbol_pass0
#define g_layout_symbol_pass0 (*(symbol * *)(g_sd + 0xccf8))
#undef g_ofb_input
#define g_ofb_input (*(FILE * *)(g_sd + 0xd12c))


// entry: 00420a51
// name : relax_switch_jump_record
// size : 2184
// sig  : void __cdecl relax_switch_jump_record(layout_record *item,int pass)


int __cdecl relax_switch_jump_record(layout_record *item,int pass)

{
  unsigned char _frec_7c[124];
#define part_item (*(layout_record *)(_frec_7c + 0))
#define label_sym (*(symbol * *)(_frec_7c + 32))
#define target_sym (*(symbol * *)(_frec_7c + 36))
#define align_pad (*(int *)(_frec_7c + 40))
#define label_hi (*(char *)(_frec_7c + 44))
#define label_lo (*(char *)(_frec_7c + 45))
#define part_offset (*(int *)(_frec_7c + 48))
#define target_label (*(short (*)[2])(_frec_7c + 52))
#define short_entries (*(short *)(_frec_7c + 56))
#define base_label (*(ushort (*)[2])(_frec_7c + 64))
#define table_item (*(layout_record * *)(_frec_7c + 68))
#define table_label (*(ushort (*)[2])(_frec_7c + 72))
#define target_dist (*(int *)(_frec_7c + 76))
#define size_probe (*(psd *)(_frec_7c + 80))
#define pool_bytes (*(int *)(_frec_7c + 104))
#define new_size (*(char *)(_frec_7c + 108))
#define tag_buf (*(char (*)[4])(_frec_7c + 112))
#define jump_ref (*(label_ref * *)(_frec_7c + 116))
  short sVar1;
  uint uVar2;
  int iVar3;
  symbol *pool_sym;
  symbol *pool_sym2;
  uint sign_mask;
  
  base_label[0] = 0;
  part_offset = item->location;
  if (pass == 0) {
    if ((item->value < -0x7f) || (0x80 < item->value)) {
      size_probe.op = OP_MOVI;
      size_probe.flg = '\x02';
      size_probe.misc = '\0';
      sVar1 = compute_record_code_size(&size_probe);
      item->part_size[2] = (char)sVar1;
      item->part_size[0] = item->part_size[2];
    }
    size_probe.op = OP_JUMPT;
    size_probe.flg = '\0';
    sVar1 = compute_record_code_size(&size_probe);
    item->part_size[3] = (char)sVar1;
  }
  new_size = '\0';
  if (pass == 0) {
    item->location = item->location - g_layout_shrink_pass0;
  }
  else {
    item->location = item->location - g_layout_shrink_pass1;
  }
  if (item->value != 0) {
    if ((item->value < -0x7f) || (0x80 < item->value)) {
      part_item.op = OP_MOVI;
      part_item.size = item->part_size[0];
      part_offset = part_offset + item->part_size[0];
      part_item.flg = '\x02';
      part_item.value = item->value;
      part_item.labels = (label_ref *)0x0;
      relax_movi_record(&part_item,pass);
      item->size = item->size - (item->part_size[0] - part_item.size);
      new_size = part_item.size + new_size;
      item->part_size[0] = part_item.size;
    }
    new_size = new_size + '\x02';
    part_offset = part_offset + 2;
  }
  part_item.op = OP_MOVI;
  part_item.size = item->part_size[2];
  part_offset = part_offset + item->part_size[2];
  part_item.flg = '\x02';
  part_item.value = (int)item->labels;
  part_item.labels = (label_ref *)0x0;
  relax_movi_record(&part_item,pass);
  item->size = item->size - (item->part_size[2] - part_item.size);
  item->part_size[2] = part_item.size;
  new_size = part_item.size + new_size + '\x02';
  part_item.location = part_offset + 2;
  part_item.op = OP_JUMPT;
  part_item.size = item->part_size[3];
  part_item.misc = '\0';
  if (pass == 1) {
    part_item.part_size[0] = item->flg;
  }
  part_offset = part_item.location + item->part_size[3];
  part_item.value = 0;
  part_item.labels = pool_alloc(8);
  (part_item.labels)->labno1 = item->label;
  (part_item.labels)->labno2 = 0;
  jump_ref = part_item.labels;
  relax_conditional_jump_record(&part_item,pass);
  item->flg = part_item.part_size[0];
  item->size = item->size - (item->part_size[3] - part_item.size);
  new_size = part_item.size + new_size;
  item->part_size[3] = part_item.size;
  pool_free(jump_ref,8);
  if (pass == 0) {
    uVar2 = read_file_bytes(g_ofb_input,tag_buf,1);
    if (uVar2 == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    table_item = read_ofb_layout_record(tag_buf[0]);
    table_item->labels = (label_ref *)0x0;
  }
  else {
    table_item = item->next;
  }
  iVar3 = find_request_entry12_value(g_current_request,(int)item->pool_size,(int *)target_label);
  if (iVar3 == 0) {
    report_message_at_source_line(0,0,0x1375,(char *)0x0);
  }
  target_sym = find_symbol_by_id(target_label[0]);
  if (g_current_request->cpu == 0) {
    target_dist = target_sym->value - table_item->location;
  }
  else {
    target_dist = target_sym->value - (item->location + part_offset + 0xc);
  }
  if (pass == 0) {
    target_dist = target_dist - g_layout_shrink_pass0;
  }
  else if ((uint)g_layout_symbol_pass0->sequence < (uint)target_sym->sequence) {
    target_dist = target_dist - (g_layout_shrink_pass1 + g_layout_shrink_pass0);
  }
  else {
    target_dist = target_dist - g_layout_shrink_pass1;
  }
  if (target_dist < 0x8000) {
    if (pass == 1) {
      record_size_decision_byte('\x01');
    }
    short_entries = 1;
  }
  else {
    if (pass == 1) {
      record_size_decision_byte('\0');
    }
    short_entries = 0;
  }
  if (g_current_request->cpu == 0) {
    if (short_entries == 0) {
      new_size = new_size + '\x06';
    }
    else {
      new_size = new_size + '\b';
    }
    new_size = new_size + '\x04';
  }
  else {
    new_size = new_size + '\f';
  }
  if (pass == 1) {
    if (g_current_request->cpu != 0) {
      if (g_last_label_number == 0x7fff) {
        report_message_at_source_line(0,0,0xbc8,(char *)0x0);
      }
      g_last_label_number = g_last_label_number + 1;
      base_label[0] = g_last_label_number;
      label_sym = create_symbol_entry('\x02','\0',g_last_label_number);
      label_sym->value = (int)new_size + item->location;
      label_sym->section_id = g_layout_section_pass1->id;
      store_u16_big_endian(base_label,(ushort *)&label_hi);
      record_size_decision_byte(label_hi);
      record_size_decision_byte(label_lo);
    }
    if (g_last_label_number == 0x7fff) {
      report_message_at_source_line(0,0,0xbc8,(char *)0x0);
    }
    g_last_label_number = g_last_label_number + 1;
    table_label[0] = g_last_label_number;
    label_sym = create_symbol_entry('\x02','\0',g_last_label_number);
    label_sym->section_id = g_layout_section_pass1->id;
    store_u16_big_endian(table_label,(ushort *)&label_hi);
    record_size_decision_byte(label_hi);
    record_size_decision_byte(label_lo);
  }
  if (pass == 0) {
    if (g_current_request->cpu == 0) {
      pool_bytes = g_word_literal_table.count * 2 + g_long_literal_table.count * 4 + 6;
    }
    else {
      pool_bytes = g_long_literal_table.count * 4 + g_word_literal_table.count * 2 + 2;
    }
  }
  else {
    if (((g_current_request->cpu == 0) && (g_word_literal_table_pass1.count == 0)) &&
       (g_long_literal_table_pass1.count == 0)) {
      if (g_last_label_number == 0x7fff) {
        report_message_at_source_line(0,0,0xbc8,(char *)0x0);
      }
      g_last_label_number = g_last_label_number + 1;
      g_literal_pool_label = g_last_label_number;
      pool_sym = create_symbol_entry('\x0f','\0',g_last_label_number);
      pool_sym->section_id = g_layout_section_pass1->id;
      store_u16_big_endian((ushort *)&g_literal_pool_label,(ushort *)&label_hi);
      record_size_decision_byte(label_hi);
      record_size_decision_byte(label_lo);
    }
    uVar2 = (int)new_size + g_word_literal_table_pass1.count * 2 + item->location;
    sign_mask = (int)uVar2 >> 0x1f;
    if (((uVar2 ^ sign_mask) - sign_mask & 3 ^ sign_mask) == sign_mask) {
      align_pad = 0;
    }
    else {
      align_pad = 2;
    }
    if (g_current_request->cpu == 0) {
      pool_bytes = g_word_literal_table_pass1.count * 2 + 4 + g_long_literal_table_pass1.count * 4;
    }
    else {
      pool_bytes = g_long_literal_table_pass1.count * 4 + g_word_literal_table_pass1.count * 2;
    }
    pool_bytes = pool_bytes + align_pad;
    if (((g_current_request->cpu == 0) || (g_word_literal_table_pass1.count != 0)) ||
       (g_long_literal_table_pass1.count != 0)) {
      pool_sym = find_symbol_by_id(g_literal_pool_label);
      pool_sym->value = (int)new_size + item->location;
      pool_sym = find_symbol_by_id(g_literal_pool_label);
      pool_sym2 = find_symbol_by_id(g_literal_pool_label);
      pool_sym->layout_records =
           (layout_record *)(pool_sym2->value + g_word_literal_table_pass1.count * 2 + align_pad);
    }
  }
  if (pass == 0) {
    clear_pool_literal_table(&g_word_literal_table);
    clear_pool_literal_table(&g_long_literal_table);
    g_layout_shrink_pass0 =
         g_layout_shrink_pass0 + (((int)item->size - (int)new_size) - pool_bytes) + 0x402;
  }
  else {
    clear_pool_literal_table(&g_word_literal_table_pass1);
    clear_pool_literal_table(&g_long_literal_table_pass1);
    g_layout_shrink_pass1 =
         g_layout_shrink_pass1 +
         (((int)item->size - (int)new_size) - pool_bytes) + item->pool_before_table;
  }
  item->size = new_size;
  item->pool_before_table = pool_bytes;
  resize_case_table_record(table_item,pass,(int)short_entries);
  if (pass == 1) {
    label_sym->value = table_item->location;
  }
  return;
#undef part_item
#undef label_sym
#undef target_sym
#undef align_pad
#undef label_hi
#undef label_lo
#undef part_offset
#undef target_label
#undef short_entries
#undef base_label
#undef table_item
#undef table_label
#undef target_dist
#undef size_probe
#undef pool_bytes
#undef new_size
#undef tag_buf
#undef jump_ref
}
