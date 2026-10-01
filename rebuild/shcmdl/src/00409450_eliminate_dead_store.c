#include "decls.h"
#include "imports.h"

// entry: 00409450
// name : eliminate_dead_store
// size : 1463
// sig  : il_node * eliminate_dead_store(il_node * node)


il_node * __cdecl eliminate_dead_store(il_node *node)

{
  unsigned char _frec_4[4];
#define repl (*(il_node * *)(_frec_4 + 0))
  il_node **ppiVar1;
  int iVar2;
  il_node *piVar3;
  il_node *piVar4;
  byte lhs_size;
  byte bVar5;
  bool dead;
  dutbl *du;
  short filn;
  ushort line;
  node_list *link;
  short listno;
  il_op op;
  byte rhs_type;
  uchar type;
  uchar *type_ptr;
  
  dead = false;
  du = node->duptr;
  if ((du != (dutbl *)0x0) && (node->refchn == (il_node *)0x0)) {
    if (du->links == (node_list *)0x0) {
      dead = true;
    }
    else {
      link = du->links;
      if ((link != (node_list *)0x0) && ((node->flag & 0x20) == 0)) {
        dead = true;
        for (; link != (node_list *)0x0; link = link->next) {
          piVar3 = link->node->parent;
          if (piVar3 == (il_node *)0x0) {
LAB_004094f2:
            dead = false;
            break;
          }
          do {
            if (piVar3 == node) break;
            op = piVar3->op;
            if (((('/' < (char)op) && ((char)op < '>')) || (('O' < (char)op && ((char)op < '`'))))
               || ((piVar3->parent == (il_node *)0x0 ||
                   ((((op = piVar3->parent->op, op == IL_AND || (op == IL_OR)) || (op == IL_COND))
                    && (iVar2 = operand_index(piVar3), iVar2 == 1)))))) {
              dead = false;
              break;
            }
            piVar3 = piVar3->parent;
          } while (piVar3 != (il_node *)0x0);
          if ((piVar3 == (il_node *)0x0) || (!dead)) goto LAB_004094f2;
        }
      }
    }
  }
  op = node->op;
  if ((((op == IL_ASSIGN) || (('O' < (char)op && ((char)op < '_')))) ||
      ((op == IL_POI || (((op == IL_POD || (op == IL_PRI)) || (op == IL_PRD)))))) && (dead)) {
    g_tree_changed = 1;
    switch(node->op) {
    case IL_PRI:
    case IL_PRD:
      type_ptr = &node->type;
      type = *type_ptr;
      if (type == '@') {
        piVar3 = node->child;
        node->child = (il_node *)0x0;
        piVar3->parent = (il_node *)0x0;
        filn = node->filn;
        line = node->line;
        listno = node->listno;
        repl = (il_node *)CONCAT22((*(unsigned short *)((char *)&repl + 2)),filn);
        piVar4 = new_const_node('\x1c',node->val);
        if (node->op == IL_PRI) {
          repl = make_node(IL_ADD,'\x1c',piVar3,piVar4,(il_node *)0x0);
        }
        else if (node->op == IL_PRD) {
          repl = make_node(IL_SUB,'\x1c',piVar3,piVar4,(il_node *)0x0);
        }
        if (((piVar3->type ^ *type_ptr) & 0xfc) != 0) {
          piVar3 = new_node(IL_CAST,*type_ptr & 0xfc);
          insert_parent(repl->child,piVar3);
        }
        replace_and_free_node(node,repl);
        repl->filn = filn;
        repl->line = line;
        repl->listno = listno;
        return repl;
      }
      if (((((((type == '\0') || (type == '\x04')) || (type == '\b')) ||
            ((type == '\f' || (type == '\x10')))) ||
           ((type == '\x14' || ((type == '\x18' || (type == '\x1c')))))) || (type == '(')) ||
         ((type == '0' || (type == '8')))) {
        piVar3 = node->child;
        node->child = (il_node *)0x0;
        piVar3->parent = (il_node *)0x0;
        filn = node->filn;
        line = node->line;
        listno = node->listno;
        repl = (il_node *)CONCAT22((*(unsigned short *)((char *)&repl + 2)),filn);
        piVar4 = alloc_node();
        piVar4->op = IL_CONST;
        piVar4->type = *type_ptr;
        switch(*type_ptr) {
        case '\0':
        case '\x04':
        case '\b':
        case '\f':
        case '\x10':
        case '\x14':
        case '\x18':
        case '\x1c':
          piVar4->val = 1;
          piVar4->val2 = 0;
          break;
        case '(':
          piVar4->val = 0x3f800000;
          piVar4->val2 = 0;
          break;
        case '0':
          piVar4->val = 0x3ff00000;
          piVar4->val2 = 0;
          break;
        case '8':
          piVar4->val = 0x3fff0000;
          piVar4->val2 = (-0x7fffffff - 1);
        }
        piVar4->val3 = 0;
        if (node->op == IL_PRI) {
          repl = make_node(IL_ADD,*type_ptr,piVar3,piVar4,(il_node *)0x0);
        }
        else if (node->op == IL_PRD) {
          repl = make_node(IL_SUB,*type_ptr,piVar3,piVar4,(il_node *)0x0);
        }
        if (((piVar3->type ^ *type_ptr) & 0xfc) != 0) {
          piVar3 = new_node(IL_CAST,*type_ptr & 0xfc);
          insert_parent(repl->child,piVar3);
        }
        replace_and_free_node(node,repl);
        repl->filn = filn;
        repl->line = line;
        repl->listno = listno;
        return repl;
      }
      break;
    case IL_POI:
    case IL_POD:
      piVar3 = node->child;
      node->child = (il_node *)0x0;
      piVar3->parent = (il_node *)0x0;
      bVar5 = node->type & 0xfc;
      replace_and_free_node(node,piVar3);
      node = piVar3;
      if ((piVar3->type & 0xfc) != (short)(char)bVar5) {
        piVar4 = new_node(IL_CAST,bVar5);
        insert_parent(piVar3,piVar4);
        piVar3->parent->filn = piVar3->filn;
        piVar3->parent->line = piVar3->line;
        piVar3->parent->listno = piVar3->listno;
        return piVar3->parent;
      }
      break;
    case IL_A_ADD:
    case IL_A_SUB:
    case IL_A_MUL:
    case IL_A_DIV:
    case IL_A_MOD:
    case IL_A_SL:
    case IL_A_SR:
    case IL_A_AND:
    case IL_A_XOR:
    case IL_A_OR:
      ppiVar1 = &node->child;
      node->op = node->op - IL_SWITCH;
      bVar5 = (*ppiVar1)->type;
      rhs_type = (*ppiVar1)->next->type;
      if (((((rhs_type ^ bVar5) & 0xfc) != 0) && (lhs_size = bVar5 & 0xf8, lhs_size != 0x40)) &&
         (((((bVar5 & 0xe0) != 0 || (((rhs_type & 0xe0) != 0 || (lhs_size == 0)))) ||
           ((rhs_type & 0xf8) == 0)) ||
          (((lhs_size == 8 || ((rhs_type & 0xf8) == 8)) || (((rhs_type ^ bVar5) & 4) != 0)))))) {
        type_ptr = &node->type;
        piVar3 = new_node(IL_CAST,*type_ptr & 0xfc);
        insert_parent(node,piVar3);
        piVar3 = *ppiVar1;
        if ((((piVar3->type ^ *type_ptr) & 0xfc) != 0) &&
           (((op = node->op, op == IL_DIV || (op == IL_MOD)) || (op == IL_SR)))) {
          piVar4 = new_node(IL_CAST,*type_ptr & 0xfc);
          insert_parent(piVar3,piVar4);
        }
        piVar3 = *ppiVar1;
        piVar4 = new_node(IL_CAST,piVar3->next->type & 0xfc);
        insert_parent(piVar3,piVar4);
        *type_ptr = (*ppiVar1)->type;
        node->parent->filn = node->filn;
        node->parent->line = node->line;
        node->parent->listno = node->listno;
        return node->parent;
      }
      type_ptr = &node->type;
      if (((*type_ptr ^ bVar5) & 0xfc) != 0) {
        piVar3 = new_node(IL_CAST,*type_ptr & 0xfc);
        insert_parent(node,piVar3);
        op = node->op;
        if (((op == IL_DIV) || (op == IL_MOD)) || (op == IL_SR)) {
          piVar3 = new_node(IL_CAST,*type_ptr & 0xfc);
          insert_parent(*ppiVar1,piVar3);
        }
        piVar3 = new_node(IL_CAST,*type_ptr & 0xfc);
        insert_parent(*ppiVar1,piVar3);
        piVar3 = new_node(IL_CAST,*type_ptr & 0xfc);
        insert_parent((*ppiVar1)->next,piVar3);
        ppiVar1 = &node->parent;
        (*ppiVar1)->filn = node->filn;
        (*ppiVar1)->line = node->line;
        (*ppiVar1)->listno = node->listno;
        return *ppiVar1;
      }
      break;
    case IL_ASSIGN:
      piVar3 = node->child->next;
      node->child->next = (il_node *)0x0;
      piVar3->parent = (il_node *)0x0;
      replace_and_free_node(node,piVar3);
      node = piVar3;
    }
  }
  return node;
#undef repl
}



