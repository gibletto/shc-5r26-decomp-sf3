#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_options
#define g_options (*(option_record * *)(g_sd + 0x1e714))
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 0041a650
// name : resolve_argument_register_clashes
// size : 873
// sig  : void resolve_argument_register_clashes(void)


int __cdecl resolve_argument_register_clashes(void)

{
  byte kind;
  uint param_regno;
  int conflict;
  short *other;
  il_node *id;
  il_node *own_node;
  lreg **slot;
  undefined4 *clash;
  short clash_set;
  bool in_reg;
  lreg *lr;
  
  slot = g_lreg_table + 1;
  id = own_node;
  do {
    lr = *slot;
    if (lr == (lreg *)0x0) {
      return;
    }
    if (lr->pregno != 0) {
      for (clash = lr->clashed; clash != (undefined4 *)0x0; clash = (undefined4 *)*clash) {
        other = (short *)clash[1];
        clash_set = other[1];
        if (clash_set == 1) {
          id = *(il_node **)(*(int *)(other + 0x10) + 0x10);
        }
        else if (clash_set == 0) {
          id = *(il_node **)(*(int *)(*(int *)(other + 0x10) + 8) + 8);
        }
        if ((id->op != IL_CONST) && (id->op != IL_ID)) {
          id = id->child;
        }
        if ((id->symx < 1) ||
           ((g_symtab[id->symx].sclass != '\a' && (g_symtab[id->symx].sclass != '\b')))) {
          lr = *slot;
          if (lr->pregno != *other) {
            if ((g_options->cpu == 4) && (*other != 0)) {
              own_node = lreg_node(lr);
              if ((own_node->op != IL_CONST) && (own_node->op != IL_ID)) {
                own_node = own_node->child;
              }
              if ((((own_node->type & 0xf8) == 0x30) && ((id->type & 0xf8) == 0x28)) &&
                 ((int)(*slot)->pregno - (int)*(short *)clash[1] == -1)) {
                *(short *)clash[1] = 0;
              }
              if ((((own_node->type & 0xf8) == 0x28) && ((id->type & 0xf8) == 0x30)) &&
                 (other = (short *)clash[1], (int)(*slot)->pregno - (int)*other == 1))
              goto LAB_0041a987;
            }
            goto LAB_0041a98c;
          }
          if (((g_options->cpu == 2) && (g_options->fpu_mode == '\x03')) || (g_options->cpu == 4)) {
            if (lr->set == 1) {
              own_node = *(il_node **)((int)lr->chain + 0x10);
            }
            else if (lr->set == 0) {
              own_node = *(il_node **)(*(int *)((int)lr->chain + 8) + 8);
            }
            if (((clash_set == 1) &&
                ((*(byte *)(*(int *)(*(int *)(other + 0x10) + 0x10) + 3) & 0xe0) == 0x20)) ||
               ((clash_set == 0 &&
                ((*(byte *)(*(int *)(*(int *)(*(int *)(other + 0x10) + 8) + 8) + 3) & 0xe0) == 0x20)
                ))) {
              if ((own_node->type & 0xe0) == 0x20) goto LAB_0041a987;
            }
            else if ((own_node->type & 0xe0) != 0x20) goto LAB_0041a987;
          }
          else {
LAB_0041a987:
            *other = 0;
          }
        }
        else {
          param_regno = parameter_register_index(id);
          own_node = lreg_node(*slot);
          if ((own_node->op != IL_CONST) && (own_node->op != IL_ID)) {
            own_node = own_node->child;
          }
          if (g_options->cpu == 4) {
            kind = own_node->type & 0xe0;
            if (((kind == 0x20) && ((id->type & 0xe0) == 0)) ||
               ((kind == 0 && ((id->type & 0xe0) == 0x20)))) goto LAB_0041a98c;
            kind = id->type & 0xe0;
            if (kind == 0x20) {
              in_reg = true;
              if (g_float_arg_reg_limit <= (int)param_regno) {
LAB_0041a775:
                in_reg = false;
              }
            }
            else {
              in_reg = true;
              if (4 < (int)param_regno) goto LAB_0041a775;
            }
            if (((kind != 0x20) && (kind != 0)) && ((id->type & 0xf8) != 0x40)) {
              in_reg = false;
            }
          }
          else if ((g_options->cpu == 2) && (g_options->fpu_mode == '\x03')) {
            kind = own_node->type & 0xe0;
            if (((kind == 0x20) && ((id->type & 0xe0) == 0)) ||
               ((kind == 0 && ((id->type & 0xe0) == 0x20)))) goto LAB_0041a98c;
            kind = id->type & 0xf8;
            if (kind == 0x28) {
              in_reg = true;
              if (g_float_arg_reg_limit <= (int)param_regno) {
LAB_0041a7f3:
                in_reg = false;
              }
            }
            else {
              in_reg = true;
              if (4 < (int)param_regno) goto LAB_0041a7f3;
            }
            if ((((id->type & 0xe0) != 0) && (kind != 0x40)) && (kind != 0x28)) {
              in_reg = false;
            }
          }
          else if (((id->type & 0xe0) == 0) ||
                  ((kind = id->type & 0xf8, kind == 0x40 || (kind == 0x28)))) {
            in_reg = true;
            if (4 < (int)param_regno) {
              in_reg = false;
            }
          }
          else {
            in_reg = false;
          }
          if ((in_reg) && (conflict = lreg_conflicts_with_call((lreg *)clash[1]), conflict == 0)) {
            (*slot)->pregno = 0;
          }
        }
LAB_0041a98c: ;
      }
    }
    slot = slot + 1;
    if ((lreg **)SD(0x00448260) < slot) {
      return;
    }
  } while( true );
}



