#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_lreg_list
#define g_lreg_list (*(lreg * *)(g_sd + 0x16264))
#undef g_options
#define g_options (*(option_record * *)(g_sd + 0x1e714))
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 00402e70
// name : coalesce_copy_webs
// size : 756
// sig  : void coalesce_copy_webs(void)


int __cdecl coalesce_copy_webs(void)

{
  lreg *plVar1;
  dutbl *def;
  uint arg_index;
  int iVar2;
  lreg *plVar3;
  byte type_class;
  dutbl *du;
  bool on_stack;
  il_node *opnd;
  lreg *tail;
  
  plVar3 = g_lreg_list;
  do {
    plVar1 = g_lreg_list;
    if (plVar3 == (lreg *)0x0) {
      for (; plVar1 != (lreg *)0x0; plVar1 = plVar1->next) {
        if (((plVar1->set == 1) && (plVar3 = plVar1->bind, plVar3 != (lreg *)0x0)) &&
           (plVar3 != plVar1)) {
          if (plVar3->bind != plVar3) {
            do {
              plVar3 = plVar3->bind;
            } while (plVar3->bind != plVar3);
          }
          merge_bound_lreg(plVar3,plVar1);
        }
      }
      return;
    }
    if (((plVar3->set == 1) && (def = find_single_definition(plVar3->chain), def != (dutbl *)0x0))
       && (def->node->op == IL_ASSIGN)) {
      opnd = def->node->child;
      arg_index = parameter_register_index(opnd);
      if (g_options->cpu == 4) {
        if ((opnd->type & 0xe0) != 0x20) goto joined_r0x00402f4c;
joined_r0x00402f1b:
        on_stack = true;
        if ((int)arg_index < g_float_arg_reg_limit) goto LAB_00402f4e;
      }
      else {
        if ((g_options->cpu == 2) && (g_options->fpu_mode == '\x03')) {
          if ((opnd->type & 0xf8) == 0x28) goto joined_r0x00402f1b;
        }
        else if (((opnd->type & 0xe0) != 0) &&
                ((type_class = opnd->type & 0xf8, type_class != 0x40 && (type_class != 0x28)))) {
          on_stack = false;
          goto LAB_00402f50;
        }
joined_r0x00402f4c:
        on_stack = true;
        if ((int)arg_index < 5) {
LAB_00402f4e:
          on_stack = false;
        }
      }
LAB_00402f50:
      if (((!on_stack) || (opnd->symx < 1)) ||
         ((g_symtab[opnd->symx].sclass != '\a' && (g_symtab[opnd->symx].sclass != '\b')))) {
        opnd = def->node->child->next;
        if (((opnd->op == IL_ID) || ((opnd->op == IL_ASSIGN && (opnd->child->op == IL_ID)))) &&
           ((opnd->cmnexp != (il_node *)0x0 &&
            ((du = opnd->cmnexp->duptr, du != (dutbl *)0x0 && (du->links != (node_list *)0x0)))))) {
          arg_index = parameter_register_index(opnd);
          if (g_options->cpu == 4) {
            if ((opnd->type & 0xe0) != 0x20) goto joined_r0x0040305c;
joined_r0x0040302b:
            on_stack = true;
            if (g_float_arg_reg_limit <= (int)arg_index) goto LAB_0040305e;
          }
          else {
            if ((g_options->cpu == 2) && (g_options->fpu_mode == '\x03')) {
              if ((opnd->type & 0xf8) == 0x28) goto joined_r0x0040302b;
            }
            else if (((opnd->type & 0xe0) != 0) &&
                    ((type_class = opnd->type & 0xf8, type_class != 0x40 && (type_class != 0x28))))
            {
              on_stack = false;
              goto LAB_00403060;
            }
joined_r0x0040305c:
            on_stack = true;
            if (4 < (int)arg_index) {
LAB_0040305e:
              on_stack = false;
            }
          }
LAB_00403060:
          if (((!on_stack) || (opnd->symx < 1)) ||
             ((g_symtab[opnd->symx].sclass != '\a' && (g_symtab[opnd->symx].sclass != '\b')))) {
            def = def->node->child->next->cmnexp->duptr;
            if (def->kind == 1) {
              def = def->links->node->duptr;
            }
            def = find_single_definition(*(dutbl **)(def->node->val3 + 0x20));
            if ((((def != (dutbl *)0x0) && (def->node->op == IL_ASSIGN)) &&
                (*(short *)(def->node->val3 + 2) == 1)) &&
               (iVar2 = definition_outside_life_areas(plVar3,def), iVar2 != 0)) {
              plVar1 = (lreg *)def->node->val3;
              plVar3->bind = plVar1;
              if (plVar1->bind == (lreg *)0x0) {
                plVar1->bind = plVar1;
              }
              plVar3->bakbind = (lreg *)0x0;
              tail = plVar1->bakbind;
              if (tail == (lreg *)0x0) {
                plVar1->bakbind = plVar3;
              }
              else {
                plVar1 = tail->bakbind;
                while (plVar1 != (lreg *)0x0) {
                  tail = tail->bakbind;
                  plVar1 = tail->bakbind;
                }
                tail->bakbind = plVar3;
              }
            }
          }
        }
      }
    }
    plVar3 = plVar3->next;
  } while( true );
}



