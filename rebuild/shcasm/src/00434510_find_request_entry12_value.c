#include "decls.h"
#include "imports.h"

// entry: 00434510
// name : find_request_entry12_value
// size : 62
// sig  : int find_request_entry12_value(request * req, int key, int * value)


int __cdecl find_request_entry12_value(request *req,int key,int *value)

{
  request_entry *item;
  int found_value;
  
  if (req == (request *)0x0) {
    return 0;
  }
  item = req->entry12_list_0c0;
  found_value = 0;
  if (item != (request_entry *)0x0) {
    do {
      if (*(int *)item->a == key) {
        found_value = *(int *)item->c;
        break;
      }
      item = item->next;
    } while (item != (request_entry *)0x0);
    if (item != (request_entry *)0x0) {
      *value = found_value;
      return 1;
    }
  }
  return 0;
}



