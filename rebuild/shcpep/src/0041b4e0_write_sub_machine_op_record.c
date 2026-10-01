#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_sub_linno
#define g_sub_linno (*(unsigned short *)(g_sd + 0x5360))


// entry: 0041b4e0
// name : write_sub_machine_op_record
// size : 264
// sig  : void write_sub_machine_op_record(FILE * out, psd * rec)


int __cdecl write_sub_machine_op_record(FILE *out,psd *rec)

{
  unsigned char _frec_1[1];
#define operand_count (*(uchar *)(_frec_1 + 0))
  char *flg_ptr;
  
  g_sub_filno = rec->filno;
  g_sub_linno = rec->linno;
  write_sub_bytes(out,(char *)&rec->filno,2);
  write_sub_bytes(out,(char *)&rec->linno,2);
  flg_ptr = &rec->flg;
  write_sub_bytes(out,(char *)&rec->expno,4);
  write_sub_bytes(out,flg_ptr,1);
  write_sub_bytes(out,&rec->misc,1);
  operand_count = rec->ea1 != (ea *)0x0;
  if (rec->ea2 != (ea *)0x0) {
    operand_count = operand_count + '\x01';
  }
  if (g_sub_record_format_table[(uint)rec->op * 2 + 1] != operand_count) {
    report_compiler_message(g_sub_filno,(uint)g_sub_linno,0x1310,(char *)0x0);
  }
  write_sub_bytes(out,(char *)&operand_count,1);
  if (rec->ea1 != (ea *)0x0) {
    write_sub_operand(out,rec->ea1,*flg_ptr & 3);
  }
  if (rec->ea2 != (ea *)0x0) {
    write_sub_operand(out,rec->ea2,*flg_ptr & 3);
  }
  return;
#undef operand_count
}



