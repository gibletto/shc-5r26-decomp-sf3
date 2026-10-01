#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_noalloc_leaf_regs
#define g_noalloc_leaf_regs (*(int * *)(g_sd + 0x16488))
#undef g_reg_file
#define g_reg_file (*(FILE * *)(g_sd + 0x1e72c))
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 00414bc0
// name : assign_registers_without_allocation
// size : 276
// sig  : void assign_registers_without_allocation(il_node * node)


int __cdecl assign_registers_without_allocation(il_node *node)

{
  unsigned char _frec_8[8];
#define local_8 (*(int * *)(_frec_8 + 0))
#define local_4 (*(short *)(_frec_8 + 4))
  int *entry;
  int *last;
  int *head;
  il_node *sub;
  
  last = local_8;
  for (sub = node->child; sub != (il_node *)0x0; sub = sub->next) {
    local_8 = last;
    assign_registers_without_allocation(sub);
    last = local_8;
  }
  if ((node->op == IL_ID) &&
     (((node->symx < 0 || (g_symtab[node->symx].sclass == '\x05')) ||
      (g_symtab[node->symx].sclass == '\x06')))) {
    entry = g_noalloc_leaf_regs;
    if (g_noalloc_leaf_regs != (int *)0x0) {
      do {
        last = entry;
        entry = last;
        if (*last == (int)node->nleaf) break;
        entry = (int *)last[3];
      } while (entry != (int *)0x0);
    }
    head = g_noalloc_leaf_regs;
    if (entry == (int *)0x0) {
      entry = regalloc_alloc(0x10);
      *entry = (int)node->nleaf;
      entry[1] = g_lreg_count;
      g_lreg_count = g_lreg_count + 1;
      entry[2] = g_int_reg_count;
      if (g_int_reg_count == 4) {
        g_int_reg_count = -1;
      }
      else {
        g_int_reg_count = g_int_reg_count + -1;
      }
      local_4 = (short)(char)node->type;
      local_8 = (int *)CONCAT22((short)entry[2],(short)entry[1]);
      write_bytes(g_reg_file,(char *)&local_8,6);
      head = entry;
      if (g_noalloc_leaf_regs != (int *)0x0) {
        last[3] = (int)entry;
        head = g_noalloc_leaf_regs;
      }
    }
    g_noalloc_leaf_regs = head;
    node->lreg = (short)entry[1];
  }
  return;
#undef local_8
#undef local_4
}



