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


// entry: 00402580
// name : delete_matched_target_prefix
// size : 483
// sig  : char delete_matched_target_prefix(code_node * target, code_node * pred, psd * * match_end)


/* WARNING: Removing unreachable block (ram,0x004025a6) */

char __cdecl delete_matched_target_prefix(code_node *target,code_node *pred,psd **match_end)

{
  unsigned char _frec_20[32];
#define rec_defs_lo (*(uint *)(_frec_20 + 0))
#define rec_defs_hi (*(uint *)(_frec_20 + 4))
#define run_defs_lo (*(uint *)(_frec_20 + 8))
#define run_defs_hi (*(uint *)(_frec_20 + 12))
#define rec_uses (*(psd * (*)[3])(_frec_20 + 16))
#define run_uses_hi (*(uint *)(_frec_20 + 28))
  char cVar1;
  uint uVar2;
  int i;
  psd *rec;
  bool in_match;
  code_node *node;
  psd_op op;
  
  uVar2 = g_rec_use_mask_lo;
  in_match = false;
  rec = rec_uses[0];
  run_defs_lo = g_rec_def_mask_lo;
  run_defs_hi = g_rec_def_mask_hi;
  run_uses_hi = g_rec_use_mask_hi;
  node = target;
  if (match_end[1] != (psd *)0x0) {
    for (; pred != (code_node *)0x0; pred = pred->next) {
      i = 0;
      rec = pred->psd;
      do {
        if (match_end[1] == rec) {
          in_match = true;
        }
        op = rec->op;
        if ((((op != OP_LABEL) && (op != OP_DLABEL)) && (op != OP_CLABEL)) &&
           (((op != OP_DUMMY && (op != OP_LINE)) &&
            ((op != OP_BBGN && ((op != OP_BEND && (in_match)))))))) {
          if (op == OP_CASEJMP) {
            return '\0';
          }
          cVar1 = compute_record_register_use_def(rec,(uint *)rec_uses,&rec_defs_lo);
          if ((((cVar1 != '\0') || ((rec_defs_lo & run_defs_lo) != 0)) ||
              ((rec_defs_hi & run_defs_hi) != 0)) ||
             (((rec_defs_lo & uVar2) != 0 || ((rec_defs_hi & run_uses_hi) != 0)))) {
            return '\0';
          }
        }
        i = i + 1;
        rec = rec + 1;
      } while (i < 0xf);
    }
  }
  for (; node != (code_node *)0x0; node = node->next) {
    i = 0;
    rec = node->psd;
    do {
      if (*match_end == rec) break;
      op = rec->op;
      if (((op != OP_LABEL) && (op != OP_DLABEL)) &&
         (((op != OP_CLABEL && (((op != OP_DUMMY && (op != OP_LINE)) && (op != OP_BBGN)))) &&
          ((op != OP_BEND && (uVar2 = is_record_volatile(rec), uVar2 != 0)))))) {
        return '\0';
      }
      i = i + 1;
      rec = rec + 1;
    } while (i < 0xf);
    if (i < 0xf) break;
  }
  if ((*match_end != (psd *)0x0) && (rec != *match_end)) {
    return '\0';
  }
  do {
    if (target == (code_node *)0x0) {
      return '\x01';
    }
    rec = target->psd;
    i = 0;
    do {
      if (*match_end == rec) break;
      op = rec->op;
      if ((((op != OP_LABEL) && (op != OP_DLABEL)) && (op != OP_CLABEL)) &&
         (((op != OP_DUMMY && (op != OP_LINE)) && ((op != OP_BBGN && (op != OP_BEND)))))) {
        delete_psd_record(rec);
      }
      i = i + 1;
      rec = rec + 1;
    } while (i < 0xf);
    if (i < 0xf) {
      return '\x01';
    }
    target = target->next;
  } while( true );
#undef rec_defs_lo
#undef rec_defs_hi
#undef run_defs_lo
#undef run_defs_hi
#undef rec_uses
#undef run_uses_hi
}



