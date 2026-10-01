#include "decls.h"
#include "imports.h"

// entry: 00412d40
// name : match_spec_scale
// size : 211
// sig  : int match_spec_scale(il_node * node, char mode)


int __cdecl match_spec_scale(il_node *node,char mode)

{
  il_node *lhs;
  il_node *rhs;
  byte ty;
  
  lhs = node->child;
  if ((((lhs->op != IL_CAST) || (ty = lhs->type, (ty & 0xe0) != 0)) || ((ty & 4) == 0)) ||
     ((ty & 0xf8) != 0x18)) {
    return 0;
  }
  rhs = lhs->next;
  if (mode != '\x01') {
    if (((rhs->op == IL_CONST) && (ty = rhs->type, (ty & 0xe0) == 0)) &&
       (((ty & 4) != 0 && (((ty & 0xf8) == 0x18 && (rhs->val == 2)))))) {
      lhs = lhs->child;
      if (((lhs->op == IL_ID) && ((lhs->type & 0xf8) == 0x10)) && (lhs->symx == g_spec_index_sym)) {
        return 1;
      }
      return 0;
    }
    return 0;
  }
  if (((rhs->op == IL_CONST) && (ty = rhs->type, (ty & 0xe0) == 0)) &&
     (((ty & 4) != 0 && (((ty & 0xf8) == 0x18 && (rhs->val == 4)))))) {
    lhs = lhs->child;
    if (((lhs->op == IL_CONST) && ((lhs->type & 0xf8) == 0x10)) && (lhs->val == 0)) {
      return 1;
    }
    return 0;
  }
  return 0;
}



