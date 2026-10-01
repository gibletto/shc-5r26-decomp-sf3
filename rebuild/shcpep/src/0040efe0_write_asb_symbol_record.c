#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_asb_output
#define g_asb_output (*(FILE * *)(g_sd + 0x5d20))
#undef g_current_symbol
#define g_current_symbol (*(symbol * *)(g_sd + 0x6d4c))


// entry: 0040efe0
// name : write_asb_symbol_record
// size : 131
// sig  : void write_asb_symbol_record(void)


int __cdecl write_asb_symbol_record(void)

{
  unsigned char _frec_c[12];
#define out_rec (*(byte *)(_frec_c + 0))
#define local_b (*(undefined1 *)(_frec_c + 1))
#define local_a (*(undefined1 *)(_frec_c + 2))
#define local_9 (*(undefined1 *)(_frec_c + 3))
#define local_8 (*(undefined1 *)(_frec_c + 4))
#define local_7 (*(undefined1 *)(_frec_c + 5))
#define local_6 (*(undefined1 *)(_frec_c + 6))
#define local_5 (*(undefined1 *)(_frec_c + 7))
#define local_4 (*(undefined1 *)(_frec_c + 8))
  uint written;
  
  out_rec = g_current_symbol->type | g_current_symbol->flags;
  local_b = (undefined1)g_current_symbol->number;
  local_a = *(undefined1 *)((int)&g_current_symbol->number + 1);
  local_9 = (undefined1)g_current_symbol->header_word;
  local_8 = *(undefined1 *)((int)&g_current_symbol->header_word + 1);
  local_7 = (undefined1)g_current_symbol->value;
  local_6 = *(undefined1 *)((int)&g_current_symbol->value + 1);
  local_5 = *(undefined1 *)((int)&g_current_symbol->value + 2);
  local_4 = *(undefined1 *)((int)&g_current_symbol->value + 3);
  written = write_file_bytes(g_asb_output,(char *)&out_rec,9);
  if (written == 0xffffffff) {
    report_fatal_message(0,0,0xce7);
  }
  return;
#undef out_rec
#undef local_b
#undef local_a
#undef local_9
#undef local_8
#undef local_7
#undef local_6
#undef local_5
#undef local_4
}



