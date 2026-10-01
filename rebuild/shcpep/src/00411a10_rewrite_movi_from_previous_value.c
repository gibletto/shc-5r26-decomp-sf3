#include "decls.h"
#include "imports.h"

// entry: 00411a10
// name : rewrite_movi_from_previous_value
// size : 226
// sig  : void rewrite_movi_from_previous_value(psd * prev_movi, psd * movi)


int __cdecl rewrite_movi_from_previous_value(psd *prev_movi,psd *movi)

{
  ea *peVar1;
  ea *b;
  label_ref *ptr;
  psd_op shift_op;
  int new_value;
  int delta;
  label_ref *next_ref;
  
  if ((prev_movi->op == OP_MOVI) && (movi->op == OP_MOVI)) {
    peVar1 = prev_movi->ea1;
    b = movi->ea1;
    new_value = immediates_match_except_value(peVar1,b);
    if (new_value != 0) {
      new_value = b->disp;
      if (((b->labels != (label_ref *)0x0) || (new_value < -0x80)) || (0x7f < new_value)) {
        delta = new_value - peVar1->disp;
        if ((-0x81 < delta) && (delta < 0x80)) {
          movi->op = OP_ADD;
          movi->flg = '\x02';
          movi->tmp = -1;
          movi->ea1->disp = delta;
          ptr = b->labels;
          while (ptr != (label_ref *)0x0) {
            next_ref = ptr->next;
            pool_free(ptr,8);
            ptr = next_ref;
          }
          b->labels = (label_ref *)0x0;
          return;
        }
        if (peVar1->labels == (label_ref *)0x0) {
          shift_op = find_shift_op_between_values(peVar1->disp,new_value);
          switch(shift_op) {
          case OP_SHLL2:
          case OP_SHLL8:
          case OP_SHLL16:
          case OP_SHLR2:
          case OP_SHLR8:
          case OP_SHLR16:
            movi->op = shift_op;
            movi->flg = '\x02';
            movi->tmp = -1;
            free_ea(b);
            peVar1 = movi->ea2;
            movi->ea2 = (ea *)0x0;
            movi->ea1 = peVar1;
          }
        }
      }
    }
  }
  return;
}



