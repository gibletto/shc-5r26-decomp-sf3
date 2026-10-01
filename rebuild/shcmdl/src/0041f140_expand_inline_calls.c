#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_inline_groups
#define g_inline_groups (*(inline_group * *)(g_sd + 0xdec8))


// entry: 0041f140
// name : expand_inline_calls
// size : 38
// sig  : void expand_inline_calls(il_node * body)


int __cdecl expand_inline_calls(il_node *body)

{
  g_inline_groups = (inline_group *)0x0;
  g_inline_flags = g_inline_flags | 1;
  expand_inline_calls_in_stmt(body);
  g_inline_flags = g_inline_flags & 0xfe;
  return;
}



