#include "decls.h"
#include "imports.h"

// entry: 0042b730
// name : copy_ea
// size : 56
// sig  : ea * copy_ea(ea * src)


ea * __cdecl copy_ea(ea *src)

{
  ea *dst;
  
  dst = alloc_zeroed(0xc);
  if (dst == (ea *)0x0) {
    report_codegen_message(0xbcd,1,0,0,(char *)0x0);
  }
  copy_ea_into(dst,src);
  return dst;
}



