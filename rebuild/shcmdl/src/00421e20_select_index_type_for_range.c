#include "decls.h"
#include "imports.h"

// entry: 00421e20
// name : select_index_type_for_range
// size : 131
// sig  : uchar select_index_type_for_range(int max_index, int min_index, int offset, int elsize, int count, int has_offset)


uchar __cdecl
select_index_type_for_range
          (int max_index,int min_index,int offset,int elsize,int count,int has_offset)

{
  int *range;
  int i;
  uchar res;
  
  res = 0xff;
  range = &g_index_type_ranges;
  i = 0;
  do {
    if (has_offset == 0) {
LAB_00421e6d:
      if ((max_index <= *range) && (range[1] <= min_index)) {
        return *(uchar *)(i * 0xc + SD(0x00433850));
      }
    }
    else if (offset < 0) {
      if ((*range / offset < elsize) && (count < offset * elsize + *range)) goto LAB_00421e68;
    }
    else if (elsize < *range / offset) {
LAB_00421e68:
      res = '\x1c';
      goto LAB_00421e6d;
    }
    range = range + 3;
    i = i + 1;
    if ((int *)SD(0x00433883) < range) {
      return res;
    }
  } while( true );
}



