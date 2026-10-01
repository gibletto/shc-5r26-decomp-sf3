#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_call_list
#define g_call_list (*(node_cell * *)(g_sd + 0x164b0))
#undef g_options
#define g_options (*(option_record * *)(g_sd + 0x1e714))
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 0041a2a0
// name : lreg_conflicts_with_call
// size : 938
// sig  : int lreg_conflicts_with_call(lreg * lr)


int __cdecl lreg_conflicts_with_call(lreg *lr)

{
  il_node *node;
  ushort pp;
  ushort ref_pp;
  int iVar1;
  uint arg_regno;
  uint param_regno;
  undefined2 extraout_var = 0;
  undefined2 extraout_var_00 = 0;
  undefined2 extraout_var_01 = 0;
  byte kind;
  char *name_p;
  char *builtin_p;
  bool bVar2;
  uint first_regno;
  il_node *arg;
  bool arg_in_reg;
  lreg *arg_lr;
  node_cell *call;
  bool conflict;
  il_op op;
  bool param_in_reg;
  undefined4 *range;
  void *ref;
  bool seen_call;
  short symx;
  dutbl *web;
  
  seen_call = false;
  conflict = false;
  call = g_call_list;
  do {
    if (call == (node_cell *)0x0) {
      return 0;
    }
    for (range = lr->life; range != (undefined4 *)0x0; range = (undefined4 *)*range) {
      pp = call->node->pp;
      if ((*(ushort *)(range[1] + 8) <= pp) && (pp <= *(ushort *)(range[1] + 10))) {
        arg = call->node->child;
        if ((arg->op == IL_ID) && (symx = arg->symx, -1 < symx)) {
          iVar1 = is_mac_builtin_name(g_symtab[symx].name);
          bVar2 = iVar1 == 0;
          if (!bVar2) {
            return 1;
          }
          iVar1 = 0xf;
          name_p = g_symtab[call->node->child->symx].name;
          builtin_p = s__builtin_trapa_004340b4;
          do {
            if (iVar1 == 0) break;
            iVar1 = iVar1 + -1;
            bVar2 = *name_p == *builtin_p;
            name_p = name_p + 1;
            builtin_p = builtin_p + 1;
          } while (bVar2);
          if (bVar2) {
            return 1;
          }
        }
        bVar2 = false;
        arg = call->node->child->next->child;
        op = arg->op;
        while (op != IL_E_ARG) {
          if ((((arg->op == IL_ID) && (arg->cmnexp != (il_node *)0x0)) &&
              (web = arg->cmnexp->duptr, web != (dutbl *)0x0)) && (arg_lr = web->lreg, arg_lr == lr)
             ) {
            bVar2 = true;
            if ((arg->symx < 1) ||
               ((g_symtab[arg->symx].sclass != '\a' && (g_symtab[arg->symx].sclass != '\b')))) {
              if (seen_call) {
                arg_regno = argument_register_index(arg);
                if (arg_regno != first_regno) {
                  conflict = true;
                }
              }
              else {
                first_regno = argument_register_index(arg);
              }
            }
            else {
              arg_regno = argument_register_index(arg);
              param_regno = parameter_register_index(arg);
              if (param_regno != arg_regno) {
                if (g_options->cpu == 4) {
                  kind = arg->type & 0xe0;
                  if (kind == 0x20) {
                    arg_in_reg = true;
                    if (g_float_arg_reg_limit <= (int)arg_regno) {
LAB_0041a43e:
                      arg_in_reg = false;
                    }
                  }
                  else {
                    arg_in_reg = true;
                    if (4 < (int)arg_regno) goto LAB_0041a43e;
                  }
                  if (kind == 0x20) {
                    param_in_reg = true;
                    if (g_float_arg_reg_limit <= (int)param_regno) {
LAB_0041a51e:
                      param_in_reg = false;
                    }
                  }
                  else {
joined_r0x0041a51c:
                    param_in_reg = true;
                    if (4 < (int)param_regno) goto LAB_0041a51e;
                  }
                }
                else if ((g_options->cpu == 2) && (g_options->fpu_mode == '\x03')) {
                  kind = arg->type & 0xf8;
                  if (kind == 0x28) {
                    arg_in_reg = true;
                    if (g_float_arg_reg_limit <= (int)arg_regno) {
LAB_0041a4a4:
                      arg_in_reg = false;
                    }
                  }
                  else {
                    arg_in_reg = true;
                    if (4 < (int)arg_regno) goto LAB_0041a4a4;
                  }
                  if (kind == 0x28) {
                    param_in_reg = true;
                    if (g_float_arg_reg_limit <= (int)param_regno) {
LAB_0041a4c4:
                      param_in_reg = false;
                    }
                  }
                  else {
                    param_in_reg = true;
                    if (4 < (int)param_regno) goto LAB_0041a4c4;
                  }
                  if (kind == 0x30) {
                    arg_in_reg = false;
                    param_in_reg = false;
                  }
                }
                else {
                  kind = arg->type;
                  if (((kind & 0xe0) == 0) || (((kind & 0xf8) == 0x40 || ((kind & 0xf8) == 0x28))))
                  {
                    arg_in_reg = true;
                    if (4 < (int)arg_regno) {
                      arg_in_reg = false;
                    }
                  }
                  else {
                    arg_in_reg = false;
                  }
                  if ((((kind & 0xe0) == 0) || ((kind & 0xf8) == 0x40)) || ((kind & 0xf8) == 0x28))
                  goto joined_r0x0041a51c;
                  param_in_reg = false;
                }
                if ((arg_in_reg) || (param_in_reg)) {
                  for (ref = lr->chain; ref != (void *)0x0; ref = *(void **)((int)ref + 0x14)) {
                    if (**(short **)((int)ref + 0xc) == 1) {
                      conflict = true;
                    }
                  }
                }
              }
              pp = statement_pp(arg);
              for (node = arg->cmnexp; node != (il_node *)0x0; node = node->refchn) {
                if ((node != arg) &&
                   (ref_pp = statement_pp(node),
                   CONCAT22(extraout_var_00,ref_pp) == CONCAT22(extraout_var,pp))) {
                  conflict = true;
                }
              }
            }
            if ((arg->flag & 0x100) == 0) {
              conflict = true;
            }
            if (arg_lr->set == 1) {
              pp = statement_pp(arg);
              iVar1 = lreg_ref_in_statement(arg,CONCAT22(extraout_var_01,pp),arg_lr);
              if (iVar1 != 0) {
                conflict = true;
              }
            }
          }
          arg = arg->next;
          op = arg->op;
        }
        if ((conflict) || (!bVar2)) {
          return 1;
        }
        seen_call = true;
      }
    }
    call = call->next;
  } while( true );
}



