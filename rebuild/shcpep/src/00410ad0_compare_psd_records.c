#include "decls.h"
#include "imports.h"

// entry: 00410ad0
// name : compare_psd_records
// size : 431
// sig  : char compare_psd_records(psd * a, psd * b)


char __cdecl compare_psd_records(psd *a,psd *b)

{
  short sVar1;
  psd_op op;
  
  if ((a == (psd *)0x0) || (b == (psd *)0x0)) {
    return '\x01';
  }
  if ((((b->op != a->op) || (b->flg != a->flg)) || (b->misc != a->misc)) ||
     (b->sptravel != a->sptravel)) {
    return '\x01';
  }
  switch(a->op) {
  case OP_NON_10:
    if (((b->filno != a->filno) || (b->linno != a->linno)) ||
       ((b->ea1 != a->ea1 || (b->ea2 != a->ea2)))) {
      return '\x01';
    }
    break;
  case OP_CASEJMP:
    if ((((b->filno != a->filno) || (b->linno != a->linno)) || (b->ea1 != a->ea1)) ||
       (b->ea2 != a->ea2)) {
      return '\x01';
    }
    break;
  default:
    sVar1 = common_code_ea_equal(a->ea1,b->ea1);
    if ((sVar1 == 0) || (sVar1 = common_code_ea_equal(a->ea2,b->ea2), sVar1 == 0)) {
      op = a->op;
      if ((op != OP_JUMP) && ((op != OP_JUMPT && (op != OP_JUMPF)))) {
        return '\x01';
      }
      return '\x02';
    }
    break;
  case OP_CTBL:
  case OP_CENT:
    if ((((b->filno != a->filno) || (b->linno != a->linno)) ||
        (*(short *)&b->ea1 != *(short *)&a->ea1)) ||
       ((*(short *)((int)&b->ea1 + 2) != *(short *)((int)&a->ea1 + 2) || (b->ea2 != a->ea2)))) {
      return '\x01';
    }
    break;
  case OP_LABEL:
  case OP_CLABEL:
  case OP_DLABEL:
  case OP_FLABEL:
    if (((*(short *)&b->ea1 != *(short *)&a->ea1) ||
        (*(short *)((int)&b->ea1 + 2) != *(short *)((int)&a->ea1 + 2))) || (b->ea2 != a->ea2)) {
      return '\x01';
    }
    break;
  case OP_LINE:
    if (((*(char *)&b->ea1 != *(char *)&a->ea1) ||
        (*(char *)((int)&b->ea1 + 1) != *(char *)((int)&a->ea1 + 1))) ||
       ((*(short *)((int)&b->ea1 + 2) != *(short *)((int)&a->ea1 + 2) || (b->ea2 != a->ea2)))) {
      return '\x01';
    }
    break;
  case OP_SWBGN:
  case OP_SWEND:
    break;
  }
  if (b->tmp == a->tmp) {
    return '\0';
  }
  op = a->op;
  if (((op != OP_JUMP) && (op != OP_JUMPT)) && (op != OP_JUMPF)) {
    return '\x01';
  }
  return '\x02';
}



