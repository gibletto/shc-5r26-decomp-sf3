#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_func_node
#define g_func_node (*(il_node * *)(g_sd + 0x1e738))
#undef g_symtab
#define g_symtab (*(symbol * *)(g_sd + 0x26efc))


// entry: 004127d0
// name : special_change_body
// size : 1005
// sig  : void special_change_body(il_node * body)


int __cdecl special_change_body(il_node *body)

{
  il_node *piVar1;
  il_node *piVar2;
  int ok;
  il_node *piVar3;
  short sym1;
  short sVar4;
  short sym2;
  short state;
  il_node *next_stmt;
  
  sym2 = 0;
  sym1 = 0;
  if ((((((((body->op == IL_BLOCK) && (piVar1 = body->child, piVar1->op == IL_FOR)) &&
          (piVar2 = piVar1->next, piVar2 != (il_node *)0x0)) &&
         ((piVar2->op == IL_RETURN && (piVar3 = piVar2->next, piVar3 != (il_node *)0x0)))) &&
        (piVar3->op == IL_E_BLOCK)) &&
       (((((piVar3->next == (il_node *)0x0 && (piVar2 = piVar2->child, piVar2->op == IL_CONST)) &&
          (((piVar2->type & 0xf8) == 0x10 &&
           (((piVar2->val == 0 && (piVar2 = piVar1->child, piVar2->op == IL_ASSIGN)) &&
            ((piVar2->type & 0xf8) == 0x10)))))) &&
         ((piVar2 = piVar2->child, piVar2->op == IL_ID &&
          (sVar4 = piVar2->symx, g_symtab[sVar4].sclass == '\x06')))) &&
        (piVar2->next->op == IL_CONST)))) &&
      (((piVar2->next->val == 0 &&
        (piVar1 = piVar1->child->next, g_spec_index_sym = sVar4, piVar1->op == IL_BLOCK)) &&
       ((piVar2 = piVar1->next, piVar2->op == IL_POI &&
        ((((piVar2->type & 0xf8) == 0x10 && (piVar2->child->op == IL_ID)) &&
         (piVar2->child->symx == sVar4)))))))) &&
     (((piVar2 = piVar2->next, piVar2->op == IL_LT && ((piVar2->type & 0xf8) == 0x10)) &&
      ((piVar2 = piVar2->child, piVar2->op == IL_ID &&
       (((piVar2->symx == sVar4 && (piVar2->next->op == IL_ID)) &&
        (g_symtab[piVar2->next->symx].sclass == '\x02')))))))) {
    piVar2 = last_operand(piVar1);
    ok = operand_index(piVar2);
    if (ok == 6) {
      state = 1;
      for (piVar2 = piVar1->child; piVar2 != (il_node *)0x0; piVar2 = piVar2->next) {
        switch(state) {
        case 1:
          if (piVar2->op != IL_ASSIGN) {
            return;
          }
          if ((piVar2->type & 0xf8) != 0x10) {
            return;
          }
          piVar3 = piVar2->child;
          if (piVar3->op != IL_ID) {
            return;
          }
          if (g_symtab[piVar3->symx].sclass != '\x06') {
            return;
          }
          ok = match_spec_load(piVar3->next,'\x01');
          if (ok == 0) {
            return;
          }
          sym1 = piVar2->child->symx;
          break;
        case 2:
          if (piVar2->op != IL_ASSIGN) {
            return;
          }
          if ((piVar2->type & 0xf8) != 0x10) {
            return;
          }
          piVar3 = piVar2->child;
          if (piVar3->op != IL_ID) {
            return;
          }
          if (g_symtab[piVar3->symx].sclass != '\x06') {
            return;
          }
          ok = match_spec_load(piVar3->next,'\x02');
          if (ok == 0) {
            return;
          }
          sym2 = piVar2->child->symx;
          break;
        case 3:
          if (piVar2->op != IL_IF) {
            return;
          }
          if (piVar2->child->op != IL_EQ) {
            return;
          }
          piVar3 = piVar2->child->next;
          if (piVar3->op != IL_ASSIGN) {
            return;
          }
          if (piVar3->next->op != IL_EMPTY) {
            return;
          }
          ok = match_spec_zero_test(piVar2,sym1);
          if (ok == 0) {
            return;
          }
          break;
        case 4:
          if (piVar2->op != IL_IF) {
            return;
          }
          if (piVar2->child->op != IL_EQ) {
            return;
          }
          piVar3 = piVar2->child->next;
          if (piVar3->op != IL_ASSIGN) {
            return;
          }
          if (piVar3->next->op != IL_EMPTY) {
            return;
          }
          ok = match_spec_zero_test(piVar2,sym2);
          if (ok == 0) {
            return;
          }
          break;
        case 5:
          if (piVar2->op != IL_IF) {
            return;
          }
          if (piVar2->child->op != IL_NE) {
            return;
          }
          piVar3 = piVar2->child->next;
          if (piVar3->op != IL_BLOCK) {
            return;
          }
          if (piVar3->next->op != IL_EMPTY) {
            return;
          }
          ok = match_spec_compare(piVar2,sym1,sym2);
          if (ok == 0) {
            return;
          }
          break;
        case 6:
          if (piVar2->op != IL_E_BLOCK) {
            return;
          }
          break;
        default:
          goto switchD_00412978_default;
        }
        state = state + 1;
      }
      sVar4 = 1;
      piVar3 = build_spec_change_tree(piVar1,sym1,sym2);
      piVar2 = piVar1->child;
      while (piVar2 != (il_node *)0x0) {
        next_stmt = piVar2->next;
        if (sVar4 == 3) {
          replace_and_free_node(piVar2,piVar3);
        }
        else if ((3 < sVar4) && (sVar4 < 6)) {
          free_tree(piVar2->child);
          delete_operand(piVar1,4);
        }
        sVar4 = sVar4 + 1;
        piVar2 = next_stmt;
      }
      if (g_debug_flags == 2) {
        dump_tree(g_func_node,0,s_after_spec_chg_tree_00435484);
      }
    }
  }
switchD_00412978_default:
  return;
}



