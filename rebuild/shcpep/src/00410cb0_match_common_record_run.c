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


// entry: 00410cb0
// name : match_common_record_run
// size : 471
// sig  : char match_common_record_run(code_node * node_a, psd * rec_a, code_node * node_b, psd * rec_b, psd * * stop)


char __cdecl match_common_record_run(code_node *node_a,psd *rec_a,code_node *node_b,psd *rec_b,psd **stop)

{
  unsigned char _frec_20[32];
#define acc_def_lo (*(uint *)(_frec_20 + 0))
#define use_lo (*(uint *)(_frec_20 + 8))
#define use_hi (*(uint *)(_frec_20 + 12))
#define def_lo (*(uint *)(_frec_20 + 16))
#define def_hi (*(uint *)(_frec_20 + 20))
#define acc_use_lo (*(uint *)(_frec_20 + 24))
  char result;
  uint acc_use_hi;
  uint use_hi_result;
  uint acc_def_hi;
  psd_op op;
  bool r0_reused;
  
  r0_reused = false;
  if (((node_a == (code_node *)0x0) || (node_b == (code_node *)0x0)) || (stop == (psd **)0x0)) {
    return '\0';
  }
  if (rec_a == (psd *)0x0) {
    rec_a = node_a->psd;
    op = rec_a->op;
    if (((op == OP_DUMMY) || (op == OP_LINE)) || ((op == OP_BBGN || (op == OP_BEND)))) {
      rec_a = find_next_psd_record(node_a,rec_a);
    }
  }
  if (rec_b == (psd *)0x0) {
    rec_b = node_b->psd;
    op = rec_b->op;
    if (((op == OP_DUMMY) || (op == OP_LINE)) || ((op == OP_BBGN || (op == OP_BEND)))) {
      rec_b = find_next_psd_record(node_b,rec_b);
    }
  }
  acc_def_hi = 0;
  acc_use_hi = 0;
  acc_use_lo = 0;
  acc_def_lo = 0;
  result = compare_psd_records(rec_a,rec_b);
  if (result == '\x01') {
    return '\0';
  }
  use_hi_result = g_reg_mask_table[0x61];
  if (result != '\x02') {
    while (((use_hi_result = acc_use_hi, result == '\0' && (rec_a != (psd *)0x0)) &&
           (rec_b != (psd *)0x0))) {
      op = rec_a->op;
      if ((op == OP_JUMPT) || (op == OP_JUMPF)) {
        if ((g_reg_mask_table[0x61] & acc_def_hi) == 0) {
          acc_use_hi = acc_use_hi | g_reg_mask_table[0x61];
        }
      }
      else if (op != OP_JUMP) {
        compute_record_register_use_def(rec_a,&use_lo,&def_lo);
        acc_use_lo = acc_use_lo | ~acc_def_lo & use_lo;
        acc_use_hi = acc_use_hi | ~acc_def_hi & use_hi;
        if (((use_hi & 1) != 0) && ((acc_def_hi & 1) != 0)) {
          r0_reused = true;
        }
        acc_def_hi = acc_def_hi | def_hi;
        acc_def_lo = acc_def_lo | def_lo;
        if (((def_hi & 1) != 0) && (r0_reused)) {
          acc_use_hi = acc_use_hi | 1;
        }
      }
      rec_a = find_next_psd_record(node_a,rec_a);
      rec_b = find_next_psd_record(node_b,rec_b);
      result = compare_psd_records(rec_a,rec_b);
    }
  }
  *stop = rec_a;
  stop[1] = rec_b;
  g_rec_use_mask_hi = use_hi_result;
  g_rec_use_mask_lo = acc_use_lo;
  g_rec_def_mask_hi = acc_def_hi;
  g_rec_def_mask_lo = acc_def_lo;
  return result;
#undef acc_def_lo
#undef use_lo
#undef use_hi
#undef def_lo
#undef def_hi
#undef acc_use_lo
}



