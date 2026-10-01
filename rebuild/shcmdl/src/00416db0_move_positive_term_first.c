#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_term_list
#define g_term_list (*(term * *)(g_sd + 0x1e4c8))


// entry: 00416db0
// name : move_positive_term_first
// size : 78
// sig  : void move_positive_term_first(void)


int __cdecl move_positive_term_first(void)

{
  term *prev;
  term *cur;
  term **link;
  
  prev = (term *)0x0;
  cur = g_term_list->next;
  if (g_term_list->next != (term *)0x0) {
    while (cur->op != '@') {
      link = &cur->next;
      prev = cur;
      cur = *link;
      if (*link == (term *)0x0) {
        return;
      }
    }
    if (prev != (term *)0x0) {
      prev->next = cur->next;
      cur->next = g_term_list;
      g_term_list = cur;
      return;
    }
    g_term_list->next = cur->next;
    cur->next = g_term_list;
    g_term_list = cur;
  }
  return;
}



