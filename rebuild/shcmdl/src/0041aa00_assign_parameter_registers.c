#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_options
#define g_options (*(option_record * *)(g_sd + 0x1e714))
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 0041aa00
// name : assign_parameter_registers
// size : 664
// sig  : void assign_parameter_registers(void)


int __cdecl assign_parameter_registers(void)

{
  lreg *lr;
  int conflict;
  uint regno;
  byte kind;
  int *clash;
  il_node *id;
  uint other_regno;
  lreg **slot;
  int i;
  int other_node;
  short cpu;
  bool in_reg;
  short *other;
  
  i = 1;
  if (0 < g_lreg_count) {
    slot = g_lreg_table;
    do {
      slot = slot + 1;
      lr = *slot;
      if ((lr->pregno == 0) && (lr->set == 1)) {
        id = *(il_node **)((int)lr->chain + 0x10);
        if (*(int *)lr->chain == 2) {
          id = id->duptr->links->node;
        }
        if ((0 < id->symx) &&
           (((g_symtab[id->symx].sclass == '\a' || (g_symtab[id->symx].sclass == '\b')) &&
            (conflict = lreg_conflicts_with_call(lr), conflict == 0)))) {
          regno = parameter_register_index(id);
          cpu = g_options->cpu;
          if ((cpu == 2) && (g_options->fpu_mode == '\x03')) {
LAB_0041ab48:
            if (((cpu == 2) && (g_options->fpu_mode == '\x03')) &&
               (kind = id->type & 0xf8, kind != 0x30)) {
              if (kind == 0x28) {
                in_reg = true;
                if (g_float_arg_regs < (int)regno) {
LAB_0041ab94:
                  in_reg = false;
                }
              }
              else {
                in_reg = true;
                if (4 < (int)regno) goto LAB_0041ab94;
              }
              if (in_reg) goto LAB_0041ab9e;
            }
          }
          else if (cpu == 4) {
            if ((id->type & 0xe0) == 0x20) {
              in_reg = true;
              if (g_float_arg_regs < (int)regno) {
LAB_0041ab42:
                in_reg = false;
              }
            }
            else {
              in_reg = true;
              if (4 < (int)regno) goto LAB_0041ab42;
            }
            if (!in_reg) goto LAB_0041ab48;
LAB_0041ab9e:
            clash = (*slot)->clashed;
            if (clash != (int *)0x0) {
              do {
                other = (short *)clash[1];
                if (other[1] == 1) {
                  other_node = *(int *)(*(int *)(other + 0x10) + 0x10);
                }
                else if (other[1] == 0) {
                  other_node = *(int *)(*(int *)(*(int *)(other + 0x10) + 8) + 8);
                }
                other_regno = (uint)*other;
                if (regno == other_regno) {
                  if (cpu == 4) {
                    if ((id->type & 0xe0) == 0x20) {
                      if ((*(byte *)(other_node + 3) & 0xe0) == 0x20) break;
                    }
                    else if ((*(byte *)(other_node + 3) & 0xe0) != 0x20) break;
                  }
                  else if ((id->type & 0xf8) == 0x28) {
                    if ((*(byte *)(other_node + 3) & 0xf8) == 0x28) break;
                  }
                  else if ((*(byte *)(other_node + 3) & 0xf8) != 0x28) break;
                }
                else if ((*other != 0) &&
                        ((((kind = id->type & 0xf8, kind == 0x30 &&
                           ((*(byte *)(other_node + 3) & 0xf8) == 0x28)) &&
                          (other_regno - regno == 1)) ||
                         (((kind == 0x28 && ((*(byte *)(other_node + 3) & 0xf8) == 0x30)) &&
                          (other_regno - regno == -1)))))) break;
                clash = (int *)*clash;
              } while (clash != (int *)0x0);
              if (clash != (int *)0x0) goto LAB_0041ac77;
            }
            (*slot)->pregno = (short)regno;
          }
          else if (((((id->type & 0xe0) == 0) || (kind = id->type & 0xf8, kind == 0x40)) ||
                   (kind == 0x28)) && ((int)regno < 5)) {
            clash = (*slot)->clashed;
            if (clash != (int *)0x0) {
              do {
                if ((int)*(short *)clash[1] == regno) break;
                clash = (int *)*clash;
              } while (clash != (int *)0x0);
              if (clash != (int *)0x0) goto LAB_0041ac77;
            }
            (*slot)->pregno = (short)regno;
          }
        }
      }
LAB_0041ac77:
      i = i + 1;
    } while (i <= g_lreg_count);
  }
  return;
}



