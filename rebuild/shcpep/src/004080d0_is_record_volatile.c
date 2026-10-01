#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_stage_flags
#define g_stage_flags (*(unsigned char *)(g_sd + 0x6d64))


// entry: 004080d0
// name : is_record_volatile
// size : 67
// sig  : uint is_record_volatile(psd * rec)


uint __cdecl is_record_volatile(psd *rec)

{
  uint rc;
  
  if (((byte)g_stage_flags & 0x10) != 0) {
    _printf(s_opvolchk_start__00425a74);
  }
  rc = (uint)((rec->flg & 0x80U) != 0);
  if (((byte)g_stage_flags & 0x10) != 0) {
    _printf(s_opvolchk_end__rc___ld_00425a5c,rc);
  }
  return rc;
}



