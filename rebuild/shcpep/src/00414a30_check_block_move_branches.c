#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_stage_flags
#define g_stage_flags (*(unsigned char *)(g_sd + 0x6d64))


// entry: 00414a30
// name : check_block_move_branches
// size : 265
// sig  : short check_block_move_branches(code_node * block, code_node * last_block, code_node * jump_source)


short __cdecl check_block_move_branches(code_node *block,code_node *last_block,code_node *jump_source)

{
  short sVar1;
  psd *block_jump;
  psd *last_jump;
  psd *ppVar2;
  short block_dest;
  short source_dest;
  
  if (((byte)g_stage_flags & 0x10) != 0) {
    _printf(s_sc_brchk_start__00427a94);
  }
  if (((block->labno == jump_source->target_labno) && (block->target_labno != 0)) &&
     (last_block->target_labno != 0)) {
    block_jump = find_block_label_jump(block);
    if (block_jump != (psd *)0x0) {
      last_jump = find_block_label_jump(last_block);
      if (last_jump != (psd *)0x0) {
        ppVar2 = find_block_label_jump(jump_source);
        if (ppVar2 != (psd *)0x0) {
          sVar1 = last_jump->ea1->labels->labno1;
          block_dest = block_jump->ea1->labels->labno1;
          if (((sVar1 != block_dest) &&
              (source_dest = ppVar2->ea1->labels->labno1, source_dest != sVar1)) &&
             ((source_dest != block_dest &&
              ((sVar1 = *(short *)&block->psd[0].ea1, source_dest == sVar1 &&
               (block->psd[0].op == OP_LABEL)))))) {
            sVar1 = check_label_movable(sVar1);
            if (sVar1 != 0) {
              if (((byte)g_stage_flags & 0x10) != 0) {
                _printf(s_sc_brchk_end__rc___d_00427a7c,1);
              }
              return 1;
            }
          }
        }
      }
    }
  }
  if (((byte)g_stage_flags & 0x10) != 0) {
    _printf(s_sc_brchk_end__rc___d_00427a7c,0);
  }
  return 0;
}



