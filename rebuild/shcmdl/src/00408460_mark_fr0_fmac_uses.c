#include "decls.h"
#include "imports.h"

// entry: 00408460
// name : mark_fr0_fmac_uses
// size : 414
// sig  : void mark_fr0_fmac_uses(il_node * node)


int __cdecl mark_fr0_fmac_uses(il_node *node)

{
  il_node *piVar1;
  bool bVar2;
  bool bVar3;
  il_node *piVar4;
  il_node *piVar5;
  int fmac_count;
  il_node *piVar6;
  short symx;
  
  fmac_count = 0;
  bVar2 = false;
  bVar3 = false;
  if ((node->cmnexp != (il_node *)0x0) && (node == node->cmnexp)) {
    piVar1 = node;
    if ((node->op == IL_ASSIGN) &&
       ((((node->parent->op == IL_COMMA && (node->child->op == IL_ID)) &&
         (piVar5 = node->parent->child->next, piVar5->op == IL_ID)) &&
        ((symx = node->child->symx, symx != 0 && (piVar5->symx == symx)))))) {
      bVar2 = true;
      bVar3 = true;
    }
    for (; piVar1 != (il_node *)0x0; piVar1 = piVar1->refchn) {
      piVar5 = piVar1->parent;
      if ((piVar5 != (il_node *)0x0) && (piVar4 = piVar5->parent, piVar4 != (il_node *)0x0)) {
        piVar6 = piVar4;
        if (bVar2) {
          bVar2 = false;
          piVar6 = piVar4->parent;
          piVar5 = piVar4;
        }
        if ((((piVar5->op == IL_MUL) && ((piVar5->type & 0xf8) == 0x28)) &&
            ((piVar6->type & 0xf8) == 0x28)) &&
           (((piVar5->child->fr0set & 1U) == 0 && ((piVar5->child->next->fr0set & 1U) == 0)))) {
          if (piVar6->op == IL_ADD) {
            piVar4 = piVar6->child;
            if (piVar4 == piVar5) {
              piVar4 = piVar4->next;
            }
            if ((piVar4->op != IL_MUL) ||
               (((piVar4->child->fr0set & 1U) == 0 && ((piVar4->child->next->fr0set & 1U) == 0))))
            goto LAB_00408545;
          }
          else if (piVar6->op == IL_A_ADD) {
LAB_00408545:
            fmac_count = fmac_count + 1;
          }
        }
      }
    }
    if (1 < fmac_count) {
      for (; node != (il_node *)0x0; node = node->refchn) {
        piVar1 = node->parent;
        piVar5 = piVar1->parent;
        piVar4 = piVar5;
        piVar6 = piVar1;
        if (bVar3) {
          piVar4 = piVar5->parent;
          piVar6 = piVar5;
        }
        bVar3 = false;
        if ((((piVar6->op == IL_MUL) && ((piVar6->type & 0xf8) == 0x28)) &&
            ((piVar4->type & 0xf8) == 0x28)) &&
           (((piVar6->child->fr0set & 1U) == 0 && ((piVar6->child->next->fr0set & 1U) == 0)))) {
          if (piVar4->op == IL_ADD) {
            piVar5 = piVar4->child;
            if (piVar5 == piVar6) {
              piVar5 = piVar5->next;
            }
            if (piVar5->op == IL_MUL) {
              if (((piVar5->child->fr0set & 1U) == 0) && ((piVar5->child->next->fr0set & 1U) == 0))
              {
                if (piVar1->op != IL_COMMA) goto LAB_004085e9;
                piVar1->fr0set = piVar1->fr0set | 1;
              }
            }
            else {
              if (piVar1->op != IL_COMMA) goto LAB_004085e9;
              piVar1->fr0set = piVar1->fr0set | 1;
            }
          }
          else if (piVar4->op == IL_A_ADD) {
LAB_004085e9:
            node->fr0set = node->fr0set | 1;
          }
        }
      }
    }
  }
  return;
}



