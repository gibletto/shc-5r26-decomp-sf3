#include "decls.h"
#include "imports.h"

// entry: 00418c40
// name : record_induction_use
// size : 86
// sig  : void record_induction_use(il_node * id, il_node * copy)


int __cdecl record_induction_use(il_node *id,il_node *copy)

{
  iv_use *use;
  
  if (id->ivno != 0) {
    use = pool_alloc(0x24);
    if (use == (iv_use *)0x0) {
      free_induction_tables();
      abort_function_optimization();
    }
    use->next = g_iv_table[id->ivno].uses;
    use->id = id;
    use->expr = id;
    use->copy_id = copy;
    use->copy = copy;
    g_iv_table[id->ivno].uses = use;
  }
  return;
}



