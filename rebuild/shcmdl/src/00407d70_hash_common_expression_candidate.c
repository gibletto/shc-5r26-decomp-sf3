#include "decls.h"
#include "imports.h"
#include "argconst.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_const_data_list
#define g_const_data_list (*(const_data * *)(g_sd + 0x16498))
#undef g_options
#define g_options (*(option_record * *)(g_sd + 0x1e714))
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 00407d70
// name : hash_common_expression_candidate
// size : 688
// sig  : void hash_common_expression_candidate(bblock * block, il_node * node)


int __cdecl hash_common_expression_candidate(bblock *block,il_node *node)

{
  int is_builtin;
  uint bucket;
  const_data *cdata;
  const_use *use;
  byte size_class;
  byte kind;
  short contents;
  uint value;
  il_node *operand;
  const_data *prev_item;
  
  if (CAST_ADDRESS_LEAF(node)) {
    return;
  }
  if (((node->op & IL_NON_F0) == IL_A_ADD) || (operand = node, (node->op & IL_NON_F8) == IL_PRI)) {
    operand = node->child;
  }
  if (operand->op == IL_ID) {
    if (operand->symx < 0) {
      return;
    }
    if ((operand->parent->op == IL_CALL) &&
       (is_builtin = is_builtin_name(g_symtab[operand->symx].name), is_builtin != 0)) {
      return;
    }
    if ((operand->parent->op == IL_CALL) && ((g_symtab[operand->symx].flags & 0x40) != 0)) {
      return;
    }
    size_class = operand->type & 0xf8;
    if (((((size_class == 0x48) && (g_symtab[operand->symx].sclass == '\x02')) ||
         (kind = operand->type & 0xf0, kind == 0x80)) || ((kind == 0x90 || (kind == 0x60)))) ||
       (kind == 0x70)) {
      value = (uint)operand->nleaf;
      contents = 1;
    }
    else {
      if (size_class == 0x48) {
        return;
      }
      if (g_symtab[operand->symx].sclass < '\x01') {
        return;
      }
      if ('\x04' < g_symtab[operand->symx].sclass) {
        return;
      }
      value = (uint)operand->nleaf;
      contents = 4;
    }
  }
  else {
    value = operand->val;
    contents = 0;
  }
  bucket = value & 0x7f;
  cdata = g_cmnexp_hash[bucket];
  do {
    if (cdata == (const_data *)0x0) {
LAB_00407fbf:
      if (cdata == (const_data *)0x0) {
        cdata = regalloc_alloc(0x1c);
        cdata->next = g_const_data_list;
        g_const_data_list = cdata;
        if (g_cmnexp_hash[bucket] == (const_data *)0x0) {
          g_cmnexp_hash[bucket] = cdata;
        }
        else {
          prev_item->hash_next = cdata;
        }
        use = regalloc_alloc(0x14);
        use->block = block;
        use->node = node;
        cdata->uses = use;
        cdata->value = value;
        cdata->contents = contents;
      }
      return;
    }
    prev_item = cdata;
    if ((cdata->value == value) && (cdata->contents == contents)) {
      if (contents == 0) {
        if ((g_options->cpu == 2) && (g_options->fpu_mode == '\x03')) {
          size_class = operand->type & 0xf8;
          if (((size_class == 0x28) &&
              ((kind = cdata->uses->node->type, (kind & 0xe0) == 0 || ((kind & 0xf8) == 0x40)))) ||
             ((((operand->type & 0xe0) == 0 || (size_class == 0x40)) &&
              ((cdata->uses->node->type & 0xf8) == 0x28)))) goto LAB_00407f8c;
        }
        if (g_options->cpu == 4) {
          size_class = operand->type;
          if ((((size_class & 0xe0) == 0x20) &&
              ((kind = cdata->uses->node->type, (kind & 0xe0) == 0 || ((kind & 0xf8) == 0x40)))) ||
             (((((size_class & 0xe0) == 0 || ((size_class & 0xf8) == 0x40)) &&
               ((cdata->uses->node->type & 0xe0) == 0x20)) ||
              ((((size_class & 0xf8) == 0x28 && ((cdata->uses->node->type & 0xf8) == 0x30)) ||
               (((size_class & 0xf8) == 0x30 && ((cdata->uses->node->type & 0xf8) == 0x28))))))))
          goto LAB_00407f8c;
        }
      }
      use = regalloc_alloc(0x14);
      use->block = block;
      use->node = node;
      use->next = cdata->uses;
      cdata->uses = use;
      goto LAB_00407fbf;
    }
LAB_00407f8c:
    cdata = cdata->hash_next;
  } while( true );
}



