#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_stage_flags
#define g_stage_flags (*(unsigned char *)(g_sd + 0x6d64))


// entry: 00407e70
// name : release_label_refs_of_record
// size : 142
// sig  : void release_label_refs_of_record(psd * rec, int mode)


int __cdecl release_label_refs_of_record(psd *rec,int mode)

{
  psd_op op;
  label_ref *ref;
  
  if (((byte)g_stage_flags & 8) != 0) {
    _printf(s_declab_start__004259b0);
  }
  if (((rec != (psd *)0x0) && (op = rec->op, op != OP_DUMMY)) &&
     ((((mode == 2 && (((op == OP_JUMP || (op == OP_JUMPT)) || (op == OP_JUMPF)))) ||
       (((mode == 1 && (op == OP_JUMP)) || (mode == 0)))) &&
      (((rec->ea1 != (ea *)0x0 && (ref = rec->ea1->labels, ref != (label_ref *)0x0)) &&
       (ref->labno1 != 0)))))) {
    for (; ref != (label_ref *)0x0; ref = ref->next) {
      decrement_label_ref_count(ref->labno1);
      if (ref->labno2 != 0) {
        decrement_label_ref_count(ref->labno2);
      }
    }
  }
  return;
}



