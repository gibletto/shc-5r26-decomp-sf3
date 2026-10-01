#include "decls.h"
#include "imports.h"

// entry: 004395e0
// name : find_keyed_entry
// size : 50
// sig  : request_entry * find_keyed_entry(request * req, int key)


request_entry * __cdecl find_keyed_entry(request *req,int key)

{
  request_entry *entry;
  
  if (req != (request *)0x0) {
    for (entry = req->entry12_list_0c0; (entry != (request_entry *)0x0 && (*(int *)entry->a != key))
        ; entry = entry->next) {
    }
    return (request_entry *)((entry == (request_entry *)0x0) - 1 & (uint)entry);
  }
  return (request_entry *)0x0;
}



