#include "decls.h"
#include "imports.h"

// entry: 0042fe40
// name : copy_array_dimension_codes
// size : 90
// sig  : short copy_array_dimension_codes(char * src, char * dst, int * consumed)


short __cdecl copy_array_dimension_codes(char *src,char *dst,int *consumed)

{
  char cVar1;
  int i;
  bool terminated;
  
  terminated = false;
  i = 0;
  cVar1 = *src;
  do {
    if (cVar1 == '\0') {
LAB_0042fe79:
      if (!terminated) {
        return -1;
      }
      dst[i + 1] = '\0';
      *consumed = i + 1;
      return 0;
    }
    cVar1 = src[i];
    dst[i] = cVar1;
    if (cVar1 == '_') {
      cVar1 = (src + i)[1];
      if (cVar1 == '\0') goto LAB_0042fe79;
      if (cVar1 != 'A') {
        terminated = true;
        goto LAB_0042fe79;
      }
    }
    i = i + 1;
    cVar1 = src[i];
  } while( true );
}



