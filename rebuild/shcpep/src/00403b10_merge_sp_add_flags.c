#include "decls.h"
#include "imports.h"

// entry: 00403b10
// name : merge_sp_add_flags
// size : 67
// sig  : void merge_sp_add_flags(psd * from, psd * into)


int __cdecl merge_sp_add_flags(psd *from,psd *into)

{
  byte flags;
  int from_disp;
  int into_disp;
  
  from_disp = from->ea1->disp;
  flags = from->flg & 0x20U | into->flg;
  into_disp = into->ea1->disp;
  into->flg = flags;
  if (((0 < from_disp) && (into_disp < 0)) || ((from_disp < 0 && (0 < into_disp)))) {
    into->flg = flags | 8;
  }
  into->flg = into->flg | from->flg & 8U;
  return;
}



