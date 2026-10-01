#include "decls.h"
#include "imports.h"

// entry: 00404ce6
// name : sort_array
// size : 50
// sig  : void __cdecl sort_array(void *base,int count,int size,void *compare)


int __cdecl sort_array(void *base,int count,int size,void *compare)

{
  unsigned char _frec_10[16];
#define sort_ctx (*(sort_context *)(_frec_10 + 0))
  
  sort_ctx.base = base;
  sort_ctx.size = size;
  sort_ctx.compare = (int)compare;
  quicksort_range(1,count,&sort_ctx);
  return;
#undef sort_ctx
}
