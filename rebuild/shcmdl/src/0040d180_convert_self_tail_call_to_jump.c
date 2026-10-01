#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_func_node
#define g_func_node (*(il_node * *)(g_sd + 0x1e738))
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 0040d180
// name : convert_self_tail_call_to_jump
// size : 853
// sig  : void convert_self_tail_call_to_jump(bblock * block, node_list * entry, node_list * * link)


int __cdecl convert_self_tail_call_to_jump(bblock *block,node_list *entry,node_list **link)

{
  unsigned char _frec_94[148];
#define i (*(short *)(_frec_94 + 0))
#define arg (*(il_node * *)(_frec_94 + 12))
#define param_list (*(short (*)[64])(_frec_94 + 20))
  il_node *stmt;
  int nargs;
  il_node *piVar1;
  il_node *node;
  il_node *parent;
  il_node *temp;
  node_list *item;
  byte dst_type;
  short filn;
  ushort line;
  short listno;
  char nparams;
  short param_symx;
  byte src_type;
  
  if (entry->node->parent->op == IL_RETURN) {
    stmt = copy_tree(0,entry->node);
    replace_and_free_node(entry->node->parent,stmt);
    entry->node = stmt;
  }
  nparams = *(char *)((int)g_symtab[g_func_node->symx].info + 6);
  *link = (node_list *)0x0;
  stmt = entry->node;
  filn = stmt->filn;
  line = stmt->line;
  listno = stmt->listno;
  if ((stmt->parent->op != IL_BLOCK) && (nparams != '\0')) {
    wrap_in_block_pair(stmt);
  }
  order_params_stack_then_register((int)g_func_node->symx,param_list);
  i = 0;
  arg = stmt->child->next->child;
  if ('\0' < nparams) {
    nargs = (int)(short)nparams;
    do {
      piVar1 = copy_tree(0,arg);
      insert_before(stmt,piVar1);
      node = alloc_node();
      node->op = IL_ID;
      param_symx = param_list[i];
      node->symx = param_symx;
      node->type = g_symtab[param_symx].type;
      node->nleaf = g_symtab[node->symx].ms_leaf;
      dst_type = node->type;
      src_type = piVar1->type;
      parent = piVar1;
      if ((((dst_type ^ src_type) & 0xfc) != 0) &&
         (((((dst_type & 0xe0) != 0 || ((src_type & 0xe0) != 0)) || ((dst_type & 0xf8) == 0)) ||
          ((((src_type & 0xf8) == 0 || ((dst_type & 0xf8) == 8)) ||
           (((src_type & 0xf8) == 8 || (((dst_type ^ src_type) & 4) != 0)))))))) {
        parent = alloc_node();
        parent->op = IL_CAST;
        parent->type = node->type & 0xfc;
        insert_parent(piVar1,parent);
        if (parent->child->op == IL_CONST) {
          parent = fold_constants(parent);
        }
      }
      if (1 < nargs - i) {
        piVar1 = new_node(IL_ASSIGN,node->type & 0xfc);
        piVar1->filn = filn;
        piVar1->line = line;
        piVar1->listno = listno;
        temp = new_temp_id(node->type & 0xfc);
        insert_parent(parent,piVar1);
        insert_before(parent,temp);
        item = pool_alloc(8);
        if (item == (node_list *)0x0) {
          abort_function_optimization();
        }
        item->node = piVar1;
        item->next = *link;
        *link = item;
        parent = copy_tree(1,temp);
        insert_before(stmt,parent);
        link = &item->next;
      }
      stmt = new_node(IL_ASSIGN,node->type);
      stmt->filn = filn;
      stmt->line = line;
      stmt->listno = listno;
      insert_parent(parent,stmt);
      insert_before(parent,node);
      item = pool_alloc(8);
      if (item == (node_list *)0x0) {
        abort_function_optimization();
      }
      i = i + 1;
      item->node = stmt;
      item->next = *link;
      *link = item;
      arg = arg->next;
    } while (nargs != i && -1 < nargs - i);
  }
  stmt = make_goto_entry_label();
  stmt->filn = filn;
  stmt->line = line;
  stmt->listno = listno;
  replace_and_free_node(entry->node,stmt);
  pool_free(entry,8);
  redirect_block_to_function_entry(block);
  return;
#undef i
#undef arg
#undef param_list
}



