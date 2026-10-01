#include "decls.h"
#include "imports.h"

// entry: 00428ad0
// name : find_keyed_offset
// size : 62
// sig  : int find_keyed_offset(char * options, int key, int * value)


int __cdecl find_keyed_offset(char *options,int key,int *value)

{
  int *entry;
  int offset;
  
  if (options == (char *)0x0) {
    return 0;
  }
  entry = *(int **)(options + 0xc0);
  offset = 0;
  if (entry != (int *)0x0) {
    do {
      if (entry[1] == key) {
        offset = entry[2];
        break;
      }
      entry = (int *)*entry;
    } while (entry != (int *)0x0);
    if (entry != (int *)0x0) {
      *value = offset;
      return 1;
    }
  }
  return 0;
}



