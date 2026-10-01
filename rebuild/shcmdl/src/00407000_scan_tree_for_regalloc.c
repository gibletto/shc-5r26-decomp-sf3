#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_call_list
#define g_call_list (*(node_cell * *)(g_sd + 0x164b0))
#undef g_call_list_tail
#define g_call_list_tail (*(node_cell * *)(g_sd + 0x51e4))
#undef g_debug_flags
#define g_debug_flags (*(unsigned char *)(g_sd + 0x267c0))
#undef g_func_node
#define g_func_node (*(il_node * *)(g_sd + 0x1e738))
#undef g_options
#define g_options (*(option_record * *)(g_sd + 0x1e714))
#undef g_regalloc_block
#define g_regalloc_block (*(bblock * *)(g_sd + 0x1648c))
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 00407000
// name : scan_tree_for_regalloc
// size : 1000
// sig  : void scan_tree_for_regalloc(bblock * block, il_node * node, int with_siblings)


int __cdecl scan_tree_for_regalloc(bblock *block,il_node *node,int with_siblings)

{
  unsigned char _frec_40[64];
#define live_set (*(uint (*)[16])(_frec_40 + 0))
  uchar any;
  int iVar1;
  node_cell *cell;
  undefined3 extraout_var = 0;
  il_node *ref;
  byte type_class;
  char *s1;
  char *s2;
  bool equal;
  dutbl *du;
  ushort flag;
  byte *flag_hi;
  short symx;
  
  do {
    if (node == (il_node *)0x0) {
      return;
    }
    scan_tree_for_regalloc(block,node->child,1);
    node->pp = (ushort)g_pp_count;
    g_pp_count = g_pp_count + 1;
    if ((node->op == IL_ID) &&
       (((g_leaf_table[node->nleaf].flag & 0xe) != 0 ||
        ((node->symx < 0 && ((node->type & 2) != 0)))))) {
      record_register_variable_use(node,block);
    }
    else {
      if (node->op == IL_CALL) {
        flag_hi = (byte *)((int)&g_func_node->flag + 1);
        *flag_hi = *flag_hi | 4;
        if ((((node->child->op == IL_ID) && (symx = node->child->symx, -1 < symx)) &&
            (iVar1 = is_builtin_name(g_symtab[symx].name), iVar1 != 0)) &&
           (iVar1 = is_mac_builtin_name(g_symtab[node->child->symx].name), iVar1 == 0)) {
          iVar1 = 0x10;
          equal = true;
          s1 = g_symtab[node->child->symx].name;
          s2 = s__builtin_strcmp_0043426c;
          do {
            if (iVar1 == 0) break;
            iVar1 = iVar1 + -1;
            equal = *s1 == *s2;
            s1 = s1 + 1;
            s2 = s2 + 1;
          } while (equal);
          if (!equal) {
            iVar1 = 0x13;
            s1 = g_symtab[node->child->symx].name;
            s2 = s__builtin_trapa_svc_004340a0;
            do {
              if (iVar1 == 0) break;
              iVar1 = iVar1 + -1;
              equal = *s1 == *s2;
              s1 = s1 + 1;
              s2 = s2 + 1;
            } while (equal);
            if (!equal) {
              iVar1 = 0xf;
              s1 = g_symtab[node->child->symx].name;
              s2 = s__builtin_trapa_004340b4;
              do {
                if (iVar1 == 0) break;
                iVar1 = iVar1 + -1;
                equal = *s1 == *s2;
                s1 = s1 + 1;
                s2 = s2 + 1;
              } while (equal);
              if (!equal) goto LAB_004071ac;
            }
          }
        }
        *(byte *)&block->flag = (byte)block->flag | 2;
        if (g_call_list == (node_cell *)0x0) {
          g_call_list_tail = regalloc_alloc(8);
          g_call_list = g_call_list_tail;
        }
        else {
          cell = regalloc_alloc(8);
          g_call_list_tail->next = cell;
          g_call_list_tail = g_call_list_tail->next;
        }
        g_call_list_tail->node = node;
      }
LAB_004071ac:
      flag = node->flag;
      if (((flag & 0x80) != 0) && ((flag & 0x100) == 0)) {
        if ((g_leaf_table[node->nleaf].use == (uint *)0x0) || (g_regalloc_block->out == (uint *)0x0)
           ) {
          node->flag = flag | 0x100;
        }
        else {
          clear_bytes((char *)live_set,0x40);
          bitset_and(live_set,g_leaf_table[node->nleaf].use,g_regalloc_block->out,'\x10');
          any = any_bit_set(live_set,0x10);
          if (CONCAT31(extraout_var,any) == 0) {
            flag_hi = (byte *)((int)&node->flag + 1);
            *flag_hi = *flag_hi | 1;
          }
        }
      }
      du = node->duptr;
      if (du != (dutbl *)0x0) {
        if (du->kind == 1) {
          if (((node->flag & 4) == 0) && (iVar1 = mark_web_allocatable(node), iVar1 != 0)) {
            if (((*(unsigned char *)((char *)&g_debug_flags + 3)) & 2) != 0) {
              dump_web_chain(node->duptr,s_mkweb_after_web_00434488);
            }
            join_related_webs(node);
            new_register_candidate(node->duptr,1);
          }
        }
        else if (((node->flag & 4) == 0) && (du->links == (node_list *)0x0)) {
          if (node->op == IL_ID) {
            if (((((node->type & 0xe0) == 0) || (type_class = node->type & 0xf8, type_class == 0x40)
                 ) || ((g_options->cpu == 4 && (type_class == 0x30)))) ||
               (ref = node, type_class == 0x28)) {
              symx = node->symx;
              if (((symx < 0) || (g_symtab[symx].sclass == '\x05')) ||
                 (g_symtab[symx].sclass == '\x06')) {
                ref = node;
                if ((g_leaf_table[node->nleaf].flag & 0x20) == 0) {
                  if (symx < 0) {
                    fatal_error(0x107d);
                  }
                  if ((g_options->warnings == '\x01') && (g_symtab[node->symx].name != (char *)0x0))
                  {
                    report_message(0xb,node,g_symtab[node->symx].name);
                  }
                  g_leaf_table[node->nleaf].flag = g_leaf_table[node->nleaf].flag | 0x20;
                }
                for (; ref != (il_node *)0x0; ref = ref->refchn) {
                  ref->lreg = -0x8000;
                }
              }
              goto LAB_0040738c;
            }
          }
          else {
            ref = node->child;
          }
          record_register_variable_use(ref,block);
        }
      }
LAB_0040738c:
      collect_register_candidate(node);
    }
    if ((((g_options->cpu == 2) && (g_options->fpu_mode == '\x03')) || (g_options->cpu == 4)) &&
       (((node->type & 0xf8) == 0x28 && ((node->fr0set & 1U) == 0)))) {
      mark_fr0_fmac_uses(node);
    }
    if (with_siblings == 0) {
      return;
    }
    node = node->next;
  } while( true );
#undef live_set
}



