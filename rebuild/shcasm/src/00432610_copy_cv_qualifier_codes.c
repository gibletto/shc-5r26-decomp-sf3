#include "decls.h"
#include "imports.h"

// entry: 00432610
// name : copy_cv_qualifier_codes
// size : 80
// sig  : int copy_cv_qualifier_codes(char * mangled, char * dst, int * consumed)


int __cdecl copy_cv_qualifier_codes(char *mangled,char *dst,int *consumed)

{
  int result;
  int n;
  char ch;
  bool saw_function;
  
  result = 0;
  saw_function = false;
  n = 0;
  ch = *mangled;
  do {
    if (ch == '\0') {
LAB_00432649:
      if (!saw_function) {
        result = 0xffff;
      }
      dst[n] = '\0';
      *consumed = n;
      return result;
    }
    ch = mangled[n];
    if ((ch != 'C') && (ch != 'V')) {
      if (mangled[n] == 'F') {
        saw_function = true;
      }
      goto LAB_00432649;
    }
    dst[n] = ch;
    n = n + 1;
    ch = mangled[n];
  } while( true );
}



