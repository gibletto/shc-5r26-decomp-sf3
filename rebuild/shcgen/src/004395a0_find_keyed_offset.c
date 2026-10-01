#include "decls.h"
#include "imports.h"

// entry: 004395a0
// name : find_keyed_offset
// size : 62
// sig  : int find_keyed_offset(request * req, int key, int * value)


int __cdecl find_keyed_offset(request *req,int key,int *value)

{
  request_entry *entry;
  int offset;
  
  if (req == (request *)0x0) {
    return 0;
  }
  entry = req->entry12_list_0c0;
  offset = 0;
  if (entry != (request_entry *)0x0) {
    do {
      if (*(int *)entry->a == key) {
        offset = *(int *)entry->b;
        break;
      }
      entry = entry->next;
    } while (entry != (request_entry *)0x0);
    if (entry != (request_entry *)0x0) {
      *value = offset;
      return 1;
    }
  }
  return 0;
}



