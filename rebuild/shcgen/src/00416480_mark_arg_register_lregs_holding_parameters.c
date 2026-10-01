#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_lreg_table
#define g_lreg_table (*(short * *)(g_sd + 0x1fa10))


// entry: 00416480
// name : mark_arg_register_lregs_holding_parameters
// size : 107
// sig  : void mark_arg_register_lregs_holding_parameters(void)


int __cdecl mark_arg_register_lregs_holding_parameters(void)

{
  int is_param;
  int ofs;
  int i;
  short *entry;
  short entry_id;
  
  entry_id = *g_lreg_table;
  entry = g_lreg_table;
  while (entry_id != 0) {
    ofs = 0;
    if ((((0 < entry[1]) && ((1 << ((byte)entry[1] & 0x1f) & 0xf0U) != 0)) && (entry[3] != 0)) &&
       (i = 0, 0 < entry[3])) {
      do {
        is_param = is_register_parameter_of_current_function
                             (*(short *)(*(int *)(entry + 4) + ofs) + 0xb6);
        if (is_param != 0) {
          *(byte *)((int)entry + 5) = *(byte *)((int)entry + 5) | 0x40;
        }
        ofs = ofs + 2;
        i = i + 1;
      } while (i < entry[3]);
    }
    entry = entry + 0x12;
    entry_id = *entry;
  }
  return;
}



