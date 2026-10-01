#include "decls.h"
#include "imports.h"

// entry: 0042d9b1
// name : pool_literal_matches
// size : 599
// sig  : int pool_literal_matches(literal_entry * entry, int value, label_ref * labels)


int __cdecl pool_literal_matches(literal_entry *entry,int value,label_ref *labels)

{
  unsigned char _frec_30[48];
#define wanted_count (*(int *)(_frec_30 + 0))
#define is_match (*(undefined4 *)(_frec_30 + 4))
#define used_slots (*(char (*)[20])(_frec_30 + 8))
#define matched_count (*(int *)(_frec_30 + 28))
#define cur_ref (*(label_ref * *)(_frec_30 + 32))
#define entry_ref (*(label_ref * *)(_frec_30 + 36))
#define slot (*(int *)(_frec_30 + 40))
  int iVar1;
  bool found;
  
  is_match = 0;
  if (entry->value == value) {
    found = true;
    for (slot = 0; slot < 0x14; slot = slot + 1) {
      used_slots[slot] = '\0';
    }
    matched_count = 0;
    entry_ref = entry->labels;
    while ((entry_ref != (label_ref *)0x0 && (found))) {
      found = false;
      slot = 0;
      for (cur_ref = labels; iVar1 = slot, cur_ref != (label_ref *)0x0; cur_ref = cur_ref->next) {
        slot = slot + 1;
        if ((used_slots[iVar1] == '\0') && (entry_ref->labno1 == cur_ref->labno1)) {
LAB_0042dab7:
          used_slots[slot + -1] = '\x01';
          found = true;
          break;
        }
        slot = iVar1 + 2;
        if ((used_slots[iVar1 + 1] == '\0') && (entry_ref->labno1 == cur_ref->labno2))
        goto LAB_0042dab7;
      }
      if ((found) && (matched_count = matched_count + 1, entry_ref->labno2 != 0)) {
        found = false;
        slot = 0;
        for (cur_ref = labels; iVar1 = slot, cur_ref != (label_ref *)0x0; cur_ref = cur_ref->next) {
          slot = slot + 1;
          if ((used_slots[iVar1] == '\0') && (entry_ref->labno2 == cur_ref->labno1)) {
LAB_0042db75:
            used_slots[slot + -1] = '\x01';
            found = true;
            break;
          }
          slot = iVar1 + 2;
          if ((used_slots[iVar1 + 1] == '\0') && (entry_ref->labno2 == cur_ref->labno2))
          goto LAB_0042db75;
        }
        if (found) {
          matched_count = matched_count + 1;
        }
      }
      entry_ref = entry_ref->next;
    }
    if (found) {
      wanted_count = 0;
      for (entry_ref = labels; entry_ref != (label_ref *)0x0; entry_ref = entry_ref->next) {
        iVar1 = wanted_count + 1;
        if (entry_ref->labno2 != 0) {
          iVar1 = wanted_count + 2;
        }
        wanted_count = iVar1;
      }
      if (wanted_count == matched_count) {
        is_match = 1;
      }
    }
  }
  return is_match;
#undef wanted_count
#undef is_match
#undef used_slots
#undef matched_count
#undef cur_ref
#undef entry_ref
#undef slot
}



