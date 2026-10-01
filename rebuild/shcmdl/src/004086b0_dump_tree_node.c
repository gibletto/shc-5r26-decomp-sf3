#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_debug_flags
#define g_debug_flags (*(unsigned char *)(g_sd + 0x267c0))
#undef g_op_names
#define g_op_names (*(unsigned char * *)(g_sd + 0x2668))
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 004086b0
// name : dump_tree_node
// size : 900
// sig  : void dump_tree_node(il_node * node, short depth)


int __cdecl dump_tree_node(il_node *node,short depth)

{
  short sVar1;
  il_op op;
  char *str;
  
  sVar1 = 0;
  if (0 < depth) {
    do {
      if ((&g_tree_dump_more)[sVar1] == 1) {
        str = &g_str_tree_bar;
      }
      else {
        str = &g_str_tree_space;
      }
      sVar1 = sVar1 + 1;
      FID_conflict__wprintf(str);
    } while (sVar1 < depth);
  }
  op = node->op;
  FID_conflict__wprintf(&g_str_plus_percent_s,(&g_op_names)[(char)op]);
  if (((('\x1f' < (char)op) && (op != IL_CALL)) && (op != IL_ARG)) &&
     ((op != IL_NULL && (op != IL_E_ARG)))) {
    dump_type(node->type);
  }
  if (g_dump_line_info != 0) {
    FID_conflict__wprintf
              (s_filn__d_line__u_listno__d_004349fc,(int)node->filn,(uint)node->line,
               (int)node->listno);
  }
  sVar1 = node->symx;
  if (sVar1 != 0) {
    if (((op == IL_SWITCH) || (op == IL_CLABEL)) || (op == IL_DLABEL)) {
      FID_conflict__wprintf(s_symx__d_004349f0,(int)sVar1);
    }
    else {
      if ((sVar1 < 1) || (str = g_symtab[sVar1].name, str == (char *)0x0)) {
        str = &g_str_empty;
      }
      FID_conflict__wprintf(s_symx__d___s___004349e0,(int)sVar1,str);
    }
  }
  if (node->lreg != 0) {
    FID_conflict__wprintf(s_lreg__d_004349d4,(int)node->lreg);
  }
  if (op == IL_ID) {
    if (0 < node->symx) {
      FID_conflict__wprintf(s_ms_leaf__d_004349c8,(int)g_symtab[node->symx].ms_leaf);
    }
    FID_conflict__wprintf(s_nleaf__d_004349bc,(int)node->nleaf);
  }
  if ((op == IL_QUALIFY) || (op == IL_B_QUALIFY)) {
    dump_qualify_fields(node);
  }
  if (op == IL_CONST) {
    dump_constant_value(node);
  }
  if (op == IL_ASM) {
    FID_conflict__wprintf(s_asmno__d_004349b0,node->val);
    FID_conflict__wprintf(s_asmsize__d_004349a4,node->val2);
  }
  if ((op == IL_CALL) && ((node->call_flags & 4) != 0)) {
    FID_conflict__wprintf(s_tail___0043499c);
  }
  if ((((op == IL_PRI) || (op == IL_PRD)) || (op == IL_POI)) || (op == IL_POD)) {
    FID_conflict__wprintf(s_size__d_00434990,node->val);
  }
  if (node->filn != 0) {
    FID_conflict__wprintf(s_nfiln__d_00434984,(int)node->filn);
  }
  if (node->line != 0) {
    FID_conflict__wprintf(s_nline__u_00434978,(uint)node->line);
  }
  if (((op == IL_BLOCK) || (op == IL_E_BLOCK)) && ((node->val & 1) != 0)) {
    FID_conflict__wprintf(s_blkflg_ON_0043496c);
  }
  if (node->pp != 0) {
    FID_conflict__wprintf(s_pp__d_00434964,(uint)node->pp);
  }
  if (node->expp != 0) {
    FID_conflict__wprintf(s_expp__d_00434958,(uint)node->expp);
  }
  if (node->refcnt != 0) {
    FID_conflict__wprintf(s_refcnt__d_0043494c,(uint)node->refcnt);
  }
  if ((node->flag != 0) &&
     (FID_conflict__wprintf(s_flag_0x_04x_0043493c,(int)(short)node->flag),
     (node->flag & 0x100) != 0)) {
    FID_conflict__wprintf(s__LASTUSE__00434930);
  }
  if (node->flag2 != 0) {
    FID_conflict__wprintf(s_flag2_0x_04x_00434920,(int)(short)node->flag2);
  }
  if (node->fr0set != '\0') {
    FID_conflict__wprintf(s_FR0set_00434918);
  }
  if (node->ivno != 0) {
    FID_conflict__wprintf(s_ivno__d_0043490c,(int)node->ivno);
  }
  if (node->invno != '\0') {
    FID_conflict__wprintf(s_invno__d_00434900,(int)node->invno);
  }
  if (((*(unsigned char *)((char *)&g_debug_flags + 3)) & 8) != 0) {
    FID_conflict__wprintf
              (s_c__08x_s__08x_f__08x_n__08x_004348d4,node,node->child,node->parent,node->next);
    if (node->cmnexp != (il_node *)0x0) {
      FID_conflict__wprintf(s_cmnexp__08x_004348c4,node->cmnexp);
    }
    if (node->refchn != (il_node *)0x0) {
      FID_conflict__wprintf(s_refchn__08x_004348b4,node->refchn);
    }
  }
  FID_conflict__wprintf(&g_str_newline);
  _fflush((FILE *)&stock_stdout);
  return;
}



