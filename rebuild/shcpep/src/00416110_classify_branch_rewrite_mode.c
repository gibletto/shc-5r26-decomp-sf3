#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_aux_record_table
#define g_aux_record_table (*(aux_record * *)(g_sd + 0x6d50))


// entry: 00416110
// name : classify_branch_rewrite_mode
// size : 90
// sig  : short classify_branch_rewrite_mode(psd * rec)


short __cdecl classify_branch_rewrite_mode(psd *rec)

{
  short saved_count;
  aux_record *aux;
  
  saved_count = count_function_saved_registers();
  if ((rec->op == OP_EXIT) || ((rec->op == OP_RETURN && (saved_count < 2)))) {
    aux = g_aux_record_table + g_current_aux_index;
    if ((aux->flags & 0x3800) == 0) {
      if ((saved_count == 0) &&
         (((aux->flags & 0x8000) == 0 || (aux->sp_adjust + aux->frame_size == 0)))) {
        return 1;
      }
      return 0;
    }
    saved_count = 0;
  }
  return saved_count;
}



