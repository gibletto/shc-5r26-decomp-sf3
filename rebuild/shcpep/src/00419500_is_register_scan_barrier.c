#include "decls.h"
#include "imports.h"

// entry: 00419500
// name : is_register_scan_barrier
// size : 57
// sig  : char is_register_scan_barrier(psd * rec)


char __cdecl is_register_scan_barrier(psd *rec)

{
  char result;
  psd_op op;
  char reg;
  
  result = '\0';
  op = rec->op;
  if (op == OP_LDC) {
    reg = rec->ea2->base;
    if ((reg == 'a') || (reg == 'c')) {
      return '\x01';
    }
  }
  else if (OP_STS < op) {
    if (OP_SLEEP < op) {
      return result;
    }
    result = '\x01';
  }
  return result;
}



