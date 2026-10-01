#include "decls.h"
#include "imports.h"

// entry: 00404d18
// name : quicksort_range
// size : 571
// sig  : void __cdecl quicksort_range(int first,int last,sort_context *ctx)


int __cdecl quicksort_range(int first,int last,sort_context *ctx)

{
  int cmp;
  void *pivot;
  int byte_no;
  int j;
  int i;
  undefined1 swap_byte;
  
  while( true ) {
    while( true ) {
      i = first;
      j = last;
      pivot = (void *)((first + (last - first) / 2 + -1) * ctx->size + (int)ctx->base);
      while ((0 < i && (i <= j))) {
        while (cmp = (*(code *)ctx->compare)((void *)(ctx->size * (i + -1) + (int)ctx->base),pivot),
              cmp < 0) {
          i = i + 1;
        }
        while (cmp = (*(code *)ctx->compare)(pivot,(void *)(ctx->size * (j + -1) + (int)ctx->base)),
              cmp < 0) {
          j = j + -1;
        }
        if (i <= j) {
          for (byte_no = 0; byte_no < ctx->size; byte_no = byte_no + 1) {
            swap_byte = *(undefined1 *)((int)ctx->base + byte_no + ctx->size * (i + -1));
            *(undefined1 *)((int)ctx->base + byte_no + ctx->size * (i + -1)) =
                 *(undefined1 *)((int)ctx->base + byte_no + ctx->size * (j + -1));
            *(undefined1 *)((int)ctx->base + byte_no + ctx->size * (j + -1)) = swap_byte;
          }
          if (first + (last - first) / 2 == i) {
            pivot = (void *)(ctx->size * (j + -1) + (int)ctx->base);
          }
          else if (first + (last - first) / 2 == j) {
            pivot = (void *)(ctx->size * (i + -1) + (int)ctx->base);
          }
          i = i + 1;
          j = j + -1;
        }
      }
      if (j - first < last - i) break;
      if (i < last) {
        quicksort_range(i,last,ctx);
      }
      if (j <= first) {
        return;
      }
      last = j;
    }
    if (first < j) {
      quicksort_range(first,j,ctx);
    }
    if (last <= i) break;
    first = i;
  }
  return;
}
