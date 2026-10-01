#include "decls.h"
#include "imports.h"

// entry: 0041e200
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
  value = FID_conflict___getenv_lk(var_name);
  if (value != (char *)0x0) {
    ch = *value;
    if (ch == '\0') {
      g_env_directory[0] = ch;
      return g_env_directory;
    }
    len = 0;
    while ((ch != '\0' && (len < 0x74))) {
      g_env_directory[len] = value[len];
      len = len + 1;
      ch = value[len];
    }
    if (len == 0x74) {
      if (value[0x74] != '\0') {
        *ok = 0;
        return (char *)0x0;
      }
      if (g_env_directory[0x73] == '\\') {
        g_env_directory[0x74] = '\0';
        return g_env_directory;
      }
    }
    else {
      if (*(char *)(len + SD(0x004293d7)) == '\\') {
        g_env_directory[len] = '\0';
        return g_env_directory;
      }
      g_env_directory[len] = '\\';
      g_env_directory[len + 1] = '\0';
      result = g_env_directory;
    }
  }
  return result;
}



