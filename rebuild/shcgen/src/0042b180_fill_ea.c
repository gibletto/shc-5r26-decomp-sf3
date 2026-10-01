#include "decls.h"
#include "imports.h"

// entry: 0042b180
// name : fill_ea
// size : 59
// sig  : void fill_ea(ea * operand, uchar type, char base, char index, char misc, int disp, label_ref * labels)


int __cdecl fill_ea(ea *operand,uchar type,char base,char index,char misc,int disp,label_ref *labels)

{
  zero_words((uint *)operand,3);
  operand->type = type;
  operand->base = base;
  operand->index = index;
  operand->misc = misc;
  operand->disp = disp;
  operand->labels = labels;
  return;
}



