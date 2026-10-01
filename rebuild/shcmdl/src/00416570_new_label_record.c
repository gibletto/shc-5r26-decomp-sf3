#include "decls.h"
#include "imports.h"

// entry: 00416570
// name : new_label_record
// size : 100
// sig  : label_rec * new_label_record(short labno)


label_rec * __cdecl new_label_record(short labno)

{
  label_rec *rec;
  uint absno;
  uint sign;
  label_rec *next;
  label_rec *tail;
  
  rec = pool_alloc(0x10);
  if (rec == (label_rec *)0x0) {
    cfg_out_of_memory();
  }
  absno = (int)labno >> 0x1f;
  absno = ((int)labno ^ absno) - absno;
  sign = (int)absno >> 0x1f;
  tail = g_label_hash[((absno ^ sign) - sign & 0xff ^ sign) - sign];
  if (tail != (label_rec *)0x0) {
    next = tail->next;
    while (next != (label_rec *)0x0) {
      tail = tail->next;
      next = tail->next;
    }
    tail->next = rec;
    rec->labno = labno;
    return rec;
  }
  g_label_hash[((absno ^ sign) - sign & 0xff ^ sign) - sign] = rec;
  rec->labno = labno;
  return rec;
}



