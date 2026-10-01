#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_deref_count_cursor
#define g_deref_count_cursor (*(deref_count * *)(g_sd + 0x1fa18))
#undef g_r0_variable
#define g_r0_variable (*(deref_count * *)(g_sd + 0x1f9a8))


// entry: 0041c000
// name : count_deref_use
// size : 103
// sig  : void count_deref_use(gen_node * id)


int __cdecl count_deref_use(gen_node *id)

{
  deref_count *found;
  deref_count *entry;
  ushort lreg_sign;
  
  found = find_deref_count(id->symx,id->lreg);
  entry = g_deref_count_cursor;
  if (found == (deref_count *)0x0) {
    g_deref_count_cursor->symx = id->symx;
    lreg_sign = id->lreg >> 0xf;
    entry->lreg = (id->lreg ^ lreg_sign) - lreg_sign;
    entry->count = '\x01';
    g_deref_count_cursor = g_deref_count_cursor + 1;
  }
  else {
    found->count = found->count + '\x01';
    entry = found;
  }
  if ((g_r0_variable == (deref_count *)0x0) || (g_r0_variable->count < entry->count)) {
    g_r0_variable = entry;
  }
  return;
}



