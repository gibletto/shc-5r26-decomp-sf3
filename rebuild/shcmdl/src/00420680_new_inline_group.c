#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_inline_groups
#define g_inline_groups (*(inline_group * *)(g_sd + 0xdec8))


// entry: 00420680
// name : new_inline_group
// size : 54
// sig  : inline_group * new_inline_group(inline_call * cand)


inline_group * __cdecl new_inline_group(inline_call *cand)

{
  inline_group *group;
  
  group = pool_alloc(0xc);
  if (group == (inline_group *)0x0) {
    abort_function_optimization();
  }
  group->calls = cand;
  group->next = g_inline_groups;
  group->prev = (inline_group *)0x0;
  g_inline_groups = group;
  return group;
}



