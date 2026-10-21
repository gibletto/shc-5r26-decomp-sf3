#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))
#undef g_layout_section_pass1
#define g_layout_section_pass1 (*(request_section * *)(g_sd + 0xcca4))

#if SHC_REBUILD_UPDATED
#include <stdlib.h>
/* ASM_CALL_SLACK=<n> (2nd Impact, 6; unset or 0 = Release 26): a forward call to a label in the same section counts
   n bytes nearer when bsr (4 bytes) or jsr through a pool literal (6 bytes plus the literal) is chosen. The choice
   that is emitted is made in the second layout pass, which measures a forward distance with the first pass's sizes
   for everything between the call and its target; the first pass counts some records bigger than the final code
   (forward conditional branches at their long form, forward calls as jsr with a literal, 2 bytes of alignment per
   literal pool), so a call whose final distance is in range can still get jsr. The 2nd Impact image has bsr where
   Release 26 picks jsr: 2i HITCHECK setup_catch_atthit -> dm_status_copy (06080E82) measures 4100 in the second
   pass against the 0xffe limit, so n >= 6. Same-file forward calls measured just over the limit that stay jsr in 2i
   bound it: Cut_Cut_Cut_t (4120) and end_fade_bgm (4124), so n <= 25. Every other call of the 2i build is unchanged
   with 6 and 8 (image byte-identical). */
static int asm_call_slack(void) {
    static int v = -1;
    if (v < 0) { char *p = getenv("ASM_CALL_SLACK"); v = (p && *p) ? atoi(p) : 0; }
    return v;
}
#endif


// entry: 004218bd
// name : relax_call_record
// size : 658
// sig  : void __cdecl relax_call_record(layout_record *item,int pass)


int __cdecl relax_call_record(layout_record *item,int pass)

{
  unsigned char _frec_1c[28];
#define label_hi (*(char *)(_frec_1c + 0))
#define label_lo (*(char *)(_frec_1c + 1))
#define pc_label (*(ushort (*)[2])(_frec_1c + 4))
#define branch_disp (*(int *)(_frec_1c + 8))
#define label_sym (*(symbol * *)(_frec_1c + 12))
#define new_size (*(char *)(_frec_1c + 16))
#define lab_ref (*(label_ref * *)(_frec_1c + 20))
  int is_word;
  
  new_size = '\0';
  if (pass == 0) {
    item->location = item->location - g_layout_shrink_pass0;
  }
  else {
    item->location = item->location - g_layout_shrink_pass1;
  }
  branch_disp = compute_branch_displacement(item,pass);
#if SHC_REBUILD_UPDATED
  if (branch_disp > 0 && branch_disp != 0x7fffffff) {   /* 0x7fffffff: another section or an external */
    branch_disp = branch_disp - asm_call_slack();
  }
#endif
  if ((branch_disp < -0x1000) || (0xffe < branch_disp)) {
    if (g_current_request->pic == 0) {
      if (pass == 1) {
        record_size_decision_byte('\x01');
      }
      new_size = new_size + '\x06';
      is_word = is_word_symbol_literal(item->value,item->labels);
      if (is_word == 0) {
        add_literal_to_pool_table(item->value,item->labels,pass,1);
      }
      else {
        add_literal_to_pool_table(item->value,item->labels,pass,0);
      }
    }
    else {
      if (pass == 1) {
        record_size_decision_byte('\x02');
        if (g_last_label_number == 0x7fff) {
          report_message_at_source_line(0,0,0xbc8,(char *)0x0);
        }
        g_last_label_number = g_last_label_number + 1;
        pc_label[0] = g_last_label_number;
        label_sym = create_symbol_entry('\x02','\0',g_last_label_number);
        label_sym->section_id = g_layout_section_pass1->id;
        store_u16_big_endian(pc_label,(ushort *)&label_hi);
        record_size_decision_byte(label_hi);
        record_size_decision_byte(label_lo);
      }
      else {
        pc_label[0] = g_literal_label_serial;
        g_literal_label_serial = g_literal_label_serial + 1;
      }
      if ((pass == 1) && (label_sym != (symbol *)0x0)) {
        label_sym->value = (int)(char)(new_size + '\x02') + item->location;
      }
      new_size = new_size + '\x06';
      lab_ref = pool_alloc(8);
      lab_ref->labno1 = item->labels->labno1;
      lab_ref->labno2 = -pc_label[0];
      add_literal_to_pool_table(0xfffffffc,lab_ref,pass,1);
      pool_free(lab_ref,8);
    }
  }
  else {
    if (pass == 1) {
      record_size_decision_byte('\0');
    }
    new_size = new_size + '\x04';
  }
  if (pass == 0) {
    g_layout_shrink_pass0 = g_layout_shrink_pass0 + ((int)item->size - (int)new_size);
  }
  else {
    g_layout_shrink_pass1 = g_layout_shrink_pass1 + ((int)item->size - (int)new_size);
  }
  item->size = new_size;
  return;
#undef label_hi
#undef label_lo
#undef pc_label
#undef branch_disp
#undef label_sym
#undef new_size
#undef lab_ref
}
