#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 0041bdc0
// name : replace_with_register_temp
// size : 512
// sig  : void replace_with_register_temp(il_node * use, short leafno, lreg * lr)


int __cdecl replace_with_register_temp(il_node *use,short leafno,lreg *lr)

{
  il_node *wrapper;
  byte kind;
  short old_symx;
  
  if ((use->op != IL_ID) && (use->op != IL_CONST)) {
    use = use->child;
  }
  if (use->op != IL_ASTER) {
    if ((((((g_regalloc_phase < 3) && (use->op == IL_ID)) && (-1 < use->symx)) &&
         (('\0' < g_symtab[use->symx].sclass && (g_symtab[use->symx].sclass < '\x05')))) &&
        (lr->set == 0)) && (*(short *)lr->chain == 4)) {
      wrapper = copy_tree(1,use);
      wrapper->op = IL_ASTER;
      wrapper->nleaf = 0;
      wrapper->symx = 0;
      kind = use->type & 0xf0;
      if (((kind == 0x60) || (kind == 0x70)) || ((kind == 0x80 || (kind == 0x90)))) {
        wrapper->val = g_symtab[use->symx].size;
      }
      insert_parent(use,wrapper);
      use->nleaf = leafno;
      use->symx = g_temp_symx;
      use->type = '@';
      return;
    }
    kind = use->type & 0xf0;
    if (((kind != 0x80) && (kind != 0x90)) || (use->cmnexp != (il_node *)0x0)) {
      use->op = IL_ID;
      use->nleaf = leafno;
      use->lreg = lr->lregno;
      old_symx = use->symx;
      use->symx = g_temp_symx;
      if (((use->type & 0xf8) == 0x48) && (use->parent->op == IL_CALL)) {
        wrapper = alloc_node();
        wrapper->op = IL_ASTER;
        wrapper->type = 'H';
        insert_parent(use,wrapper);
      }
      kind = use->type & 0xf0;
      if ((kind == 0x60) || (kind == 0x70)) {
        wrapper = alloc_node();
        wrapper->op = IL_ASTER;
        wrapper->type = use->type;
        wrapper->val = g_symtab[old_symx].size;
        insert_parent(use,wrapper);
      }
      kind = use->type & 0xf0;
      if ((((kind == 0x80) || (kind == 0x90)) || ((use->type & 0xf8) == 0x48)) ||
         ((kind == 0x60 || (kind == 0x70)))) {
        use->type = '@';
      }
      if (((lr->set == 0) && (*(short *)lr->chain == 0)) && ((use->type & 0xe0) != 0x20)) {
        wrapper = alloc_node();
        wrapper->op = IL_CAST;
        wrapper->type = use->type;
        use->type = '\x10';
        insert_parent(use,wrapper);
      }
    }
  }
  return;
}



