#include "decls.h"
#include "imports.h"

// entry: 00430220
// name : push_demangle_token
// size : 37
// sig  : void __cdecl push_demangle_token(char *text,short *count)


int __cdecl push_demangle_token(char *text,short *count)

{
  int text_offset;
  
  text_offset = intern_token_text(text);
  g_demangle_tokens[*count].text = &g_demangle_token_pool + text_offset;
  *count = *count + 1;
  return;
}
