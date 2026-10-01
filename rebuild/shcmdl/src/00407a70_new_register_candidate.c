#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_candidate_list_tail
#define g_candidate_list_tail (*(lreg * *)(g_sd + 0x1626c))
#undef g_lreg_list
#define g_lreg_list (*(lreg * *)(g_sd + 0x16264))


// entry: 00407a70
// name : new_register_candidate
// size : 132
// sig  : lreg * new_register_candidate(void * source, int kind)


lreg * __cdecl new_register_candidate(void *source,int kind)

{
  lreg *reg;
  
  if (g_candidate_list_tail == (lreg *)0x0) {
    g_lreg_list = regalloc_alloc(0x2c);
    g_candidate_list_tail = g_lreg_list;
  }
  else {
    reg = regalloc_alloc(0x2c);
    g_candidate_list_tail->next = reg;
    g_candidate_list_tail = g_candidate_list_tail->next;
  }
  g_candidate_list_tail->set = (short)kind;
  g_candidate_list_tail->chain = source;
  if ((kind == 1) && (source != (void *)0x0)) {
    do {
      if (*(int *)source == 2) {
        *(lreg **)(*(int *)((int)source + 0x10) + 0x28) = g_candidate_list_tail;
      }
      source = *(void **)((int)source + 8);
    } while (source != (int *)0x0);
    return g_candidate_list_tail;
  }
  return g_candidate_list_tail;
}



