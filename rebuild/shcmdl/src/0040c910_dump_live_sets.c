#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_f_chain
#define g_f_chain (*(bblock * *)(g_sd + 0x26ad0))
#undef stock_stdout
#define stock_stdout (*(unsigned char * *)(g_sd + 0x40e8))


// entry: 0040c910
// name : dump_live_sets
// size : 437
// sig  : void dump_live_sets(void)


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl dump_live_sets(void)

{
  bblock *blk;
  uint *def_bits;
  uint *in_bits;
  uint *out_bits;
  uint *use_bits;
  
  for (blk = g_f_chain; blk != (bblock *)0x0; blk = blk->f_next) {
    in_bits = blk->l_in;
    use_bits = blk->sets->use;
    def_bits = blk->sets->def;
    out_bits = blk->out;
    FID_conflict__fwprintf
              ((FILE *)&stock_stdout,(wchar_t *)s_____Basic_Block_No_0ld_____00435160,
               (int)blk->number);
    FID_conflict__fwprintf((FILE *)&stock_stdout,(wchar_t *)s_u_array___08lX_00435150,use_bits);
    dump_bitset(use_bits,0x10,s_Current_Basic_Block_Use_00435138);
    _stock_stdout_cnt = _stock_stdout_cnt + -1;
    if (_stock_stdout_cnt < 0) {
      stock_flsbuf(10,(FILE *)&stock_stdout);
    }
    else {
      *stock_stdout = 10;
      stock_stdout = stock_stdout + 1;
    }
    _fflush((FILE *)&stock_stdout);
    FID_conflict__fwprintf((FILE *)&stock_stdout,(wchar_t *)s_d_array___08lX_00435128,def_bits);
    dump_bitset(def_bits,0x10,s_Current_Basic_Block_Def_00435110);
    _stock_stdout_cnt = _stock_stdout_cnt + -1;
    if (_stock_stdout_cnt < 0) {
      stock_flsbuf(10,(FILE *)&stock_stdout);
    }
    else {
      *stock_stdout = 10;
      stock_stdout = stock_stdout + 1;
    }
    _fflush((FILE *)&stock_stdout);
    FID_conflict__fwprintf((FILE *)&stock_stdout,(wchar_t *)s_i_array___08lX_0043508c,in_bits);
    dump_bitset(in_bits,0x10,s_Current_Basic_Block_In_00435074);
    _stock_stdout_cnt = _stock_stdout_cnt + -1;
    if (_stock_stdout_cnt < 0) {
      stock_flsbuf(10,(FILE *)&stock_stdout);
    }
    else {
      *stock_stdout = 10;
      stock_stdout = stock_stdout + 1;
    }
    _fflush((FILE *)&stock_stdout);
    FID_conflict__fwprintf((FILE *)&stock_stdout,(wchar_t *)s_o_array___08lX_00435064,out_bits);
    dump_bitset(out_bits,0x10,s_Current_Basic_Block_Out_0043504c);
    _stock_stdout_cnt = _stock_stdout_cnt + -1;
    if (_stock_stdout_cnt < 0) {
      stock_flsbuf(10,(FILE *)&stock_stdout);
    }
    else {
      *stock_stdout = 10;
      stock_stdout = stock_stdout + 1;
    }
    _fflush((FILE *)&stock_stdout);
  }
  return;
}



