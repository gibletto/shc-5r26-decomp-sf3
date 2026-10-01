#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 0041e0c0
// name : cse_reinsert_class
// size : 197
// sig  : void cse_reinsert_class(il_node * head)


int __cdecl cse_reinsert_class(il_node *head)

{
  char cVar1;
  byte kind;
  il_op op;
  
  cVar1 = is_conditionally_evaluated(head);
  while (cVar1 != '\0') {
    head = cse_drop_class_head(head);
    if (head->refcnt < 2) {
      return;
    }
    cVar1 = is_conditionally_evaluated(head);
  }
  op = head->op;
  if (((((op != IL_ID) || (head->symx < 1)) || ((g_symtab[head->symx].attr & 3) != 0)) ||
      ((cVar1 = g_symtab[head->symx].sclass, cVar1 < '\x01' || ('\x04' < cVar1)))) &&
     ((cVar1 = (&g_op_class)[(char)op], cVar1 != '\x10' ||
      ((kind = head->type & 0xf0, kind == 0x80 || (kind == 0x90)))))) {
    if (((cVar1 == '\x04') || (cVar1 == '\b')) || (cVar1 == '\x10')) {
      cse_hash_arith_expr(head,head->cse_block);
    }
    return;
  }
  if (op != IL_ID) {
    cse_record_memory_ref(head,head->cse_block);
    return;
  }
  cse_record_variable(head,head->cse_block);
  return;
}



