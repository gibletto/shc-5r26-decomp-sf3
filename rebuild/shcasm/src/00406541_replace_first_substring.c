#include "decls.h"
#include "imports.h"

// entry: 00406541
// name : replace_first_substring
// size : 291
// sig  : char * replace_first_substring(char * str, char * find, char * repl)


char * __cdecl replace_first_substring(char *str,char *find,char *repl)

{
  uint str_len;
  uint find_len;
  char *result;
  uint repl_len;
  char *match;
  char *out;
  
  str_len = stock_strlen(str);
  find_len = stock_strlen(find);
  if ((int)str_len < (int)find_len) {
    result = (char *)0x0;
  }
  else {
    repl_len = stock_strlen(repl);
    match = find_substring(str,find);
    if (match == (char *)0x0) {
      result = (char *)0x0;
    }
    else {
      result = stock_malloc((str_len - find_len) + repl_len + 1);
      out = result;
      if (result == (char *)0x0) {
        result = (char *)0x0;
      }
      else {
        for (; str < match; str = str + 1) {
          *out = *str;
          out = out + 1;
        }
        for (; *repl != '\0'; repl = repl + 1) {
          *out = *repl;
          out = out + 1;
        }
        for (str = str + find_len; *str != '\0'; str = str + 1) {
          *out = *str;
          out = out + 1;
        }
        *out = '\0';
      }
    }
  }
  return result;
}



