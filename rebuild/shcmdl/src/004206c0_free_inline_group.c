#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_inline_groups
#define g_inline_groups (*(inline_group * *)(g_sd + 0xdec8))


// entry: 004206c0
// name : free_inline_group
// size : 69
// sig  : void free_inline_group(inline_group * group)


int __cdecl free_inline_group(inline_group *group)

{
  free_inline_calls(group->calls);
  if (group->prev != (inline_group *)0x0) {
    group->prev->next = group->next;
  }
  if (group->next != (inline_group *)0x0) {
    group->next->prev = group->prev;
  }
  if (group == g_inline_groups) {
    g_inline_groups = group->next;
  }
  pool_free(group,0xc);
  return;
}



