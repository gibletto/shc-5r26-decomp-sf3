#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_f_chain
#define g_f_chain (*(bblock * *)(g_sd + 0x26ad0))
#undef stock_stdout
#define stock_stdout (*(unsigned char * *)(g_sd + 0x40e8))


// entry: 0040c750
// name : dump_reaching_sets
// size : 436
// sig  : void dump_reaching_sets(void)


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __cdecl dump_reaching_sets(void)

{
  bblock *blk;
  uint *gen_bits;
  uint *in_bits;
  uint *kill_bits;
  uint *out_bits;
  bblock_sets *sets;
  
  for (blk = g_f_chain; blk != (bblock *)0x0; blk = blk->f_next) {
    sets = blk->sets;
    in_bits = blk->d_in;
    gen_bits = sets->gen;
    kill_bits = sets->kill;
    out_bits = sets->reach_out;
    FID_conflict__fwprintf
              ((FILE *)&stock_stdout,(wchar_t *)s_____Basic_Block_No_0ld_____004350f0,
               (int)blk->number);
    FID_conflict__fwprintf((FILE *)&stock_stdout,(wchar_t *)s_g_array___08lX_004350e0,gen_bits);
    dump_bitset(gen_bits,8,s_Current_Basic_Block_Gen_004350c8);
    _stock_stdout_cnt = _stock_stdout_cnt + -1;
    if (_stock_stdout_cnt < 0) {
      stock_flsbuf(10,(FILE *)&stock_stdout);
    }
    else {
      *stock_stdout = 10;
      stock_stdout = stock_stdout + 1;
    }
    _fflush((FILE *)&stock_stdout);
    FID_conflict__fwprintf((FILE *)&stock_stdout,(wchar_t *)s_k_array___08lX_004350b8,kill_bits);
    dump_bitset(kill_bits,8,s_Current_Basic_Block_Kill_0043509c);
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
    dump_bitset(in_bits,8,s_Current_Basic_Block_In_00435074);
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
    dump_bitset(out_bits,8,s_Current_Basic_Block_Out_0043504c);
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



