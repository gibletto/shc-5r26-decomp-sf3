#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_options
#define g_options (*(option_record * *)(g_sd + 0x1e714))
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 0041b400
// name : assign_float_registers
// size : 1196
// sig  : int assign_float_registers(int next_mem_id, char func_attr_08, char func_attr_1c)


int __cdecl assign_float_registers(int next_mem_id,char func_attr_08,char func_attr_1c)

{
  lreg *plVar1;
  byte own_kind;
  int iVar2;
  il_node *piVar3;
  il_node *own_node;
  int limit;
  uint uVar4;
  uint uVar5;
  lreg **slot;
  int *clash;
  int i;
  short *other;
  char sclass;
  short set_kind;
  
  uVar5 = 1;
  if (0 < g_float_reg_count) {
    do {
      if ((g_float_arg_reg_limit <= (int)uVar5) && (func_attr_1c == '\x10')) break;
      i = 1;
      if (0 < g_lreg_count) {
        slot = g_lreg_table;
        do {
          slot = slot + 1;
          plVar1 = *slot;
          set_kind = plVar1->set;
          if (((((set_kind != 3) &&
                (((g_options->cpu != 2 || (g_options->fpu_mode != '\x03')) ||
                 (((set_kind != 1 ||
                   ((*(byte *)(*(int *)((int)plVar1->chain + 0x10) + 3) & 0xf8) == 0x28)) &&
                  ((set_kind != 0 ||
                   ((*(short *)plVar1->chain == 0 &&
                    ((*(byte *)(*(int *)(*(int *)((int)plVar1->chain + 8) + 8) + 3) & 0xf8) == 0x28)
                    ))))))))) &&
               ((g_options->cpu != 4 ||
                (((set_kind != 1 ||
                  ((*(byte *)(*(int *)((int)plVar1->chain + 0x10) + 3) & 0xe0) == 0x20)) &&
                 ((set_kind != 0 ||
                  ((*(short *)plVar1->chain == 0 &&
                   ((*(byte *)(*(int *)(*(int *)((int)plVar1->chain + 8) + 8) + 3) & 0xe0) == 0x20))
                  )))))))) &&
              ((uVar4 = (int)uVar5 >> 0x1f, ((uVar5 ^ uVar4) - uVar4 & 1 ^ uVar4) != uVar4 ||
               (((set_kind != 1 ||
                 ((*(byte *)(*(int *)((int)plVar1->chain + 0x10) + 3) & 0xf8) != 0x30)) &&
                ((set_kind != 0 ||
                 ((*(short *)plVar1->chain != 0 ||
                  ((*(byte *)(*(int *)(*(int *)((int)plVar1->chain + 8) + 8) + 3) & 0xf8) != 0x30)))
                 ))))))) && (plVar1->pregno == 0)) {
            if ((int)uVar5 < g_float_arg_reg_limit) {
              iVar2 = lreg_conflicts_with_call(plVar1);
              if ((iVar2 == 0) && ((*slot)->bind == (lreg *)0x0)) {
                if ((int)uVar5 < g_float_arg_reg_limit) {
                  if ((*slot)->set == 1) {
                    piVar3 = *(il_node **)((int)(*slot)->chain + 0x10);
                    if (piVar3->op != IL_ID) {
                      piVar3 = piVar3->child;
                    }
                    if ((0 < piVar3->symx) &&
                       (((g_symtab[piVar3->symx].sclass == '\a' ||
                         (g_symtab[piVar3->symx].sclass == '\b')) &&
                        (uVar4 = parameter_register_index(piVar3), (int)uVar4 < (int)uVar5))))
                    goto LAB_0041b733;
                  }
                  goto LAB_0041b5be;
                }
                goto LAB_0041b5c6;
              }
            }
            else {
LAB_0041b5be:
              if (g_float_arg_reg_limit <= (int)uVar5) {
LAB_0041b5c6:
                if (((*slot)->priori < 3) ||
                   (((g_float_arg_reg_limit <= (int)uVar5 && (func_attr_08 != '\0')) &&
                    (iVar2 = lreg_spans_call(*slot), iVar2 != 0)))) goto LAB_0041b733;
              }
              clash = (*slot)->clashed;
              if (clash != (int *)0x0) {
                do {
                  if (g_options->cpu == 4) {
                    plVar1 = (lreg *)clash[1];
                    if ((plVar1->set != 0) || (*(short *)plVar1->chain == 0)) {
                      piVar3 = lreg_node(plVar1);
                      if ((int)*(short *)clash[1] == uVar5) {
                        if ((piVar3->type & 0xe0) == 0x20) break;
                      }
                      else if (*(short *)clash[1] != 0) {
                        own_node = lreg_node(*slot);
                        own_kind = own_node->type & 0xf8;
                        if ((((own_kind == 0x28) && ((piVar3->type & 0xf8) == 0x30)) &&
                            ((int)*(short *)clash[1] - uVar5 == -1)) ||
                           (((own_kind == 0x30 && ((piVar3->type & 0xf8) == 0x28)) &&
                            ((int)*(short *)clash[1] - uVar5 == 1)))) break;
                      }
                    }
                  }
                  else {
                    other = (short *)clash[1];
                    if (((int)*other == uVar5) &&
                       (((other[1] == 1 &&
                         ((*(byte *)(*(int *)(*(int *)(other + 0x10) + 0x10) + 3) & 0xf8) == 0x28))
                        || ((other[1] == 0 &&
                            ((**(short **)(other + 0x10) == 0 &&
                             ((*(byte *)(*(int *)(*(int *)(*(short **)(other + 0x10) + 4) + 8) + 3)
                              & 0xf8) == 0x28)))))))) break;
                  }
                  clash = (int *)*clash;
                } while (clash != (int *)0x0);
                if (clash != (int *)0x0) goto LAB_0041b733;
              }
              if ((((g_float_arg_reg_limit <= (int)uVar5) || ((*slot)->set != 1)) ||
                  ((*(byte *)(*(int *)((int)(*slot)->chain + 0x10) + 0x5f) & 0x80) == 0)) &&
                 ((plVar1 = *slot, plVar1->set != 0 ||
                  ((*(byte *)(*(int *)(*(int *)((int)plVar1->chain + 8) + 8) + 0x5f) & 0x80) == 0)))
                 ) {
                plVar1->pregno = (short)uVar5;
              }
            }
          }
LAB_0041b733:
          i = i + 1;
        } while (i <= g_lreg_count);
      }
      uVar5 = uVar5 + 1;
    } while ((int)uVar5 <= g_float_reg_count);
  }
  iVar2 = 1;
  if (0 < g_lreg_count) {
    slot = g_lreg_table;
    do {
      slot = slot + 1;
      plVar1 = *slot;
      set_kind = plVar1->set;
      if (((set_kind != 3) &&
          (((g_options->cpu != 2 || (g_options->fpu_mode != '\x03')) ||
           (((set_kind != 1 || ((*(byte *)(*(int *)((int)plVar1->chain + 0x10) + 3) & 0xf8) == 0x28)
             ) && ((set_kind != 0 ||
                   ((*(short *)plVar1->chain == 0 &&
                    ((*(byte *)(*(int *)(*(int *)((int)plVar1->chain + 8) + 8) + 3) & 0xf8) == 0x28)
                    ))))))))) &&
         (((g_options->cpu != 4 ||
           (((set_kind != 1 || ((*(byte *)(*(int *)((int)plVar1->chain + 0x10) + 3) & 0xe0) == 0x20)
             ) && ((set_kind != 0 ||
                   ((*(short *)plVar1->chain == 0 &&
                    ((*(byte *)(*(int *)(*(int *)((int)plVar1->chain + 8) + 8) + 3) & 0xe0) == 0x20)
                    ))))))) && ((plVar1->pregno == 0 && (set_kind == 1)))))) {
        piVar3 = *(il_node **)((int)plVar1->chain + 0x10);
        if (piVar3->op != IL_ID) {
          piVar3 = piVar3->child;
        }
        if (((piVar3->symx < 0) || (sclass = g_symtab[piVar3->symx].sclass, sclass == '\x05')) ||
           (sclass == '\x06')) {
          plVar1->pregno = (short)next_mem_id;
LAB_0041b891:
          next_mem_id = next_mem_id + -1;
        }
        else if ((sclass == '\a') || (sclass == '\b')) {
          uVar5 = parameter_register_index(piVar3);
          limit = 5;
          if ((piVar3->type & 0xe0) == 0x20) {
            limit = g_float_arg_reg_limit;
          }
          if ((int)uVar5 < limit) {
            (*slot)->pregno = (short)next_mem_id;
            goto LAB_0041b891;
          }
        }
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 <= g_lreg_count);
  }
  return next_mem_id;
}



