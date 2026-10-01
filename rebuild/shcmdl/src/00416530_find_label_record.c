#include "decls.h"
#include "imports.h"

// entry: 00416530
// name : find_label_record
// size : 51
// sig  : label_rec * __cdecl find_label_record(short labno)


label_rec * __cdecl find_label_record(short labno)

{
  uint absno;
  uint sign;
  label_rec *rec;
  
  absno = (int)labno >> 0x1f;
  absno = ((int)labno ^ absno) - absno;
  sign = (int)absno >> 0x1f;
  for (rec = g_label_hash[((absno ^ sign) - sign & 0xff ^ sign) - sign];
      (rec != (label_rec *)0x0 && (rec->labno != labno)); rec = rec->next) {
  }
  return rec;
}
