#include "decls.h"
#include "imports.h"

// entry: 00423b80
// name : read_option_record
// size : 36
// sig  : void read_option_record(char * record, FILE * fp)


int __cdecl read_option_record(char *record,FILE *fp)

{
  uint result;
  
  result = read_bytes(fp,record,(int)g_option_record_size);
  check_read_result(result);
  return;
}



