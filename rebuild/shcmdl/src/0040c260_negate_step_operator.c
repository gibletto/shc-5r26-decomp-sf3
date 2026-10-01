#include "decls.h"
#include "imports.h"

// entry: 0040c260
// name : negate_step_operator
// size : 49
// sig  : void negate_step_operator(il_node * step)


int __cdecl negate_step_operator(il_node *step)

{
  switch(step->op) {
  case IL_PRI:
  case IL_POI:
    step->op = step->op + IL_E_FILE;
    return;
  case IL_A_ADD:
    step->op = IL_A_SUB;
    return;
  case IL_A_SUB:
    step->op = IL_A_ADD;
  }
  return;
}



