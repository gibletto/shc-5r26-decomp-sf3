#include "decls.h"
#include "imports.h"

// entry: 0042b680
// name : read_count_or_fail
// size : 100
// sig  : uint read_count_or_fail(char * buf, uint size, FILE * in)


uint __cdecl read_count_or_fail(char *buf,uint size,FILE *in)

{
  short count_read;
  uint bytes_read;
  undefined2 extraout_var = 0;
  uint extraout_EAX;
  
  bytes_read = read_file_bytes(in,buf,size);
  count_read = (short)bytes_read;
  if (count_read == -1) {
    report_codegen_message(0xce6,1,0,0,(char *)0x0);
    return CONCAT22(extraout_var,0xffff);
  }
  if ((count_read != 0) && (bytes_read = (uint)count_read, bytes_read != size)) {
    (extraout_EAX = (uint)report_codegen_message(0x1252,1,0,0,(char *)0x0));
    bytes_read = extraout_EAX;
  }
  return CONCAT22((short)(bytes_read >> 0x10),count_read);
}



