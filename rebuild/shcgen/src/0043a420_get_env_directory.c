#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef DAT_0045e743
#define DAT_0045e743 (*(char *)(g_sd + 0x1e743))
#undef g_env_directory
#define g_env_directory (*(char *)(g_sd + 0x1e6d0))


// entry: 0043a420
// name : get_env_directory
// size : 182
// sig  : char * get_env_directory(char * var_name, int * ok)


char * __cdecl get_env_directory(char *var_name,int *ok)

{
  char *value;
  int len;
  char *result;
  char ch;
  
  result = (char *)0x0;
  *ok = 1;
  value = stock_getenv(var_name);
  if (value != (char *)0x0) {
    ch = *value;
    if (ch == '\0') {
      g_env_directory = ch;
      return &g_env_directory;
    }
    len = 0;
    while ((ch != '\0' && (len < 0x74))) {
      (&g_env_directory)[len] = value[len];
      len = len + 1;
      ch = value[len];
    }
    if (len == 0x74) {
      if (value[0x74] != '\0') {
        *ok = 0;
        return (char *)0x0;
      }
      if (DAT_0045e743 == '\\') {
        DAT_0045e744 = 0;
        return &g_env_directory;
      }
    }
    else {
      if (*(char *)(len + SD(0x0045e6cf)) == '\\') {
        (&g_env_directory)[len] = 0;
        return &g_env_directory;
      }
      (&g_env_directory)[len] = 0x5c;
      (&DAT_0045e6d1)[len] = 0;
      result = &g_env_directory;
    }
  }
  return result;
}



