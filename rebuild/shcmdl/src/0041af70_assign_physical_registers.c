#include "decls.h"
#include "imports.h"
#include "regvarlog.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_func_node
#define g_func_node (*(il_node * *)(g_sd + 0x1e738))
#undef g_options
#define g_options (*(option_record * *)(g_sd + 0x1e714))
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 0041af70
// name : assign_physical_registers
// size : 1161
// sig  : void assign_physical_registers(void)


int __cdecl assign_physical_registers(void)

{
  byte func_attr_1c;
  int iVar1;
  uint param_regno;
  int *clash;
  byte func_attr_08;
  byte kind;
  il_node *id_node;
  int limit;
  int iVar2;
  lreg **slot;
  int i;
  bool assigned;
  lreg *lr;
  short *other;
  char sclass;
  short set_kind;
  
  iVar2 = 1;
  func_attr_1c = g_symtab[g_func_node->symx].attr & 0x1c;
  func_attr_08 = g_symtab[g_func_node->symx].attr & 8;
  if (0 < g_int_reg_count) {
    do {
      if ((4 < iVar2) && (func_attr_1c == 0x10)) {
        iVar2 = g_int_reg_count + 1;
        break;
      }
      i = 1;
      if (0 < g_lreg_count) {
        slot = g_lreg_table;
        do {
          slot = slot + 1;
          lr = *slot;
          set_kind = lr->set;
          if ((set_kind != 3) &&
             ((((g_options->cpu != 2 || (g_options->fpu_mode != '\x03')) ||
               (((set_kind != 1 || ((*(byte *)(*(int *)((int)lr->chain + 0x10) + 3) & 0xf8) != 0x28)
                 ) && (((set_kind != 0 || (*(short *)lr->chain != 0)) ||
                       ((*(byte *)(*(int *)(*(int *)((int)lr->chain + 8) + 8) + 3) & 0xf8) != 0x28))
                      )))) &&
              (((g_options->cpu != 4 ||
                (((set_kind != 1 ||
                  ((*(byte *)(*(int *)((int)lr->chain + 0x10) + 3) & 0xe0) != 0x20)) &&
                 ((set_kind != 0 ||
                  ((*(short *)lr->chain != 0 ||
                   ((*(byte *)(*(int *)(*(int *)((int)lr->chain + 8) + 8) + 3) & 0xe0) != 0x20))))))
                )) && (lr->pregno == 0)))))) {
            if (iVar2 < 5) {
              iVar1 = lreg_conflicts_with_call(lr);
              if ((iVar1 == 0) && ((*slot)->bind == (lreg *)0x0)) {
                if (iVar2 < 5) {
                  if ((*slot)->set == 1) {
                    id_node = *(il_node **)((int)(*slot)->chain + 0x10);
                    if (id_node->op != IL_ID) {
                      id_node = id_node->child;
                    }
                    if ((0 < id_node->symx) &&
                       (((g_symtab[id_node->symx].sclass == '\a' ||
                         (g_symtab[id_node->symx].sclass == '\b')) &&
                        (param_regno = parameter_register_index(id_node), (int)param_regno < iVar2))
                       )) goto LAB_0041b1d8;
                  }
                  goto LAB_0041b0ff;
                }
                goto LAB_0041b104;
              }
            }
            else {
LAB_0041b0ff:
              if (4 < iVar2) {
LAB_0041b104:
                if (((*slot)->priori < 3) ||
                   (((4 < iVar2 && (func_attr_08 != 0)) &&
                    (iVar1 = lreg_spans_call(*slot), iVar1 != 0)))) goto LAB_0041b1d8;
              }
              clash = (*slot)->clashed;
              if (clash != (int *)0x0) {
                do {
                  other = (short *)clash[1];
                  if ((*other == iVar2) &&
                     ((((g_options->cpu != 2 || (g_options->fpu_mode != '\x03')) &&
                       (g_options->cpu != 4)) ||
                      (((other[1] == 1 &&
                        ((*(byte *)(*(int *)(*(int *)(other + 0x10) + 0x10) + 3) & 0xe0) != 0x20))
                       || ((other[1] == 0 &&
                           ((**(short **)(other + 0x10) != 0 ||
                            ((*(byte *)(*(int *)(*(int *)(*(short **)(other + 0x10) + 4) + 8) + 3) &
                             0xe0) != 0x20)))))))))) break;
                  clash = (int *)*clash;
                } while (clash != (int *)0x0);
                if (clash != (int *)0x0) goto LAB_0041b1d8;
              }
              if ((((4 < iVar2) || ((*slot)->set != 1)) ||
                  ((*(byte *)(*(int *)((int)(*slot)->chain + 0x10) + 0x5f) & 0x80) == 0)) &&
                 (((*slot)->set != 0 ||
                  ((*(byte *)(*(int *)(*(int *)((int)(*slot)->chain + 8) + 8) + 0x5f) & 0x80) == 0))
                 )) {
                (*slot)->pregno = (short)iVar2;
              }
            }
          }
LAB_0041b1d8:
          i = i + 1;
        } while (i <= g_lreg_count);
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 <= g_int_reg_count);
  }
  iVar1 = -1;
  if (g_int_reg_count < iVar2) {
    do {
      assigned = false;
      iVar2 = 1;
      if (0 < g_lreg_count) {
        slot = g_lreg_table;
        do {
          slot = slot + 1;
          lr = *slot;
          set_kind = lr->set;
          if ((set_kind != 3) &&
             ((((g_options->cpu != 2 || (g_options->fpu_mode != '\x03')) ||
               (((set_kind != 1 || ((*(byte *)(*(int *)((int)lr->chain + 0x10) + 3) & 0xf8) != 0x28)
                 ) && (((set_kind != 0 || (*(short *)lr->chain != 0)) ||
                       ((*(byte *)(*(int *)(*(int *)((int)lr->chain + 8) + 8) + 3) & 0xf8) != 0x28))
                      )))) &&
              (((g_options->cpu != 4 ||
                (((set_kind != 1 ||
                  ((*(byte *)(*(int *)((int)lr->chain + 0x10) + 3) & 0xe0) != 0x20)) &&
                 ((set_kind != 0 ||
                  ((*(short *)lr->chain != 0 ||
                   ((*(byte *)(*(int *)(*(int *)((int)lr->chain + 8) + 8) + 3) & 0xe0) != 0x20))))))
                )) && (lr->pregno == 0)))))) {
            clash = lr->clashed;
            if (clash != (int *)0x0) {
              do {
                if (*(short *)clash[1] == iVar1) break;
                clash = (int *)*clash;
              } while (clash != (int *)0x0);
              if (clash != (int *)0x0) goto LAB_0041b388;
            }
            if (set_kind == 1) {
              id_node = *(il_node **)((int)lr->chain + 0x10);
              if (id_node->op != IL_ID) {
                id_node = id_node->child;
              }
              if (((id_node->symx < 0) ||
                  (sclass = g_symtab[id_node->symx].sclass, sclass == '\x05')) || (sclass == '\x06')
                 ) {
                assigned = true;
                lr->pregno = (short)iVar1;
              }
              else if ((sclass == '\a') || (sclass == '\b')) {
                param_regno = parameter_register_index(id_node);
                if (((id_node->type & 0xe0) == 0) ||
                   ((kind = id_node->type & 0xf8, kind == 0x40 || (limit = 0, kind == 0x28)))) {
                  limit = 5;
                }
                if ((int)param_regno < limit) {
                  assigned = true;
                  (*slot)->pregno = (short)iVar1;
                }
              }
            }
          }
LAB_0041b388:
          iVar2 = iVar2 + 1;
        } while (iVar2 <= g_lreg_count);
      }
      if (!assigned) break;
      iVar1 = iVar1 + -1;
    } while( true );
  }
  if (((g_options->cpu == 2) && (g_options->fpu_mode == '\x03')) || (g_options->cpu == 4)) {
    iVar1 = assign_float_registers(iVar1,func_attr_08,func_attr_1c);
  }
  REGVAR_LOG();
  add_memory_lregs((short)iVar1);
  write_lreg_numbers();
  return;
}



