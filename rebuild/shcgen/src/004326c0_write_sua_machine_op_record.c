#include "decls.h"
#include "imports.h"

// entry: 004326c0
// name : write_sua_machine_op_record
// size : 264
// sig  : void write_sua_machine_op_record(FILE * out, psd * rec)


int __cdecl write_sua_machine_op_record(FILE *out,psd *rec)

{
  unsigned char _frec_1[1];
#define operand_count (*(char *)(_frec_1 + 0))
  char *buf;
  
  g_sua_filno = rec->filno;
  g_sua_linno = rec->linno;
  write_sua_bytes(out,(char *)&rec->filno,2);
  write_sua_bytes(out,(char *)&rec->linno,2);
  buf = &rec->flg;
  write_sua_bytes(out,(char *)&rec->expno,4);
  write_sua_bytes(out,buf,1);
  write_sua_bytes(out,&rec->misc,1);
  operand_count = rec->ea1 != (ea *)0x0;
  if (rec->ea2 != (ea *)0x0) {
    operand_count = operand_count + '\x01';
  }
  if ((&DAT_0045c3a1)[(uint)rec->op * 2] != operand_count) {
    report_compiler_message(g_sua_filno,(uint)g_sua_linno,0x1310,(char *)0x0);
  }
  write_sua_bytes(out,&operand_count,1);
  if (rec->ea1 != (ea *)0x0) {
    write_sua_operand(out,rec->ea1,*buf & 3);
  }
  if (rec->ea2 != (ea *)0x0) {
    write_sua_operand(out,rec->ea2,*buf & 3);
  }
  return;
#undef operand_count
}



