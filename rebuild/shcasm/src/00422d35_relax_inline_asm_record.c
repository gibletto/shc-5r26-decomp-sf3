#include "decls.h"
#include "imports.h"

// entry: 00422d35
// name : relax_inline_asm_record
// size : 155
// sig  : void __cdecl relax_inline_asm_record(layout_record *item,int pass)


int __cdecl relax_inline_asm_record(layout_record *item,int pass)

{
  uint sign_mask;
  
  if (pass == 0) {
    item->location = item->location - g_layout_shrink_pass0;
  }
  else {
    item->location = item->location - g_layout_shrink_pass1;
  }
  if (pass == 1) {
    if (item->value == 0) {
      sign_mask = item->location >> 0x1f;
      if (((item->location ^ sign_mask) - sign_mask & 3 ^ sign_mask) != sign_mask) {
        g_layout_shrink_pass1 = g_layout_shrink_pass1 + 2;
      }
    }
    else {
      g_layout_shrink_pass1 =
           ((item->value & 1U) + item->location + item->value + 2 & 3) + g_layout_shrink_pass1;
    }
  }
  return;
}
