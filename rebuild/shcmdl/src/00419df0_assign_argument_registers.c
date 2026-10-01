#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_call_list
#define g_call_list (*(node_cell * *)(g_sd + 0x164b0))
#undef g_lreg_list
#define g_lreg_list (*(lreg * *)(g_sd + 0x16264))
#undef g_options
#define g_options (*(option_record * *)(g_sd + 0x1e714))
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 00419df0
// name : assign_argument_registers
// size : 592
// sig  : void assign_argument_registers(void)


int __cdecl assign_argument_registers(void)

{
  short sVar1;
  ushort pp;
  int iVar2;
  undefined2 extraout_var = 0;
  uint regno;
  byte kind;
  char *name_p;
  char *builtin_p;
  bool bVar3;
  lreg *lr;
  il_node *arg;
  node_cell *call;
  lreg *cur_lr;
  ushort *flags;
  il_op op;
  void *ref;
  dutbl *web;
  
  for (cur_lr = g_lreg_list; call = g_call_list, cur_lr != (lreg *)0x0; cur_lr = cur_lr->next) {
    if (cur_lr->set == 1) {
      for (ref = cur_lr->chain; ref != (void *)0x0; ref = *(void **)((int)ref + 8)) {
        *(lreg **)((int)ref + 0x18) = cur_lr;
      }
    }
  }
  do {
    if (call == (node_cell *)0x0) {
      resolve_argument_register_clashes();
      return;
    }
    arg = call->node->child;
    if ((arg->op == IL_ID) && (sVar1 = arg->symx, -1 < sVar1)) {
      iVar2 = is_mac_builtin_name(g_symtab[sVar1].name);
      if (iVar2 == 0) {
        iVar2 = 0xf;
        bVar3 = true;
        name_p = g_symtab[call->node->child->symx].name;
        builtin_p = s__builtin_trapa_004340b4;
        do {
          if (iVar2 == 0) break;
          iVar2 = iVar2 + -1;
          bVar3 = *name_p == *builtin_p;
          name_p = name_p + 1;
          builtin_p = builtin_p + 1;
        } while (bVar3);
        if (!bVar3) goto LAB_00419e9c;
      }
    }
    else {
LAB_00419e9c:
      arg = call->node->child->next->child;
      op = arg->op;
      while (op != IL_E_ARG) {
        if ((((arg->op == IL_ID) && (arg->cmnexp != (il_node *)0x0)) &&
            (web = arg->cmnexp->duptr, web != (dutbl *)0x0)) &&
           (((arg->flag & 0x100) != 0 && (cur_lr = web->lreg, cur_lr != (lreg *)0x0)))) {
          if (cur_lr->set == 1) {
            lr = cur_lr;
            pp = statement_pp(arg);
            iVar2 = lreg_ref_in_statement(arg,CONCAT22(extraout_var,pp),lr);
            if (iVar2 != 0) goto LAB_0041a020;
          }
          if (((cur_lr != (lreg *)0x0) && (iVar2 = lreg_conflicts_with_call(cur_lr), iVar2 == 0)) &&
             (cur_lr->bind == (lreg *)0x0)) {
            regno = argument_register_index(arg);
            sVar1 = g_options->cpu;
            if (sVar1 == 4) {
              if ((arg->type & 0xe0) == 0x20) {
                bVar3 = true;
                if ((int)regno <= g_float_arg_regs) {
LAB_00419f6d:
                  bVar3 = false;
                }
              }
              else {
                bVar3 = true;
                if ((int)regno < 5) goto LAB_00419f6d;
              }
              if (!bVar3) {
LAB_00419fb4:
                if (((sVar1 == 2) && (g_options->fpu_mode == '\x03')) &&
                   (kind = arg->type & 0xf8, kind != 0x30)) {
                  if (kind == 0x28) {
                    bVar3 = true;
                    if ((int)regno <= g_float_arg_regs) {
LAB_00419fef:
                      bVar3 = false;
                    }
                  }
                  else {
                    bVar3 = true;
                    if ((int)regno < 5) goto LAB_00419fef;
                  }
                  if (bVar3) goto LAB_0041a020;
                }
                if (cur_lr->set == 1) {
                  flags = (ushort *)(*(int *)((int)cur_lr->chain + 0x10) + 0x5e);
                  *flags = *flags | 0x8000;
                }
                else if (cur_lr->set == 0) {
                  flags = (ushort *)(*(int *)(*(int *)((int)cur_lr->chain + 8) + 8) + 0x5e);
                  *flags = *flags | 0x8000;
                }
                cur_lr->pregno = (short)regno;
              }
            }
            else if (((arg->type & 0xf8) != 0x30) &&
                    (((sVar1 == 4 || ((arg->type & 0xf8) == 0x30)) ||
                     (((sVar1 == 2 && (g_options->fpu_mode == '\x03')) || ((int)regno < 5))))))
            goto LAB_00419fb4;
          }
        }
LAB_0041a020:
        arg = arg->next;
        op = arg->op;
      }
    }
    call = call->next;
  } while( true );
}



