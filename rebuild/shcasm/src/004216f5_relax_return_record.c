#include "decls.h"
#include "imports.h"

// entry: 004216f5
// name : relax_return_record
// size : 456
// sig  : void __cdecl relax_return_record(layout_record *item,int pass)


int __cdecl relax_return_record(layout_record *item,int pass)

{
  unsigned char _frec_58[88];
#define tail_item (*(layout_record *)(_frec_58 + 0))
#define old_location (*(int *)(_frec_58 + 32))
#define aux_ix (*(short *)(_frec_58 + 36))
#define saved_count (*(int *)(_frec_58 + 40))
#define new_size (*(char *)(_frec_58 + 76))
#define func_label (*(short *)(_frec_58 + 80))
  short sVar1;
  symbol *func_sym;
  
  old_location = item->location;
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
  if (pass == 0) {
    item->part_size[0] = item->size;
  }
  sVar1 = count_saved_registers(aux_ix);
  saved_count = (int)sVar1;
  if (saved_count < 2) {
    tail_item.op = OP_EXIT;
    tail_item.size = item->part_size[0];
    tail_item.misc = '\x02';
    if (pass == 1) {
      tail_item.part_size[0] = item->part_size[1];
    }
    tail_item.value = 0;
    tail_item.labels = (label_ref *)0x0;
    tail_item.pool_size = 0;
    relax_exit_record(&tail_item,pass);
    item->part_size[1] = tail_item.part_size[0];
  }
  else {
    tail_item.op = OP_JUMP;
    tail_item.size = item->part_size[0];
    tail_item.misc = '\x02';
    tail_item.location = old_location;
    tail_item.value = 0;
    tail_item.labels = item->labels;
    tail_item.pool_size = 0;
    relax_jump_record(&tail_item,pass);
  }
  item->size = item->size - (item->part_size[0] - tail_item.size);
  new_size = tail_item.size + new_size;
  item->part_size[0] = tail_item.size;
  if (pass == 0) {
    g_layout_shrink_pass0 = g_layout_shrink_pass0 + ((int)item->size - (int)new_size);
  }
  else {
    g_layout_shrink_pass1 = g_layout_shrink_pass1 + ((int)item->size - (int)new_size);
  }
  item->size = new_size;
  layout_literal_pool(item,pass);
  return;
#undef tail_item
#undef old_location
#undef aux_ix
#undef saved_count
#undef new_size
#undef func_label
}
