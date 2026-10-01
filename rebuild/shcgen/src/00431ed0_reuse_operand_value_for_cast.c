#include "decls.h"
#include "imports.h"

// entry: 00431ed0
// name : reuse_operand_value_for_cast
// size : 191
// sig  : int reuse_operand_value_for_cast(gen_node * node)


int __cdecl reuse_operand_value_for_cast(gen_node *node)

{
  int reused;
  ea *src;
  byte kind;
  gen_node *child;
  node_desc *child_desc;
  uchar *flags;
  
  reused = 0;
  child = node->child;
  if ((child->desc->flags2 & 0x20) != 0) {
    if (child->desc->opnd_class == '\x02') {
      flags = &node->desc->flags3;
      *flags = *flags | 8;
      if (node->desc->tmpl == (tmpl_header *)0x0) {
        flags = &node->desc->flags3;
        *flags = *flags | 0x80;
      }
    }
    node->desc->busy_regs = child->desc->busy_regs;
    node->desc->fbusy_regs = child->desc->fbusy_regs;
    node->desc->frame_top = child->desc->frame_top;
    kind = 0;
    child_desc = child->desc;
    src = child_desc->mem_ea;
    if (src != (ea *)0x0) {
      kind = src->type & 0x1f;
    }
    if (((kind == 0) && (src = &child_desc->dest, (src->type & 0x1f) == 0)) &&
       (src = &g_ea_pop, (child_desc->flags2 & 8) == 0)) {
      src = &child_desc->value;
    }
    copy_ea_into(&node->desc->value,src);
    node->desc->opnd_class = child->desc->opnd_class;
    flags = &node->desc->flags3;
    *flags = *flags | 0x80;
    flags = &node->desc->flags3;
    *flags = *flags | 8;
    reused = 1;
  }
  return reused;
}



