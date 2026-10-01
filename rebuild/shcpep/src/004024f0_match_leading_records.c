#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_rec_def_mask_hi
#define g_rec_def_mask_hi (*(unsigned int *)(g_sd + 0x6d5c))
#undef g_rec_def_mask_lo
#define g_rec_def_mask_lo (*(unsigned int *)(g_sd + 0x6d58))
#undef g_rec_use_mask_hi
#define g_rec_use_mask_hi (*(unsigned int *)(g_sd + 0x5c44))
#undef g_rec_use_mask_lo
#define g_rec_use_mask_lo (*(unsigned int *)(g_sd + 0x5c40))


// entry: 004024f0
// name : match_leading_records
// size : 132
// sig  : char match_leading_records(code_node * node, psd * rec, code_node * other, psd * * match_end)


char __cdecl match_leading_records(code_node *node,psd *rec,code_node *other,psd **match_end)

{
  char result;
  int i;
  psd *rec_b;
  psd_op op;
  
  result = '\0';
  if (other == (code_node *)0x0) {
    return '\0';
  }
  do {
    rec_b = other->psd;
    i = 0;
    do {
      op = rec_b->op;
      if ((((op != OP_DUMMY) && (op != OP_BBGN)) && (op != OP_BEND)) &&
         ((op != OP_LINE &&
          (result = match_common_record_run(node,rec,other,rec_b,match_end), result != '\0')))) {
        if (((g_rec_def_mask_lo & g_rec_use_mask_lo) != 0) ||
           ((g_rec_def_mask_hi & g_rec_use_mask_hi) != 0)) {
          return -1;
        }
        break;
      }
      i = i + 1;
      rec_b = rec_b + 1;
    } while (i < 0xf);
    if (i < 0xf) {
      return result;
    }
    other = other->next;
    if (other == (code_node *)0x0) {
      return result;
    }
  } while( true );
}



