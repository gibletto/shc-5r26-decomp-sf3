#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_stage_flags
#define g_stage_flags (*(unsigned char *)(g_sd + 0x6d64))


// entry: 004144b0
// name : copy_label_ref_list
// size : 173
// sig  : label_ref * copy_label_ref_list(label_ref * src)


label_ref * __cdecl copy_label_ref_list(label_ref *src)

{
  label_ref *head;
  label_ref *new_ref;
  label_ref *src_ref;
  label_ref *tail;
  
  if (((byte)g_stage_flags & 8) != 0) {
    _printf(s_cpylab_start__lp___08lx_00427998,src);
    dump_memory_hex((uchar *)src,s_input_labtbl_00427988,8);
  }
  if (src != (label_ref *)0x0) {
    head = (label_ref *)alloc_zeroed_flushing_blocks(8);
    head->labno1 = src->labno1;
    head->labno2 = src->labno2;
    tail = head;
    for (src_ref = src->next; src_ref != (label_ref *)0x0; src_ref = src_ref->next) {
      new_ref = (label_ref *)alloc_zeroed_flushing_blocks(8);
      tail->next = new_ref;
      new_ref->labno1 = src_ref->labno1;
      new_ref->labno2 = src_ref->labno2;
      tail = new_ref;
    }
    if (((byte)g_stage_flags & 8) != 0) {
      dump_memory_hex((uchar *)tail,s_output_labtbl_00427978,8);
      _printf(s_cpylab_end__newlp___08lx_0042795c,tail);
    }
    return head;
  }
  return (label_ref *)0x0;
}



