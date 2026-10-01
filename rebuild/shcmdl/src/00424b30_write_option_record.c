#include "decls.h"
#include "imports.h"

// entry: 00424b30
// name : write_option_record
// size : 36
// sig  : void write_option_record(char * record, FILE * fp)


int __cdecl write_option_record(char *record,FILE *fp)

{
  uint result;
  
  result = write_bytes(fp,record,(int)g_option_record_size);
  check_write_result(result);
  return;
}



