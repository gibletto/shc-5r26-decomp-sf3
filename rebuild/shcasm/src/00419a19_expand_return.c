#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_lit_input
#define g_lit_input (*(FILE * *)(g_sd + 0x10c84))


// entry: 00419a19
// name : expand_return
// size : 367
// sig  : void __cdecl expand_return(psd *rec)


int __cdecl expand_return(psd *rec)

{
  unsigned char _frec_20[32];
#define tail_rec (*(psd *)(_frec_20 + 0))
#define lit_byte (*(char (*)[4])(_frec_20 + 24))
  short saved_count;
  symbol *func_sym;
  uint nread;
  
  func_sym = find_symbol_by_id(g_function_label);
  saved_count = count_saved_registers(func_sym->aux_index);
  if (saved_count < 2) {
    set_psd_record(&tail_rec,'!','\x02','\0','\0',0,rec->expno,rec->filno,rec->linno);
    tail_rec.ea1 = (ea *)0x0;
    tail_rec.ea2 = (ea *)0x0;
    tail_rec.flg = tail_rec.flg | 0x10;
    expand_exit_epilogue(&tail_rec);
  }
  else {
    set_psd_record(&tail_rec,'$','\x02','\0','\x01',0,rec->expno,rec->filno,rec->linno);
    tail_rec.ea1 = rec->ea1;
    rec->ea1 = (ea *)0x0;
    tail_rec.ea2 = (ea *)0x0;
    tail_rec.flg = tail_rec.flg | 0x10;
    expand_jump(&tail_rec);
  }
  if ((rec->flg & 0x10) == 0) {
    nread = read_file_bytes(g_lit_input,lit_byte,1);
    if (nread == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    if (lit_byte[0] == '\x01') {
      g_expanded_records[g_expanded_record_count + -1].flg =
           g_expanded_records[g_expanded_record_count + -1].flg | 0x10;
    }
  }
  return;
#undef tail_rec
#undef lit_byte
}
