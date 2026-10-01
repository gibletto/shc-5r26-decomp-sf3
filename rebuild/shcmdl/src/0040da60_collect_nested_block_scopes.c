#include "decls.h"
#include "imports.h"

// entry: 0040da60
// name : collect_nested_block_scopes
// size : 133
// sig  : void collect_nested_block_scopes(il_node * node, scope_info * info)


int __cdecl collect_nested_block_scopes(il_node *node,scope_info *info)

{
  short count;
  short *array;
  short **scopes;
  il_node *sub;
  
  for (sub = node->child; sub != (il_node *)0x0; sub = sub->next) {
    if (sub->op == IL_BLOCK) {
      scopes = &info->scopes;
      count = info->nscopes + 1;
      info->nscopes = count;
      if (count == 1) {
        array = stock_calloc(1,2);
      }
      else {
        array = stock_realloc(*scopes,count * 2);
      }
      *scopes = array;
      if (*scopes == (short *)0x0) {
        abort_function_optimization();
      }
      (*scopes)[info->nscopes + -1] = sub->symx;
      g_inline_scopes_changed = '\x01';
    }
    else {
      collect_nested_block_scopes(sub,info);
    }
  }
  return;
}



