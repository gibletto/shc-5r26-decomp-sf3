#include "decls.h"
#include "imports.h"

// entry: 0040b100
// name : new_ea_operand
// size : 45
// sig  : ea * __cdecl new_ea_operand(uchar type,char base,char index,int disp,label_ref *labels)


ea * __cdecl new_ea_operand(uchar type,char base,char index,int disp,label_ref *labels)

{
  ea *opnd;
  
  opnd = (ea *)alloc_zeroed_flushing_blocks(0xc);
  opnd->type = type;
  opnd->base = base;
  opnd->index = index;
  opnd->disp = disp;
  opnd->labels = labels;
  return opnd;
}
