#include "decls.h"
#include "imports.h"

// entry: 00403380
// name : definition_outside_life_areas
// size : 133
// sig  : int definition_outside_life_areas(lreg * reg, dutbl * def)


int __cdecl definition_outside_life_areas(lreg *reg,dutbl *def)

{
  dutbl *bound_def;
  int iVar1;
  int *area;
  int bound;
  ushort pp;
  
  iVar1 = def->node->val3;
  if (((iVar1 != 0) && (bound = *(int *)(iVar1 + 0x18), bound != 0)) && (iVar1 != bound)) {
    bound_def = find_single_definition(*(dutbl **)(bound + 0x20));
    iVar1 = definition_outside_life_areas(reg,bound_def);
    if (iVar1 == 0) {
      return 0;
    }
  }
  if ((reg->bakbind != (lreg *)0x0) &&
     (iVar1 = definition_outside_life_areas(reg->bakbind,def), iVar1 == 0)) {
    return 0;
  }
  area = reg->life;
  if (area != (int *)0x0) {
    pp = def->node->pp;
    do {
      if ((*(ushort *)(area[1] + 8) <= pp) && (pp <= *(ushort *)(area[1] + 10))) {
        return 0;
      }
      area = (int *)*area;
    } while (area != (int *)0x0);
  }
  return 1;
}



