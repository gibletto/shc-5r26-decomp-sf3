#include "decls.h"
#include "imports.h"

// entry: 00432380
// name : format_array_dimensions
// size : 129
// sig  : short __cdecl format_array_dimensions(char *mangled,char *dst,int *consumed)


short __cdecl format_array_dimensions(char *mangled,char *dst,int *consumed)

{
  unsigned char _frec_104[260];
#define codes_len (*(int *)(_frec_104 + 0))
#define dim_codes (*(char (*)[256])(_frec_104 + 4))
  char cVar1;
  short status;
  short i;
  char acStackY_8100 [32740];
  
  status = copy_array_dimension_codes(mangled,dim_codes,&codes_len);
  if (status == 0) {
    i = 0;
    while (dim_codes[0] != '\0') {
      cVar1 = dim_codes[i];
      if (cVar1 == 'A') {
        dst[i] = '[';
      }
      else {
        dst[i] = ']';
        if (cVar1 != '_') {
          dst[i] = cVar1;
        }
      }
      i = i + 1;
      dim_codes[0] = dim_codes[i];
    }
    dst[i] = '\0';
    *consumed = codes_len;
  }
  return status;
#undef codes_len
#undef dim_codes
}
