#include "decls.h"
#include "imports.h"

// entry: 00424e70
// name : write_named_record_list
// size : 148
// sig  : void write_named_record_list(int * head, FILE * fp)


int __cdecl write_named_record_list(int *head,FILE *fp)

{
  unsigned char _frec_2[2];
#define cnt (*(short *)(_frec_2 + 0))
  char *buf;
  uint result;
  short name_len;
  int rec;
  
  cnt = 0;
  for (rec = *head; rec != 0; rec = *(int *)(rec + 0x1c)) {
    cnt = cnt + 1;
  }
  result = write_bytes(fp,(char *)&cnt,2);
  check_write_result(result);
  if (cnt != 0) {
    for (buf = (char *)*head; buf != (char *)0x0; buf = *(char **)(buf + 0x1c)) {
      name_len = *(short *)(buf + 2);
      result = write_bytes(fp,buf,0x20);
      check_write_result(result);
      if (*(short *)(buf + 2) != 0) {
        result = write_bytes(fp,*(char **)(buf + 4),(int)(short)(name_len + 1));
        check_write_result(result);
      }
    }
  }
  return;
#undef cnt
}



