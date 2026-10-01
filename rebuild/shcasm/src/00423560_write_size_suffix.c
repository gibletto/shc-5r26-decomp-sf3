#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef PTR_DAT_00441d98
#define PTR_DAT_00441d98 (*(unsigned char * *)(g_sd + 0x6d98))


// entry: 00423560
// name : write_size_suffix
// size : 41
// sig  : void __cdecl write_size_suffix(short stream,short size,short field)


int __cdecl write_size_suffix(short stream,short size,short field)

{
  put_text_at_column(stream,(&PTR_DAT_00441d98)[size],field);
  return;
}
