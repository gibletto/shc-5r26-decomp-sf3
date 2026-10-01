#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_builtin_function_names
#define g_builtin_function_names (*(unsigned char * *)(g_sd + 0x1220))


// entry: 00401c00
// name : lookup_builtin_function_id
// size : 130
// sig  : int lookup_builtin_function_id(char * name)


int __cdecl lookup_builtin_function_id(char *name)

{
  int cmp;
  short i;
  byte *entry_p;
  int id;
  byte *name_p;
  bool below;
  byte ch;
  undefined *entry_name;
  
  id = 0;
  cmp = stock_strncmp(name,s__builtin__004413b0,9);
  if (cmp == 0) {
    i = 0;
    entry_name = g_builtin_function_names;
    while ((entry_name != (undefined *)0x0 && (id == 0))) {
      name_p = (byte *)(name + 9);
      entry_p = (&g_builtin_function_names)[i * 2];
      do {
        ch = *name_p;
        below = ch < *entry_p;
        if (ch != *entry_p) {
LAB_00401c5c:
          cmp = (1 - (uint)below) - (uint)(below != 0);
          goto LAB_00401c61;
        }
        if (ch == 0) break;
        ch = name_p[1];
        below = ch < entry_p[1];
        if (ch != entry_p[1]) goto LAB_00401c5c;
        name_p = name_p + 2;
        entry_p = entry_p + 2;
      } while (ch != 0);
      cmp = 0;
LAB_00401c61:
      if (cmp == 0) {
        id = (int)(short)(&g_builtin_function_ids)[i * 4];
      }
      i = i + 1;
      entry_name = (&g_builtin_function_names)[i * 2];
    }
  }
  return id;
}



