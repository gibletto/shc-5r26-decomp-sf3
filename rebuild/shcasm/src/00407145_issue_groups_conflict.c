#include "decls.h"
#include "imports.h"

// entry: 00407145
// name : issue_groups_conflict
// size : 307
// sig  : int issue_groups_conflict(int entry_a, int entry_b)


int __cdecl issue_groups_conflict(int entry_a,int entry_b)

{
  int conflict;
  char group_a;
  char group_b;
  
  group_a = g_superscalar_window[entry_a].issue_group;
  group_b = g_superscalar_window[entry_b].issue_group;
  if ((group_a == '\x04') || (group_b == '\x04')) {
    conflict = 0xff;
  }
  else if ((group_a == '\x01') && (group_b == '\x01')) {
    conflict = 0xff;
  }
  else if ((group_a == '\x06') && ((group_b == '\x06' || (group_b == '\x05')))) {
    conflict = 0xff;
  }
  else if (group_a == '\x05') {
    conflict = 0xff;
  }
  else if ((((group_a < '\a') || ('\x15' < group_a)) || (group_b < '\a')) || ('\x15' < group_b)) {
    if ((group_a == '\x02') && (group_b == '\x02')) {
      conflict = 0xff;
    }
    else {
      conflict = 0;
    }
  }
  else {
    conflict = 0xff;
  }
  return conflict;
}



