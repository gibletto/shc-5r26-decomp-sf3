#include "decls.h"
#include "imports.h"

// entry: 004336e0
// name : find_symbol_request_entry_b
// size : 64
// sig  : int find_symbol_request_entry_b(request * req, short symx, int * out)


int __cdecl find_symbol_request_entry_b(request *req,short symx,int *out)

{
  request_entry *entry;
  int value;
  
  if (req == (request *)0x0) {
    return 0;
  }
  entry = req->entry11_list_0bc;
  value = 0;
  if (entry != (request_entry *)0x0) {
    do {
      if (*(short *)(entry->c + 2) == symx) {
        value = *(int *)entry->b;
        break;
      }
      entry = entry->next;
    } while (entry != (request_entry *)0x0);
    if (entry != (request_entry *)0x0) {
      *out = value;
      return 1;
    }
  }
  return 0;
}



