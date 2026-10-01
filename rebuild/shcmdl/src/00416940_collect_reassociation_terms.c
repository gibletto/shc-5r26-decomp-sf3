#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef PTR_PTR_00433afc
#define PTR_PTR_00433afc (*(unsigned char * *)(g_sd + 0x1afc))
#undef PTR_PTR_00433bf8
#define PTR_PTR_00433bf8 (*(unsigned char * *)(g_sd + 0x1bf8))
#undef g_released_nodes
#define g_released_nodes (*(il_node * *)(g_sd + 0x1e4d0))
#undef g_term_list
#define g_term_list (*(term * *)(g_sd + 0x1e4c8))


// entry: 00416940
// name : collect_reassociation_terms
// size : 1062
// sig  : int collect_reassociation_terms(il_node * node, short op_class, short negate, il_op parent_op)


/* WARNING: Type propagation algorithm not settling */

int __cdecl collect_reassociation_terms(il_node *node,short op_class,short negate,il_op parent_op)

{
  unsigned char _frec_10[16];
#define fold_result (*(int (*)[4])(_frec_10 + 0))
  int iVar1;
  term *entry;
  il_node *piVar2;
  short sVar3;
  term *cur;
  term *next;
  term *prev;
  term *new_head;
  il_op op;
  il_node *other_node;
  
  sVar3 = 0;
  op = node->op;
  switch(op) {
  case IL_MINUS:
    if (op_class == 1) {
      sVar3 = 1;
    }
    else if (op_class == 2) {
      sVar3 = 2;
      g_negation_count = g_negation_count + 1;
    }
    break;
  case IL_ADD:
  case IL_SUB:
    sVar3 = 1;
    break;
  case IL_MUL:
    sVar3 = 2;
    break;
  case IL_B_AND:
    sVar3 = 3;
    break;
  case IL_B_XOR:
    sVar3 = 5;
    break;
  case IL_B_OR:
    sVar3 = 4;
  }
  if (sVar3 == op_class) {
    sVar3 = negate;
    if (op == IL_MINUS) {
      sVar3 = 1 - negate;
    }
    iVar1 = collect_reassociation_terms(node->child,op_class,sVar3,op);
    if (iVar1 == -1) {
      return -1;
    }
    piVar2 = node->child->next;
    if (piVar2 != (il_node *)0x0) {
      if (op == IL_SUB) {
        negate = 1 - negate;
      }
      iVar1 = collect_reassociation_terms(piVar2,op_class,negate,op);
      if (iVar1 == -1) {
        return -1;
      }
    }
    node->cmnexp = g_released_nodes;
    g_released_nodes = node;
    return 0;
  }
  entry = pool_alloc(0xc);
  if (entry == (term *)0x0) {
    return -1;
  }
  if (op_class == 1) {
    parent_op = IL_SUB - (negate == 0);
  }
  else if (op_class == 2) {
    entry->op = 'D';
    goto LAB_00416a93;
  }
  entry->op = parent_op;
LAB_00416a93:
  entry->node = node;
  if (node->op == IL_CONST) {
    piVar2 = new_const_node(node->type & 0xfc,0);
    entry->node = piVar2;
    piVar2->val = node->val;
    piVar2->val2 = node->val2;
    node->cmnexp = g_released_nodes;
    g_released_nodes = node;
    if (entry->op == 'A') {
      iVar1 = type_arith_class(piVar2->type & 0xfc);
      (**(code **)(PTR_PTR_00433afc + iVar1 * 4))(&piVar2->val,&piVar2->val);
      convert_constant(piVar2->type,piVar2->type,(uint *)&piVar2->val,(uint *)&piVar2->val);
      entry->op = '@';
    }
    if (entry->op == 'D') {
      fold_result[0] = 0;
      fold_result[3] = 0;
      fold_result[2] = 0;
      fold_result[1] = 0;
      iVar1 = type_arith_class(piVar2->type & 0xfc);
      (**(code **)(PTR_PTR_00433bf8 + iVar1 * 4))(&piVar2->val,fold_result + 1,fold_result);
      if (fold_result[0] != 0) {
        g_negation_count = g_negation_count + 1;
        (**(code **)(PTR_PTR_00433afc + iVar1 * 4))(&piVar2->val,&piVar2->val);
        convert_constant(piVar2->type,piVar2->type,(uint *)&piVar2->val,(uint *)&piVar2->val);
      }
    }
  }
  if (g_term_list == (term *)0x0) {
    g_term_list = entry;
    return 0;
  }
  prev = (term *)0x0;
  next = g_term_list;
  if (g_term_list != (term *)0x0) {
    piVar2 = entry->node;
    do {
      cur = next;
      other_node = cur->node;
      next = cur;
      new_head = entry;
      if (g_reassoc_side_effect == 0) {
        if ((char)other_node->nodes < (char)piVar2->nodes) {
LAB_00416ccb:
          if (prev != (term *)0x0) {
            prev->next = entry;
            new_head = g_term_list;
          }
LAB_00416d4e:
          g_term_list = new_head;
          entry->next = cur;
          break;
        }
        if (piVar2->op != IL_ID) goto LAB_00416c30;
        if ((other_node->op == IL_ID) && (piVar2->symx < other_node->symx)) goto LAB_00416ccb;
        if (((((piVar2->type & 2) == 0) && (other_node->op == IL_ID)) &&
            ((other_node->type & 2) == 0)) && (piVar2->symx == other_node->symx)) {
          if (((op_class == 1) && (cur->op != entry->op)) || (op_class == 5)) {
            piVar2->cmnexp = g_released_nodes;
            g_released_nodes = piVar2;
            pool_free(entry,0xc);
            if (prev == (term *)0x0) {
              g_term_list = cur->next;
              if (g_term_list == (term *)0x0) {
                g_term_list = (term *)0x0;
              }
            }
            else {
              prev->next = cur->next;
            }
            other_node->cmnexp = g_released_nodes;
            g_released_nodes = other_node;
            pool_free(cur,0xc);
            break;
          }
          if ((op_class == 3) || (op_class == 4)) {
            piVar2->cmnexp = g_released_nodes;
            g_released_nodes = piVar2;
            pool_free(entry,0xc);
            break;
          }
        }
      }
LAB_00416c30:
      if (other_node->op == IL_CONST) {
        if (piVar2->op != IL_CONST) {
          if (prev != (term *)0x0) {
            prev->next = entry;
            new_head = g_term_list;
          }
          goto LAB_00416d4e;
        }
        iVar1 = type_arith_class(piVar2->type);
        (**(code **)(*(int *)(&g_fold_op_table + entry->op * 4) + iVar1 * 4))
                  (&other_node->val,&piVar2->val,&other_node->val);
        convert_constant(other_node->type,other_node->type,(uint *)&other_node->val,
                         (uint *)&other_node->val);
        piVar2->cmnexp = g_released_nodes;
        g_released_nodes = piVar2;
        pool_free(entry,0xc);
        break;
      }
      next = cur->next;
      prev = cur;
    } while (next != (term *)0x0);
  }
  if (next == (term *)0x0) {
    prev->next = entry;
  }
  return 0;
#undef fold_result
}



