#include "decls.h"
#include "imports.h"

// entry: 00408b20
// name : dump_value_bytes
// size : 71
// sig  : void dump_value_bytes(uchar * bytes, int count)


int __cdecl dump_value_bytes(uchar *bytes,int count)

{
  int i;
  byte *p;
  
  i = 0;
  FID_conflict__wprintf(s_val__00434a7c);
  if (0 < count) {
    do {
      p = bytes + i;
      i = i + 1;
      FID_conflict__wprintf(&g_str_percent_02x,(uint)*p);
    } while (i < count);
  }
  FID_conflict__wprintf(&g_str_close_bracket);
  return;
}



