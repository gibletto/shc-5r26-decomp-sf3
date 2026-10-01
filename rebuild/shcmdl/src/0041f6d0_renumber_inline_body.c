#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_func_node
#define g_func_node (*(il_node * *)(g_sd + 0x1e738))
#undef g_options
#define g_options (*(option_record * *)(g_sd + 0x1e714))
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 0041f6d0
// name : renumber_inline_body
// size : 1110
// sig  : void renumber_inline_body(il_node * node, inline_call * cand)


int __cdecl renumber_inline_body(il_node *node,inline_call *cand)

{
  uint new_symx;
  il_node *piVar1;
  il_node *piVar2;
  il_node *value_copy;
  switch_case *sw_case;
  switch_table *table;
  int iVar3;
  inline_map_entry *map_entry;
  int ofs;
  short *label_slot;
  void *caller_info;
  short old_label;
  short old_symx;
  char sclass;
  
  piVar1 = node->child;
  while (piVar1 != (il_node *)0x0) {
    piVar2 = piVar1->next;
    if (piVar1->op == IL_BLOCK) {
      old_symx = piVar1->symx;
      new_symx = new_symbol(old_symx,'\0');
      piVar1->symx = (short)new_symx;
      add_inline_map_entry(2,(short)new_symx,old_symx);
    }
    if (piVar1->op == IL_SWITCH) {
      g_switch_depth = g_switch_depth + 1;
      *(short *)(&g_switch_number_stack_m1 + g_switch_depth * 2) = piVar1->symx;
      read_switch_table((int)piVar1->symx);
    }
    renumber_inline_body(piVar1,cand);
    piVar1 = piVar2;
  }
  switch(node->op) {
  case IL_BLOCK:
    remap_inlined_scope_members(node->symx);
    if (node->parent->op != IL_FUNC) {
      add_scope_to_enclosing_block(node);
    }
  case IL_E_BLOCK:
    *(byte *)&node->val = (byte)node->val | 1;
    break;
  case IL_SWITCH:
    *(undefined2 *)(&g_switch_number_stack_m1 + g_switch_depth * 2) = 0;
    g_switch_depth = g_switch_depth + -1;
    table = find_switch_table(node->symx);
    node->symx = g_options->next_switch_table;
    g_options->next_switch_table = g_options->next_switch_table + 1;
    table->number = node->symx;
    break;
  case IL_RETURN:
    if (cand->return_label == 0) {
      new_symx = new_symbol(0,'\v');
      cand->return_label = (short)new_symx;
    }
    piVar1 = alloc_node();
    piVar1->op = IL_GOTO;
    piVar1->symx = cand->return_label;
    if (node->child->op == IL_NULL) {
      replace_and_free_node(node,piVar1);
    }
    else {
      if (node->parent->op != IL_BLOCK) {
        wrap_stmt_in_scope(node);
      }
      piVar2 = new_node(IL_ID,g_symtab[cand->result].type);
      piVar2->symx = cand->result;
      value_copy = copy_tree(0,node->child);
      piVar2 = make_node(IL_ASSIGN,piVar2->type & 0xfc,piVar2,value_copy,(il_node *)0x0);
      replace_and_free_node(node,piVar2);
      insert_after(piVar2,piVar1);
    }
    break;
  case IL_GOTO:
    old_symx = node->symx;
    map_entry = find_inline_map_entry(1,old_symx);
    if (map_entry == (inline_map_entry *)0x0) {
      new_symx = new_symbol(old_symx,'\0');
      node->symx = (short)new_symx;
      add_inline_map_entry(1,old_symx,(short)new_symx);
    }
    else {
      node->symx = map_entry->new_number;
    }
    break;
  case IL_GLABEL:
    old_symx = node->symx;
    iVar3 = 0;
    map_entry = find_inline_map_entry(1,old_symx);
    if (map_entry == (inline_map_entry *)0x0) {
      old_label = g_symtab[old_symx].unknown_04;
      new_symx = new_symbol(old_symx,'\0');
      node->symx = (short)new_symx;
      add_inline_map_entry(1,old_symx,(short)new_symx);
      if ((0 < *(short *)((int)g_symtab[cand->callee].info + 8)) &&
         (caller_info = g_symtab[g_func_node->symx].new_info, 0 < *(short *)((int)caller_info + 8)))
      {
        ofs = 0;
        do {
          label_slot = (short *)(*(int *)((int)caller_info + 0x10) + ofs);
          if (*label_slot == old_label) {
            *label_slot = g_symtab[node->symx].unknown_04;
          }
          ofs = ofs + 2;
          iVar3 = iVar3 + 1;
        } while (iVar3 < *(short *)((int)caller_info + 8));
      }
    }
    else {
      node->symx = map_entry->new_number;
    }
    break;
  case IL_CLABEL:
    table = find_switch_table(*(short *)(&g_switch_number_stack_m1 + g_switch_depth * 2));
    sw_case = find_switch_case(table,node->symx);
    iVar3 = new_label_number();
    node->symx = (short)iVar3;
    sw_case->label = (short)iVar3;
    break;
  case IL_DLABEL:
    table = find_switch_table(*(short *)(&g_switch_number_stack_m1 + g_switch_depth * 2));
    iVar3 = new_label_number();
    node->symx = (short)iVar3;
    table->default_label = (short)iVar3;
    break;
  case IL_ID:
    old_symx = node->symx;
    sclass = g_symtab[old_symx].sclass;
    if ((((sclass == '\x05') || (sclass == '\x06')) || (sclass == '\a')) || (sclass == '\b')) {
      map_entry = find_inline_map_entry(1,old_symx);
      if (map_entry == (inline_map_entry *)0x0) {
        new_symx = new_symbol(old_symx,'\0');
        node->symx = (short)new_symx;
        add_inline_map_entry(1,old_symx,(short)new_symx);
        if (g_symtab[node->symx].sclass != '\x06') {
          g_symtab[node->symx].sclass = '\x05';
        }
      }
      else {
        node->symx = map_entry->new_number;
      }
    }
  }
  if ((node->op == IL_CALL) && ((int)g_options->inline_passes != g_inline_pass)) {
    node->filn = cand->call->filn;
    node->line = cand->call->line;
    node->listno = cand->call->listno;
    return;
  }
  node->filn = 0;
  node->line = 0;
  node->listno = 0;
  return;
}



