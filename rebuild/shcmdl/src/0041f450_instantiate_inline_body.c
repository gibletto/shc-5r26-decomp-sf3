#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 0041f450
// name : instantiate_inline_body
// size : 584
// sig  : il_node * instantiate_inline_body(inline_call * cand)


il_node * __cdecl instantiate_inline_body(inline_call *cand)

{
  short sVar1;
  il_node *pos;
  uint new_symx;
  il_node *body;
  inline_map_entry *map_entry;
  il_node *arg_copy;
  il_node *param_id;
  il_node *piVar2;
  int param_ofs;
  il_node *arg;
  int *info;
  byte param_type;
  byte ty;
  
  info = g_symtab[cand->callee].info;
  if ((*(byte *)(info + 1) & 0xf8) != 0x50) {
    new_symx = new_symbol(0,'\x05');
    cand->result = (short)new_symx;
    g_symtab[(short)new_symx].type = (uchar)info[1];
    g_symtab[cand->result].size = *info;
  }
  body = copy_tree(0,(g_symtab[cand->callee].inline_body)->tree);
  body = body->child;
  sVar1 = body->symx;
  new_symx = new_symbol(sVar1,'\0');
  body->symx = (short)new_symx;
  add_inline_map_entry(2,(short)new_symx,sVar1);
  renumber_inline_body(body,cand);
  free_node(body->parent);
  pos = body->child;
  arg = cand->call->child->next->child;
  if (arg->op != IL_E_ARG) {
    param_ofs = 0;
    do {
      map_entry = find_inline_map_entry
                            (1,*(short *)((int)(g_symtab[cand->callee].inline_body)->params +
                                         param_ofs));
      if (map_entry == (inline_map_entry *)0x0) {
        arg_copy = copy_tree(0,arg);
        clear_line_info(arg_copy);
        insert_before(pos,arg_copy);
      }
      else {
        arg_copy = copy_tree(0,arg);
        param_id = alloc_node();
        param_id->op = IL_ID;
        sVar1 = map_entry->new_number;
        param_id->symx = sVar1;
        ty = g_symtab[sVar1].type;
        param_id->type = ty;
        piVar2 = make_node(IL_ASSIGN,ty & 0xfc,param_id,arg_copy,(il_node *)0x0);
        insert_before(pos,piVar2);
        ty = arg_copy->type;
        param_type = param_id->type;
        if ((((ty ^ param_type) & 0xfc) != 0) &&
           (((((param_type & 0xe0) != 0 || ((ty & 0xe0) != 0)) || ((param_type & 0xf8) == 0)) ||
            ((((ty & 0xf8) == 0 || ((param_type & 0xf8) == 8)) ||
             (((ty & 0xf8) == 8 || (((ty ^ param_type) & 4) != 0)))))))) {
          piVar2 = alloc_node();
          piVar2->op = IL_CAST;
          piVar2->type = param_id->type & 0xfc;
          insert_parent(arg_copy,piVar2);
        }
        add_member_to_scope(body->symx,param_id->symx);
      }
      arg = arg->next;
      param_ofs = param_ofs + 2;
    } while (arg->op != IL_E_ARG);
  }
  clear_inline_maps();
  return body;
}



