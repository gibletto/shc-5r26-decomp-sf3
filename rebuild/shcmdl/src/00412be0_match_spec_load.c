#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef _g_spec_sym1
#define _g_spec_sym1 (*(short *)(g_sd + 0xe050))
#undef _g_spec_sym2
#define _g_spec_sym2 (*(short *)(g_sd + 0xe052))
#undef g_spec_sym1
#define g_spec_sym1 (*(short *)(g_sd + 0xe050))


// entry: 00412be0
// name : match_spec_load
// size : 343
// sig  : int match_spec_load(il_node * expr, char which)


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl match_spec_load(il_node *expr,char which)

{
  il_node *piVar1;
  int ok;
  il_node *scale;
  short symx;
  byte ty;
  
  if (((((expr->op != IL_CAST) || ((expr->type & 0xf8) != 0x10)) ||
       (piVar1 = expr->child, piVar1->op != IL_ASTER)) ||
      (((piVar1->type & 0xf8) != 8 || (piVar1 = piVar1->child, piVar1->op != IL_ADD)))) ||
     ((piVar1->type & 0xf8) != 0x40)) {
    return 0;
  }
  ok = match_spec_scale(piVar1->child->next,'\x02');
  if (ok == 0) {
    return 0;
  }
  piVar1 = expr->child->child->child;
  if (((piVar1->op == IL_QUALIFY) && ((piVar1->type & 0xf8) == 0x40)) && (piVar1->val2 == 0)) {
    piVar1 = piVar1->child;
    if ((((piVar1->op != IL_ASTER) || ((piVar1->type & 0xe0) != 0x60)) ||
        (piVar1 = piVar1->child, piVar1->op != IL_ASTER)) || ((piVar1->type & 0xf8) != 0x40)) {
      return 0;
    }
    piVar1 = piVar1->child;
    if ((((piVar1->op == IL_ADD) && ((piVar1->type & 0xf8) == 0x40)) &&
        ((scale = piVar1->child, scale->op == IL_ID &&
         (((scale->type & 0xf8) == 0x40 && (scale = scale->next, scale->op == IL_MUL)))))) &&
       ((ty = scale->type, (ty & 0xe0) == 0 && (((ty & 4) != 0 && ((ty & 0xf8) == 0x18)))))) {
      ok = match_spec_scale(scale,'\x01');
      if (ok == 0) {
        return 0;
      }
      symx = piVar1->child->symx;
      if (which == '\x01') {
        _g_spec_sym1 = symx;
        return 1;
      }
      _g_spec_sym2 = symx;
      return 1;
    }
    return 0;
  }
  return 0;
}



