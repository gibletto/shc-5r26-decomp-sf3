#include "decls.h"
#include "imports.h"

// entry: 0042b020
// name : fill_psd_record_without_sptravel
// size : 64
// sig  : void fill_psd_record_without_sptravel(psd * rec, psd_op op, char flg, char misc, int expno, short filno, ushort linno, ea * ea1, ea * ea2)


int __cdecl
fill_psd_record_without_sptravel
          (psd *rec,psd_op op,char flg,char misc,int expno,short filno,ushort linno,ea *ea1,ea *ea2)

{
  rec->op = op;
  rec->flg = flg;
  rec->misc = misc;
  rec->expno = expno;
  rec->filno = filno;
  rec->linno = linno;
  rec->ea1 = ea1;
  rec->ea2 = ea2;
  return;
}



