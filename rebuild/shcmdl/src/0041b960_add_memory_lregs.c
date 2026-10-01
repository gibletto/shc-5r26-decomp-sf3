#include "decls.h"
#include "imports.h"

// entry: 0041b960
// name : add_memory_lregs
// size : 80
// sig  : void add_memory_lregs(short next_mem_id)


int __cdecl add_memory_lregs(short next_mem_id)

{
  lreg *lr;
  const_data **list_head;
  lreg *obj;
  
  list_head = g_mem_object_lists;
  do {
    for (obj = (lreg *)*list_head; obj != (lreg *)0x0; obj = obj->life) {
      lr = new_register_candidate(obj,2);
      g_lreg_count = g_lreg_count + 1;
      g_lreg_table[g_lreg_count] = lr;
      lr->pregno = next_mem_id;
      next_mem_id = next_mem_id + -1;
    }
    *list_head = (const_data *)0x0;
    list_head = list_head + 1;
  } while (list_head < g_lreg_table);
  return;
}



