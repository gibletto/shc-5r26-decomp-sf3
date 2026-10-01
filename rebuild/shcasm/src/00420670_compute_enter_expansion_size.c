#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_aux_record_table
#define g_aux_record_table (*(aux_record * *)(g_sd + 0x10c74))


// entry: 00420670
// name : compute_enter_expansion_size
// size : 993
// sig  : void __cdecl compute_enter_expansion_size(layout_record *item,int pass)


int __cdecl compute_enter_expansion_size(layout_record *item,int pass)

{
  unsigned char _frec_50[80];
#define movi_item (*(layout_record *)(_frec_50 + 0))
#define aux_ix (*(short *)(_frec_50 + 32))
#define stack_ref (*(label_ref *)(_frec_50 + 36))
#define size_probe (*(psd *)(_frec_50 + 44))
#define new_size (*(char *)(_frec_50 + 68))
#define func_label (*(short *)(_frec_50 + 72))
  short sVar1;
  symbol *func_sym;
  int iVar2;
  
  new_size = '\0';
  if (pass == 0) {
    func_label = g_ofb_current_label;
  }
  else {
    func_label = g_layout_symbol_labno_pass1;
  }
  func_sym = find_symbol_by_id(func_label);
  aux_ix = func_sym->aux_index;
  if (((g_aux_record_table[aux_ix].flags & 0x4000) != 0) &&
     ((g_aux_record_table[aux_ix].flags & 0x1800) != 0)) {
    new_size = new_size + '\x02';
    if ((((byte)(g_aux_record_table[aux_ix].flags >> 8) & 0x18) == 0x10) &&
       (iVar2 = get_symbol_attribute_bits((short)g_aux_record_table[aux_ix].stack_value), iVar2 != 0
       )) {
      new_size = new_size + '\x02';
    }
    else if ((((byte)(g_aux_record_table[aux_ix].flags >> 8) & 0x18) == 0x18) &&
            (iVar2 = get_symbol_attribute_bits((short)g_aux_record_table[aux_ix].stack_value),
            iVar2 == 1)) {
      new_size = new_size + '\x04';
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
      if (((byte)(g_aux_record_table[aux_ix].flags >> 8) & 0x18) == 8) {
        movi_item.value = g_aux_record_table[aux_ix].stack_value;
        movi_item.labels = (label_ref *)0x0;
      }
      else {
        movi_item.value = 0;
        stack_ref.next = (label_ref *)0x0;
        stack_ref.labno1 = (short)g_aux_record_table[aux_ix].stack_value;
        stack_ref.labno2 = 0;
        movi_item.labels = &stack_ref;
      }
      relax_movi_record(&movi_item,pass);
      item->size = item->size - (item->part_size[0] - movi_item.size);
      new_size = movi_item.size + new_size;
      item->part_size[0] = movi_item.size;
      if (((byte)(g_aux_record_table[aux_ix].flags >> 8) & 0x18) == 0x10) {
        new_size = new_size + '\x02';
      }
    }
    new_size = new_size + '\x04';
  }
  sVar1 = count_saved_registers(aux_ix);
  new_size = new_size + (char)sVar1 * '\x02';
  if (((int)(short)g_aux_record_table[aux_ix].flags & 0x8000U) == 0) {
    new_size = new_size + '\x02';
  }
  if (g_aux_record_table[aux_ix].frame_size != 0) {
    if (g_aux_record_table[aux_ix].frame_size < 0x81) {
      new_size = new_size + '\x02';
    }
    else {
      movi_item.op = OP_MOVI;
      if (pass == 0) {
        size_probe.op = OP_MOVI;
        size_probe.flg = '\x02';
        size_probe.misc = '\0';
        sVar1 = compute_record_code_size(&size_probe);
        item->part_size[1] = (char)sVar1;
      }
      movi_item.size = item->part_size[1];
      movi_item.flg = '\x02';
      movi_item.value = -g_aux_record_table[aux_ix].frame_size;
      movi_item.labels = (label_ref *)0x0;
      relax_movi_record(&movi_item,pass);
      item->size = item->size - (item->part_size[1] - movi_item.size);
      item->part_size[1] = movi_item.size;
      new_size = movi_item.size + new_size + '\x02';
    }
  }
  if (pass == 0) {
    g_layout_shrink_pass0 = g_layout_shrink_pass0 + ((int)item->size - (int)new_size);
  }
  else {
    g_layout_shrink_pass1 = g_layout_shrink_pass1 + ((int)item->size - (int)new_size);
  }
  item->size = new_size;
  return;
#undef movi_item
#undef aux_ix
#undef stack_ref
#undef size_probe
#undef new_size
#undef func_label
}
