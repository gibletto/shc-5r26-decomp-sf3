#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_options
#define g_options (*(option_record * *)(g_sd + 0x1e714))


// entry: 00419800
// name : source_file_name
// size : 60
// sig  : char * source_file_name(int filn)


char * __cdecl source_file_name(int filn)

{
  int *file_rec;
  
  file_rec = g_options->file_list;
  if (file_rec != (int *)0x0) {
    do {
      if ((short)file_rec[1] == filn) break;
      file_rec = (int *)*file_rec;
    } while (file_rec != (int *)0x0);
    if (file_rec != (int *)0x0) {
      copy_file_basename(&g_file_name_buf,(char *)file_rec[2]);
    }
  }
  return &g_file_name_buf;
}



