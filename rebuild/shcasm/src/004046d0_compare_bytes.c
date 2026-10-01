#include "decls.h"
#include "imports.h"

// entry: 004046d0
// name : compare_bytes
// size : 93
// sig  : int compare_bytes(char * a, char * b)


int __cdecl compare_bytes(char *a,char *b)

{
  int result;
  
  if (*b == *a) {
    result = 0;
  }
  else if (*a < *b) {
    result = -1;
  }
  else {
    result = 1;
  }
  return result;
}



