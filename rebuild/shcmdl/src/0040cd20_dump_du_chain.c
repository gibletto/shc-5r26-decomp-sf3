#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_str_temp_nul
#define g_str_temp_nul (*(char *)(g_sd + 0x3294))
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 0040cd20
// name : dump_du_chain
// size : 367
// sig  : void dump_du_chain(il_node * node)


int __cdecl dump_du_chain(il_node *node)

{
  unsigned char _frec_14[20];
#define row (*(int *)(_frec_14 + 0))
#define name_buf (*(undefined4 *)(_frec_14 + 4))
#define local_c (*(char (*)[12])(_frec_14 + 8))
  byte len;
  undefined1 *puVar1;
  undefined1 *arg_blkno;
  undefined1 *arg_leaf;
  undefined4 *arg_name;
  char *fmt;
  int kind;
  node_list *link;
  il_node *linked;
  short nleaf;
  
  row = 0;
  for (link = node->duptr->links; link != (node_list *)0x0; link = link->next) {
    if (node->op == IL_ID) {
      nleaf = node->nleaf;
    }
    else {
      nleaf = node->child->nleaf;
    }
    puVar1 = (undefined1 *)(int)g_leaf_table[nleaf].symno;
    if ((int)puVar1 < 1) {
      name_buf = g_str_temp;
      local_c[0] = g_str_temp_nul;
      _sprintf(local_c,&g_str_percent_d,-(int)puVar1);
    }
    else {
      len = g_symtab[(int)puVar1].name_len;
      if (0xe < len) {
        len = 0xf;
      }
      stock_strncpy((char *)&name_buf,g_symtab[(int)puVar1].name,(uint)len);
      local_c[len - 4] = '\0';
    }
    if (row == 0) {
      FID_conflict__wprintf(s______________________DU_CHAIN_TA_00435254);
      FID_conflict__wprintf(s_NODE___s_00435248,(&g_op_names_upper)[(char)node->op]);
      FID_conflict__wprintf(s__________________________________0043520c);
      FID_conflict__wprintf(s___No__b_No__id_name__symno_flag__004351d0);
      FID_conflict__wprintf(s__________________________________0043520c);
      arg_name = &name_buf;
      linked = link->node;
      kind = node->duptr->kind;
      arg_leaf = (undefined1 *)(int)node->nleaf;
      arg_blkno = (undefined1 *)(int)node->duptr->block->number;
      fmt = s___4d__4d___15s__5d__04X__010lX___004351a8;
    }
    else {
      linked = link->node;
      kind = node->duptr->kind;
      puVar1 = &g_str_empty;
      arg_name = (undefined4 *)&g_str_empty;
      arg_blkno = &g_str_empty;
      arg_leaf = &g_str_empty;
      fmt = s___4s__4s___15s__5s__04X__010lX___00435180;
    }
    FID_conflict__wprintf(fmt,arg_leaf,arg_blkno,arg_name,puVar1,kind,linked,node);
    row = row + 1;
    FID_conflict__wprintf(s__________________________________0043520c);
  }
  return;
#undef row
#undef name_buf
#undef local_c
}



