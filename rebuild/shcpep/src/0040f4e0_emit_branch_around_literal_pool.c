#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_section
#define g_current_section (*(request_section * *)(g_sd + 0x5d0c))
#undef g_ofb_output
#define g_ofb_output (*(FILE * *)(g_sd + 0x5cf8))
#undef g_sub_output
#define g_sub_output (*(FILE * *)(g_sd + 0x5bfc))


// entry: 0040f4e0
// name : emit_branch_around_literal_pool
// size : 506
// sig  : void emit_branch_around_literal_pool(psd * rec, short pool_size, int sptravel)


/* WARNING: Heritage AFTER dead removal. Example location: s0xfffffffc : 0x0040f5bd */
/* WARNING: Restarted to delay deadcode elimination for space: stack */

int __cdecl emit_branch_around_literal_pool(psd *rec,short pool_size,int sptravel)

{
  unsigned char _frec_2c[44];
#define local_2c (*(psd *)(_frec_2c + 0))
#define local_14 (*(label_ref *)(_frec_2c + 24))
#define local_c (*(ea *)(_frec_2c + 32))
  short code_size;
  short sVar1;
  uint uVar2;
  symbol *sym;
  int i;
  undefined4 *src;
  psd *dst;
  undefined4 word_val;
  
  local_14.next = g_label_ref_template.next;
  (*(unsigned int *)((char *)&local_14 + 4)) = (*(unsigned int *)((char *)&g_label_ref_template + 4));
  (*(unsigned int *)((char *)&local_c + 0)) = (*(unsigned int *)((char *)&g_ea_template + 0));
  local_c.disp = g_ea_template.disp;
  local_c.labels = g_ea_template.labels;
  src = &g_empty_psd;
  dst = &local_2c;
  for (i = 6; i != 0; i = i + -1) {
    word_val = *src;
    dst->op = (char)word_val;
    dst->flg = (char)((uint)word_val >> 8);
    dst->misc = (char)((uint)word_val >> 0x10);
    dst->tmp = (char)((uint)word_val >> 0x18);
    src = src + 1;
    dst = (psd *)&dst->sptravel;
  }
  uVar2 = make_new_label_number();
  sVar1 = (short)uVar2;
  if (sVar1 == 0) {
    report_fatal_message(0,0,0xbc8);
  }
  local_2c.op = OP_BRA;
  local_2c.flg = '\x02';
  local_2c.misc = '\0';
  local_2c.tmp = -1;
  local_2c.sptravel = 0;
  local_2c.expno = rec->expno;
  local_2c.ea1 = &local_c;
  local_c.labels = &local_14;
  local_2c.filno = rec->filno;
  local_2c.linno = rec->linno;
  local_2c.ea2 = (ea *)0x0;
  local_c.type = '\a';
                    /* WARNING: Ignoring partial resolution of indirect */
  local_c.base = -1;
                    /* WARNING: Ignoring partial resolution of indirect */
  local_c.index = -1;
                    /* WARNING: Ignoring partial resolution of indirect */
  local_c.misc = '\0';
  local_c.disp = 0;
  (local_c.labels)->labno1 = sVar1;
  i = (int)pool_size;
  (local_c.labels)->labno2 = 0;
  (local_c.labels)->next = (label_ref *)0x0;
  write_ofb_record(g_ofb_output,&local_2c,g_location_counter,i);
  write_sub_record(g_sub_output,&local_2c);
  code_size = compute_record_code_size(&local_2c);
  g_location_counter = g_location_counter + code_size;
  g_location_counter = g_location_counter + i;
  (local_2c.ea1)->labels = (label_ref *)0x0;
  local_2c.op = OP_LABEL;
  local_2c.flg = '\0';
  local_2c.tmp = -1;
  local_2c.expno = 0;
  local_2c.sptravel = sptravel;
  local_2c.filno = 0;
  local_2c.linno = 0;
  local_2c.ea1 = (ea *)(uVar2 & 0xffff);
  local_2c.ea2 = (ea *)0x0;
  sym = create_symbol_record('\x02','\0',sVar1);
  sym->header_word = g_current_section->id;
  write_ofb_record(g_ofb_output,&local_2c,g_location_counter,i);
  write_sub_record(g_sub_output,&local_2c);
  define_label_at_location_counter(&local_2c);
  sVar1 = compute_record_code_size(&local_2c);
  g_location_counter = g_location_counter + sVar1;
  return;
#undef local_2c
#undef local_14
#undef local_c
}



