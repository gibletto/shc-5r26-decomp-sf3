#include "decls.h"
#include "imports.h"

// entry: 004314e0
// name : find_operator_name_code
// size : 93
// sig  : short find_operator_name_code(uchar * name)


short __cdecl find_operator_name_code(uchar *name)

{
  byte bVar1;
  short i;
  int cmp;
  byte *name_pos;
  byte *table_pos;
  bool bVar2;
  bool found;
  
  i = 0;
  found = false;
  do {
    table_pos = (&g_mangle_operator_names)[i * 2];
    name_pos = name;
    do {
      bVar1 = *table_pos;
      bVar2 = bVar1 < *name_pos;
      if (bVar1 != *name_pos) {
LAB_00431518:
        cmp = (1 - (uint)bVar2) - (uint)(bVar2 != 0);
        goto LAB_0043151d;
      }
      if (bVar1 == 0) break;
      bVar1 = table_pos[1];
      bVar2 = bVar1 < name_pos[1];
      if (bVar1 != name_pos[1]) goto LAB_00431518;
      table_pos = table_pos + 2;
      name_pos = name_pos + 2;
    } while (bVar1 != 0);
    cmp = 0;
LAB_0043151d:
    if (cmp == 0) {
      found = true;
      goto LAB_0043152f;
    }
    i = i + 1;
    if (0x29 < i) {
LAB_0043152f:
      if (!found) {
        i = -1;
      }
      return i;
    }
  } while( true );
}



