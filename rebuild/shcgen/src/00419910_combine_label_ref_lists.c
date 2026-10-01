#include "decls.h"
#include "imports.h"

// entry: 00419910
// name : combine_label_ref_lists
// size : 539
// sig  : label_ref * combine_label_ref_lists(label_ref * left, label_ref * right, int add)


label_ref * __cdecl combine_label_ref_lists(label_ref *left,label_ref *right,int add)

{
  label_ref *merged;
  label_ref *plVar1;
  label_ref *prev;
  label_ref *cur;
  label_ref *ptr;
  label_ref *plVar2;
  
  if ((left == (label_ref *)0x0) || (right == (label_ref *)0x0)) {
    if (left == (label_ref *)0x0) {
      if (right == (label_ref *)0x0) {
        return (label_ref *)0x0;
      }
      plVar1 = copy_label_ref_list(right);
      if ((add == 0) && (cur = plVar1, plVar1 != (label_ref *)0x0)) {
        do {
          cur->labno1 = -cur->labno1;
          cur->labno2 = -cur->labno2;
          cur = cur->next;
        } while (cur != (label_ref *)0x0);
        return plVar1;
      }
    }
    else {
      plVar1 = copy_label_ref_list(left);
    }
  }
  else {
    merged = copy_label_ref_list(left);
    plVar1 = merged->next;
    cur = merged;
    while (plVar1 != (label_ref *)0x0) {
      cur = cur->next;
      plVar1 = cur->next;
    }
    plVar1 = copy_label_ref_list(right);
    cur->next = plVar1;
    cur = merged;
    if (add == 0) {
      for (; plVar1 != (label_ref *)0x0; plVar1 = plVar1->next) {
        plVar1->labno1 = -plVar1->labno1;
        plVar1->labno2 = -plVar1->labno2;
      }
    }
    for (; plVar1 = cur, cur != (label_ref *)0x0; cur = cur->next) {
      for (; plVar1 != (label_ref *)0x0; plVar1 = plVar1->next) {
        if (cur == plVar1) {
          if ((int)plVar1->labno1 + (int)plVar1->labno2 == 0) {
            plVar1->labno1 = 0;
LAB_004199f7:
            plVar1->labno2 = 0;
          }
        }
        else {
          if ((int)plVar1->labno1 + (int)cur->labno1 == 0) {
            cur->labno1 = 0;
            plVar1->labno1 = 0;
          }
          else if ((int)plVar1->labno2 + (int)cur->labno1 == 0) {
            cur->labno1 = 0;
            plVar1->labno2 = 0;
          }
          if ((int)plVar1->labno1 + (int)cur->labno2 == 0) {
            cur->labno2 = 0;
            plVar1->labno1 = 0;
          }
          else if ((int)plVar1->labno2 + (int)cur->labno2 == 0) {
            cur->labno2 = 0;
            goto LAB_004199f7;
          }
        }
      }
    }
    plVar2 = (label_ref *)0x0;
    plVar1 = (label_ref *)0x0;
    cur = merged;
    if (merged != (label_ref *)0x0) {
      while (plVar1 = (label_ref *)0x0, merged != (label_ref *)0x0) {
        if (cur->labno1 == 0) {
          if (cur->labno2 != 0) {
            cur->labno1 = cur->labno2;
            cur->labno2 = 0;
            goto LAB_00419a6f;
          }
          if (plVar2 == (label_ref *)0x0) {
            plVar1 = cur->next;
            pool_free(cur,8);
            merged = plVar1;
          }
          else {
            plVar2->next = cur->next;
            pool_free(cur,8);
            plVar1 = plVar2->next;
          }
        }
        else {
LAB_00419a6f:
          if ((cur->labno2 == 0) &&
             (plVar1 = cur, plVar2 = cur->next, cur->next != (label_ref *)0x0)) {
            do {
              ptr = plVar2;
              prev = plVar1;
              prev->labno2 = ptr->labno1;
              ptr->labno1 = ptr->labno2;
              ptr->labno2 = 0;
              plVar1 = ptr;
              plVar2 = ptr->next;
            } while (ptr->next != (label_ref *)0x0);
            if ((ptr->labno1 == 0) && (ptr->labno2 == 0)) {
              prev->next = (label_ref *)0x0;
              pool_free(ptr,8);
            }
          }
          plVar1 = cur->next;
          plVar2 = cur;
        }
        cur = plVar1;
        if (plVar1 == (label_ref *)0x0) {
          return merged;
        }
      }
    }
  }
  return plVar1;
}



