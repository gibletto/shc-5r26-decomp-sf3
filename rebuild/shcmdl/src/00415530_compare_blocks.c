#include "decls.h"
#include "imports.h"

// entry: 00415530
// name : compare_blocks
// size : 146
// sig  : uint compare_blocks(bblock * a, bblock * b)


uint __cdecl compare_blocks(bblock *a,bblock *b)

{
  il_node *stmt_a;
  il_node *stmt_b;
  uint result;
  byte *flagp;
  
  if (b == a) {
    return 0;
  }
  stmt_a = last_statement_of_list(a->ilnode);
  stmt_b = last_statement_of_list(b->ilnode);
  if ((stmt_a != (il_node *)0x0) && (stmt_b != (il_node *)0x0)) {
    g_merge_match_depth = 0;
    result = compare_statements_backward(stmt_a,stmt_b,a,b);
    if (result == 0) {
      g_merge_pair_count = g_merge_pair_count + 1;
      flagp = (byte *)((int)&a->flag + 1);
      *flagp = *flagp | 1;
      flagp = (byte *)((int)&b->flag + 1);
      *flagp = *flagp | 1;
      if (b->number <= a->number) {
        link_merged_block(a,b);
        return 0;
      }
      link_merged_block(b,a);
    }
    return result;
  }
  return 1;
}



