#include "decls.h"
#include "imports.h"

// entry: 00411860
// name : rewrite_repeated_movi_per_register
// size : 208
// sig  : void rewrite_repeated_movi_per_register(code_node * node)


int __cdecl rewrite_repeated_movi_per_register(code_node *node)

{
  int i;
  uint seen_hi;
  psd *movi;
  uint seen_lo;
  bool already_seen;
  char reg;
  
  seen_hi = 0xffffffff;
  seen_lo = g_reg_mask_table[0xf];
  do {
    if (node == (code_node *)0x0) {
      return;
    }
    i = 0;
    movi = node->psd;
    do {
      if (movi->op == OP_MOVI) {
        reg = movi->ea2->base;
        if (reg < '\0') {
          if ('_' < reg) goto code_r0x004118ba;
          already_seen = false;
        }
        else if (reg < '`') {
          already_seen = (g_reg_mask_table[reg] & seen_lo) != 0;
        }
        else {
code_r0x004118ba:
          already_seen = (g_reg_mask_table[reg] & seen_hi) != 0;
        }
        if (already_seen) break;
        if (reg < '\0') {
          if ('_' < reg) goto code_r0x004118f0;
        }
        else if (reg < '`') {
          seen_lo = seen_lo | g_reg_mask_table[reg];
        }
        else {
code_r0x004118f0:
          seen_hi = seen_hi | g_reg_mask_table[reg];
        }
        rewrite_next_movi_of_register(node,movi);
      }
      i = i + 1;
      movi = movi + 1;
    } while (i < 0xf);
    node = node->next;
  } while( true );
}



