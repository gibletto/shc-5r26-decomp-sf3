#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_const_data_list
#define g_const_data_list (*(const_data * *)(g_sd + 0x16498))
#undef g_options
#define g_options (*(option_record * *)(g_sd + 0x1e714))
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 00408020
// name : record_register_variable_use
// size : 456
// sig  : void record_register_variable_use(il_node * node, bblock * block)


int __cdecl record_register_variable_use(il_node *node,bblock *block)

{
  short bucket;
  uint arg_index;
  const_data *obj;
  const_use *use;
  byte size_class;
  const_data *prev_item;
  ushort leafno;
  bool on_stack;
  char sclass;
  ushort sign;
  byte type;
  
  arg_index = parameter_register_index(node);
  type = node->type;
  size_class = type & 0xf8;
  if (((size_class == 0x30) || (g_options->cpu != 2)) || (g_options->fpu_mode != '\x03')) {
    if (g_options->cpu == 4) {
      if ((type & 0xe0) == 0x20) goto joined_r0x00408096;
    }
    else if ((((type & 0xe0) != 0) && (size_class != 0x40)) && (size_class != 0x28)) {
      on_stack = false;
      goto LAB_004080c5;
    }
joined_r0x004080c1:
    on_stack = true;
    if ((int)arg_index < 5) goto LAB_004080c5;
  }
  else {
    if (size_class != 0x28) goto joined_r0x004080c1;
joined_r0x00408096:
    on_stack = true;
    if ((int)arg_index < g_float_arg_reg_limit) goto LAB_004080c5;
  }
  on_stack = false;
LAB_004080c5:
  if ((((node->symx < 0) || (sclass = g_symtab[node->symx].sclass, sclass == '\x05')) ||
      ((sclass == '\x06' ||
       ((on_stack &&
        (((sclass == '\a' || (sclass == '\b')) && ((g_leaf_table[node->nleaf].flag & 0xc) == 0))))))
      )) && (((((type & 0xe0) == 0 || (size_class == 0x40)) ||
              ((g_options->cpu == 4 && (size_class == 0x30)))) || (size_class == 0x28)))) {
    leafno = node->nleaf;
    sign = (short)leafno >> 0xf;
    bucket = ((leafno ^ sign) - sign & 0x7f ^ sign) - sign;
    obj = g_mem_object_lists[bucket];
    if (obj != (const_data *)0x0) {
      do {
        prev_item = obj;
        if (prev_item->value == (int)(short)leafno) {
          use = regalloc_alloc(0x14);
          use->node = node;
          use->block = block;
          use->next = prev_item->uses;
          prev_item->uses = use;
          obj = prev_item;
          break;
        }
        obj = prev_item->hash_next;
      } while (obj != (const_data *)0x0);
    }
    if (obj == (const_data *)0x0) {
      obj = regalloc_alloc(0x1c);
      obj->next = g_const_data_list;
      g_const_data_list = obj;
      if (g_mem_object_lists[bucket] == (const_data *)0x0) {
        g_mem_object_lists[bucket] = obj;
      }
      else {
        prev_item->hash_next = obj;
      }
      use = regalloc_alloc(0x14);
      use->node = node;
      use->block = block;
      obj->uses = use;
      obj->value = (int)node->nleaf;
    }
  }
  return;
}



