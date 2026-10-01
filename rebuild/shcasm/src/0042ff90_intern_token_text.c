#include "decls.h"
#include "imports.h"

// entry: 0042ff90
// name : intern_token_text
// size : 63
// sig  : int intern_token_text(char * text)


int __cdecl intern_token_text(char *text)

{
  char cVar1;
  int text_start;
  int i;
  
  i = 0;
  cVar1 = *text;
  while (cVar1 != '\0') {
    (&g_demangle_token_pool)[i + g_demangle_token_pool_used] = text[i];
    i = i + 1;
    cVar1 = text[i];
  }
  text_start = g_demangle_token_pool_used;
  i = g_demangle_token_pool_used + i;
  g_demangle_token_pool_used = i + 1;
  (&g_demangle_token_pool)[i] = 0;
  return text_start;
}



