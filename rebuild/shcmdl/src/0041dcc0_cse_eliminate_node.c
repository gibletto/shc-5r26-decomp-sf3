#include "decls.h"
#include "imports.h"
#include "castmul.h"
#include "gcserules.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_cse_variables
#define g_cse_variables (*(node_list * *)(g_sd + 0x267a4))
#undef g_memory_refs
#define g_memory_refs (*(node_list * *)(g_sd + 0x1e780))
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 0041dcc0
// name : cse_eliminate_node
// size : 384
// sig  : il_node * cse_eliminate_node(il_node * node)


il_node * __cdecl cse_eliminate_node(il_node *node)

{
  char cVar1;
  node_list *pnVar2;
  symbol *sym;
  int memory_kind;
  bblock *blk;
  il_node *stmt;
  byte kind;
  node_list **ppnVar3;
  node_list *first;
  node_list *item;
  il_op op;
  node_list **prev_link;
  
  CASTMUL_VISIT(node);
  op = node->op;
  if (((((op == IL_ID) && (0 < node->symx)) && (sym = g_symtab + node->symx, (sym->attr & 3) == 0))
      && (((sym->unknown_38 == -1 && ('\0' < sym->sclass)) && (sym->sclass < '\x05')))) ||
     (((cVar1 = (&g_op_class)[(char)op], cVar1 == '\x10' && (kind = node->type & 0xf0, kind != 0x80)
       ) && (kind != 0x90)))) {
    if (op == IL_ID) {
      ppnVar3 = &g_cse_variables;
      first = g_cse_variables;
      memory_kind = 1;
    }
    else {
      ppnVar3 = &g_memory_refs;
      first = g_memory_refs;
      memory_kind = 2;
    }
    pnVar2 = *ppnVar3;
    while (prev_link = ppnVar3, item = pnVar2, item != (node_list *)0x0) {
      pnVar2 = item->next;
      ppnVar3 = &item->next;
      if (item->node == node) {
        if ((node->cse_next != (il_node *)0x0) &&
           (blk = cse_find_common_block(node,memory_kind), blk != (bblock *)0x0) && GCSE_BLOCK_OK(node,blk)) {
          stmt = cse_find_using_stmt(blk,node);
          node = cse_replace_with_temp(stmt,node,blk);
        }
        if (first != item) {
          *prev_link = item->next;
          pool_free(item,8);
        }
        return node;
      }
    }
  }
  else if (((cVar1 == '\x04') || (cVar1 == '\b')) || (cVar1 == '\x10')) {
    ppnVar3 = g_expr_hash;
    do {
      for (pnVar2 = *ppnVar3; pnVar2 != (node_list *)0x0; pnVar2 = pnVar2->next) {
        if (((pnVar2->node == node) && (node->cse_next != (il_node *)0x0)) &&
           (blk = cse_find_common_block(node,(uint)((node->flag2 & 8) != 0)), blk != (bblock *)0x0) && GCSE_BLOCK_OK(node,blk) && CASTMUL_OK(node,blk))
        {
          stmt = cse_find_using_stmt(blk,node);
          stmt = cse_replace_with_temp(stmt,node,blk);
          return stmt;
        }
      }
      ppnVar3 = ppnVar3 + 1;
      if ((node_list **)((int)g_expr_hash + 0x1ff) < ppnVar3) {
        return node;
      }
    } while( true );
  }
  return node;
}



