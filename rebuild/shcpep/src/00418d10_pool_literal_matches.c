#include "decls.h"
#include "imports.h"

// entry: 00418d10
// name : pool_literal_matches
// size : 317
// sig  : int pool_literal_matches(literal_entry * entry, int value, label_ref * labels)


int __cdecl pool_literal_matches(literal_entry *entry,int value,label_ref *labels)

{
  unsigned char _frec_18[24];
#define local_18 (*(undefined4 *)(_frec_18 + 0))
#define used_slots (*(char (*)[20])(_frec_18 + 4))
  int result;
  int next_slot;
  label_ref *entry_ref;
  short labno;
  label_ref *lref;
  int match_count;
  bool matched;
  int slot;
  
  result = 0;
  if (entry->value == value) {
    matched = true;
    local_18 = 0;
    entry_ref = entry->labels;
    used_slots[0] = '\0';
    used_slots[1] = '\0';
    used_slots[2] = '\0';
    used_slots[3] = '\0';
    used_slots[4] = '\0';
    used_slots[5] = '\0';
    used_slots[6] = '\0';
    used_slots[7] = '\0';
    used_slots[8] = '\0';
    used_slots[9] = '\0';
    used_slots[10] = '\0';
    used_slots[0xb] = '\0';
    used_slots[0xc] = '\0';
    used_slots[0xd] = '\0';
    used_slots[0xe] = '\0';
    used_slots[0xf] = '\0';
    used_slots[0x10] = '\0';
    used_slots[0x11] = '\0';
    used_slots[0x12] = '\0';
    used_slots[0x13] = '\0';
    match_count = local_18;
    for (; entry_ref != (label_ref *)0x0; entry_ref = entry_ref->next) {
      if (!matched) {
        return 0;
      }
      matched = false;
      slot = 0;
      for (lref = labels; lref != (label_ref *)0x0; lref = lref->next) {
        next_slot = slot + 1;
        if (((used_slots[slot] == '\0') && (lref->labno1 == entry_ref->labno1)) ||
           ((next_slot = slot + 2, used_slots[slot + 1] == '\0' &&
            (entry_ref->labno1 == lref->labno2)))) {
          *(undefined1 *)((int)&local_18 + next_slot + 3) = 1;
          matched = true;
          break;
        }
        slot = next_slot;
      }
      local_18 = match_count;
      if (matched) {
        labno = entry_ref->labno2;
        local_18 = match_count + 1;
        if (labno != 0) {
          matched = false;
          slot = 0;
          for (lref = labels; lref != (label_ref *)0x0; lref = lref->next) {
            next_slot = slot + 1;
            if (((used_slots[slot] == '\0') && (lref->labno1 == labno)) ||
               ((next_slot = slot + 2, used_slots[slot + 1] == '\0' && (lref->labno2 == labno)))) {
              *(undefined1 *)((int)&local_18 + next_slot + 3) = 1;
              matched = true;
              break;
            }
            slot = next_slot;
          }
          if (matched) {
            local_18 = match_count + 2;
          }
        }
      }
      match_count = local_18;
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
      if (slot == match_count) {
        result = 1;
      }
    }
  }
  return result;
#undef local_18
#undef used_slots
}



