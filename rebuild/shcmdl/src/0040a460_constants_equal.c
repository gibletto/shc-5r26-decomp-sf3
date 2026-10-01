#include "decls.h"
#include "imports.h"

// entry: 0040a460
// name : constants_equal
// size : 94
// sig  : int constants_equal(il_node * a, il_node * b)


int __cdecl constants_equal(il_node *a,il_node *b)

{
  byte a_type;
  byte b_type;
  
  b_type = b->type;
  a_type = a->type;
  if (((((b_type ^ a_type) & 0xfc) == 0) ||
      ((((((a_type & 0xe0) == 0 && ((b_type & 0xe0) == 0)) && ((a_type & 0xf8) != 0)) &&
        (((b_type & 0xf8) != 0 && ((a_type & 0xf8) != 8)))) &&
       (((b_type & 0xf8) != 8 && (((b_type ^ a_type) & 4) == 0)))))) &&
     (((b->val == a->val && (b->val2 == a->val2)) && (b->val3 == a->val3)))) {
    return 1;
  }
  return 0;
}



