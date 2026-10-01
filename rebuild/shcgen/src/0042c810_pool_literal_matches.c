#include "decls.h"
#include "imports.h"

// entry: 0042c810
// name : pool_literal_matches
// size : 317
// sig  : int pool_literal_matches(literal_entry * entry, int value, label_ref * labels)


int __cdecl pool_literal_matches(literal_entry *entry,int value,label_ref *labels)

{
  unsigned char _frec_18[24];
#define seen_count (*(undefined4 *)(_frec_18 + 0))
#define slot_used (*(char (*)[20])(_frec_18 + 4))
  int equal;
  int next_slot;
  int count;
  label_ref *entry_ref;
  bool matched;
  label_ref *ref;
  short second_labno;
  int slot;
  
  equal = 0;
  if (entry->value == value) {
    matched = true;
    seen_count = 0;
    entry_ref = entry->labels;
    slot_used[0] = '\0';
    slot_used[1] = '\0';
    slot_used[2] = '\0';
    slot_used[3] = '\0';
    slot_used[4] = '\0';
    slot_used[5] = '\0';
    slot_used[6] = '\0';
    slot_used[7] = '\0';
    slot_used[8] = '\0';
    slot_used[9] = '\0';
    slot_used[10] = '\0';
    slot_used[0xb] = '\0';
    slot_used[0xc] = '\0';
    slot_used[0xd] = '\0';
    slot_used[0xe] = '\0';
    slot_used[0xf] = '\0';
    slot_used[0x10] = '\0';
    slot_used[0x11] = '\0';
    slot_used[0x12] = '\0';
    slot_used[0x13] = '\0';
    count = seen_count;
    for (; entry_ref != (label_ref *)0x0; entry_ref = entry_ref->next) {
      if (!matched) {
        return 0;
      }
      matched = false;
      slot = 0;
      for (ref = labels; ref != (label_ref *)0x0; ref = ref->next) {
        next_slot = slot + 1;
        if (((slot_used[slot] == '\0') && (ref->labno1 == entry_ref->labno1)) ||
           ((next_slot = slot + 2, slot_used[slot + 1] == '\0' && (entry_ref->labno1 == ref->labno2)
            ))) {
          *(undefined1 *)((int)&seen_count + next_slot + 3) = 1;
          matched = true;
          break;
        }
        slot = next_slot;
      }
      seen_count = count;
      if (matched) {
        second_labno = entry_ref->labno2;
        seen_count = count + 1;
        if (second_labno != 0) {
          matched = false;
          slot = 0;
          for (ref = labels; ref != (label_ref *)0x0; ref = ref->next) {
            next_slot = slot + 1;
            if (((slot_used[slot] == '\0') && (ref->labno1 == second_labno)) ||
               ((next_slot = slot + 2, slot_used[slot + 1] == '\0' && (ref->labno2 == second_labno))
               )) {
              *(undefined1 *)((int)&seen_count + next_slot + 3) = 1;
              matched = true;
              break;
            }
            slot = next_slot;
          }
          if (matched) {
            seen_count = count + 2;
          }
        }
      }
      count = seen_count;
    }
    if (matched) {
      slot = 0;
      for (; labels != (label_ref *)0x0; labels = labels->next) {
        next_slot = slot + 1;
        if (labels->labno2 != 0) {
          next_slot = slot + 2;
        }
        slot = next_slot;
      }
      if (slot == count) {
        equal = 1;
      }
    }
  }
  return equal;
#undef seen_count
#undef slot_used
}



