#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_aux_record_table
#define g_aux_record_table (*(aux_record * *)(g_sd + 0x10c74))
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))


// entry: 00421388
// name : relax_exit_record
// size : 877
// sig  : void __cdecl relax_exit_record(layout_record *item,int pass)


int __cdecl relax_exit_record(layout_record *item,int pass)

{
  unsigned char _frec_54[84];
#define movi_item (*(layout_record *)(_frec_54 + 0))
#define sp_total (*(int *)(_frec_54 + 32))
#define aux_ix (*(short *)(_frec_54 + 36))
#define size_probe (*(psd *)(_frec_54 + 48))
#define new_size (*(char *)(_frec_54 + 72))
#define func_label (*(short *)(_frec_54 + 76))
  char total_size;
  short sVar1;
  symbol *func_sym;
  
  new_size = '\0';
  if (pass == 0) {
    item->location = item->location - g_layout_shrink_pass0;
    func_label = g_function_label_pass0;
  }
  else {
    item->location = item->location - g_layout_shrink_pass1;
    func_label = g_function_label_pass1;
  }
  func_sym = find_symbol_by_id(func_label);
  aux_ix = func_sym->aux_index;
  sp_total = g_aux_record_table[aux_ix].sp_adjust + g_aux_record_table[aux_ix].frame_size;
  if (sp_total != 0) {
    if (sp_total < 0x80) {
      new_size = new_size + '\x02';
    }
    else {
      movi_item.op = OP_MOVI;
      if (pass == 0) {
        size_probe.op = OP_MOVI;
        size_probe.flg = '\x02';
        size_probe.misc = '\0';
        sVar1 = compute_record_code_size(&size_probe);
        item->part_size[0] = (char)sVar1;
      }
      movi_item.size = item->part_size[0];
      movi_item.flg = '\x02';
      movi_item.value = sp_total;
      movi_item.labels = (label_ref *)0x0;
      relax_movi_record(&movi_item,pass);
      item->size = item->size - (item->part_size[0] - movi_item.size);
      item->part_size[0] = movi_item.size;
      new_size = movi_item.size + new_size + '\x02';
    }
  }
  if (((int)(short)g_aux_record_table[aux_ix].flags & 0x8000U) == 0) {
    new_size = new_size + '\x02';
  }
  sVar1 = count_saved_registers(aux_ix);
  new_size = new_size + (char)sVar1 * '\x02';
  if (((g_aux_record_table[aux_ix].flags & 0x4000) != 0) &&
     ((g_aux_record_table[aux_ix].flags & 0x1800) != 0)) {
    new_size = new_size + '\x04';
  }
  if (((g_aux_record_table[aux_ix].flags & 0x4000) == 0) ||
     ((g_aux_record_table[aux_ix].flags & 0x2000) == 0)) {
    total_size = new_size + '\x04';
    if (((g_current_request->optimize != 0) && ((g_aux_record_table[aux_ix].flags & 0x4000) == 0))
       && (((g_aux_record_table[aux_ix].saved_regs != 0 ||
            (g_aux_record_table[aux_ix].saved_regs2 != 0)) ||
           ((((int)(short)g_aux_record_table[aux_ix].flags & 0x8000U) != 0 &&
            (((sp_total != 0 || ((g_aux_record_table[aux_ix].saved_sys & 3) != 0)) ||
             ((g_aux_record_table[aux_ix].saved_mac & 3) != 0)))))))) {
      total_size = new_size + '\x02';
    }
  }
  else {
    total_size = new_size + '\x02';
  }
  new_size = total_size;
  if (pass == 0) {
    g_layout_shrink_pass0 = g_layout_shrink_pass0 + ((int)item->size - (int)new_size);
  }
  else {
    g_layout_shrink_pass1 = g_layout_shrink_pass1 + ((int)item->size - (int)new_size);
  }
  item->size = new_size;
  layout_literal_pool(item,pass);
  return;
#undef movi_item
#undef sp_total
#undef aux_ix
#undef size_probe
#undef new_size
#undef func_label
}
