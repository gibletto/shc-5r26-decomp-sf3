#include "decls.h"
#include "imports.h"

// entry: 00403c70
// name : convert_test_to_dt
// size : 73
// sig  : void convert_test_to_dt(psd * test, psd * add)


int __cdecl convert_test_to_dt(psd *test,psd *add)

{
  ea *reg_operand;
  
  test->op = OP_DT;
  reg_operand = copy_ea(add->ea2);
  test->ea1 = reg_operand;
  free_ea(test->ea2);
  test->ea2 = (ea *)0x0;
  delete_psd_record(add);
  return;
}



