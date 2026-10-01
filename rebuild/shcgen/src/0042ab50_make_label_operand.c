#include "decls.h"
#include "imports.h"

// entry: 0042ab50
// name : make_label_operand
// size : 60
// sig  : ea * make_label_operand(short labno)


ea * __cdecl make_label_operand(short labno)

{
  label_ref *labels;
  ea *operand;
  
  labels = alloc_zeroed(8);
  labels->labno1 = labno;
  operand = alloc_zeroed(0xc);
  fill_ea(operand,'\a',-1,-1,'\0',0,labels);
  return operand;
}



