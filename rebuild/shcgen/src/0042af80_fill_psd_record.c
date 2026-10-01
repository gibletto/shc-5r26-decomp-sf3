#include "decls.h"
#include "imports.h"

// entry: 0042af80
// name : fill_psd_record
// size : 155
// sig  : void fill_psd_record(psd * rec, psd_op op, char flg, char misc, int expno, short filno, ushort linno, ea * ea1, ea * ea2, int sptravel, char tmp)


int __cdecl fill_psd_record(psd *rec,psd_op op,char flg,char misc,int expno,short filno,ushort linno,ea *ea1,
               ea *ea2,int sptravel,char tmp)

{
  rec->op = op;
  rec->flg = flg;
  rec->misc = misc;
  if ((op == OP_MOV_LOC) || (op == OP_MOVA_LC)) {
    rec->sptravel = sptravel;
  }
  else {
    rec->sptravel = 0;
  }
  if (((((op == OP_MOV_LOC) || (op == OP_MOVA_LC)) || (op == OP_CALL)) ||
      ((op == OP_JUMP || (op == OP_JUMPT)))) ||
     ((op == OP_JUMPF || ((op == OP_MOVA_FC || (op == OP_NON_2C)))))) {
    rec->tmp = tmp;
  }
  else {
    rec->tmp = -1;
  }
  rec->sptravel = sptravel;
  rec->filno = filno;
  rec->expno = expno;
  rec->linno = linno;
  rec->ea1 = ea1;
  rec->ea2 = ea2;
  return;
}



