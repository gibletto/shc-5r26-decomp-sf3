#include "decls.h"
#include "imports.h"

// entry: 0041e30b
// name : alloc_ea_operand
// size : 79
// sig  : ea * alloc_ea_operand(uchar type, uchar base, uchar index, int disp, label_ref * labels)


ea * __cdecl alloc_ea_operand(uchar type,uchar base,uchar index,int disp,label_ref *labels)

{
  ea *operand;
  
  operand = pool_alloc(0xc);
  operand->type = type;
  operand->base = base;
  operand->index = index;
  operand->disp = disp;
  operand->labels = labels;
  return operand;
}



