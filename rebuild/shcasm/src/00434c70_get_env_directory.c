#include "decls.h"
#include "imports.h"

// entry: 00434c70
// name : get_env_directory
// size : 182
// sig  : char * get_env_directory(char * var_name, int * ok)


char * __cdecl get_env_directory(char *var_name,int *ok)

{
  char *env_value;
  int i;
  char *result_dir;
  char ch;
  
  result_dir = (char *)0x0;
  *ok = 1;
  env_value = stock_getenv(var_name);
  if (env_value != (char *)0x0) {
    ch = *env_value;
    if (ch == '\0') {
      g_env_directory[0] = ch;
      return g_env_directory;
    }
    i = 0;
    while ((ch != '\0' && (i < 0x74))) {
      g_env_directory[i] = env_value[i];
      i = i + 1;
      ch = env_value[i];
    }
    if (i == 0x74) {
      if (env_value[0x74] != '\0') {
        *ok = 0;
        return (char *)0x0;
      }
      if (g_env_directory[0x73] == '\\') {
        g_env_directory[0x74] = '\0';
        return g_env_directory;
      }
    }
    else {
      if (*(char *)(i + SD(0x004474df)) == '\\') {
        g_env_directory[i] = '\0';
        return g_env_directory;
      }
      g_env_directory[i] = '\\';
      g_env_directory[i + 1] = '\0';
      result_dir = g_env_directory;
    }
  }
  return result_dir;
}



