#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef DAT_0043fca3
#define DAT_0043fca3 (*(char *)(g_sd + 0xdca3))
#undef g_env_dir_buffer
#define g_env_dir_buffer (*(char *)(g_sd + 0xdc30))


// entry: 00428b10
// name : get_env_directory
// size : 182
// sig  : char * get_env_directory(char * var_name, int * ok)


char * __cdecl get_env_directory(char *var_name,int *ok)

{
  char *env;
  int i;
  char *result;
  char ch;
  
  result = (char *)0x0;
  *ok = 1;
  env = stock_getenv(var_name);
  if (env != (char *)0x0) {
    ch = *env;
    if (ch == '\0') {
      g_env_dir_buffer = ch;
      return &g_env_dir_buffer;
    }
    i = 0;
    while ((ch != '\0' && (i < 0x74))) {
      (&g_env_dir_buffer)[i] = env[i];
      i = i + 1;
      ch = env[i];
    }
    if (i == 0x74) {
      if (env[0x74] != '\0') {
        *ok = 0;
        return (char *)0x0;
      }
      if (DAT_0043fca3 == '\\') {
        DAT_0043fca4 = 0;
        return &g_env_dir_buffer;
      }
    }
    else {
      if (*(char *)(i + SD(0x0043fc2f)) == '\\') {
        (&g_env_dir_buffer)[i] = 0;
        return &g_env_dir_buffer;
      }
      (&g_env_dir_buffer)[i] = 0x5c;
      (&DAT_0043fc31)[i] = 0;
      result = &g_env_dir_buffer;
    }
  }
  return result;
}



