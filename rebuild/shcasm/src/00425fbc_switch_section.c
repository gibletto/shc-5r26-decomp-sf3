#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef PTR_DAT_00441eb0
#define PTR_DAT_00441eb0 (*(unsigned char * *)(g_sd + 0x6eb0))
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))
#undef g_current_section
#define g_current_section (*(request_section * *)(g_sd + 0x10b2c))
#undef g_section_location_counters
#define g_section_location_counters (*(unsigned char * *)(g_sd + 0x1ef8))


// entry: 00425fbc
// name : switch_section
// size : 778
// sig  : void __cdecl switch_section(psd *rec)


int __cdecl switch_section(psd *rec)

{
  unsigned char _frec_28[40];
#define i (*(int *)(_frec_28 + 0))
#define section_name (*(char (*)[32])(_frec_28 + 4))
  psd_op section_op;
  
  if ((rec->filno == 2) || (rec->filno == 3)) {
    rec->op = OP_DATA;
  }
  section_op = rec->op;
  if (g_current_request->code == 1) {
    flush_reloc_records();
  }
  switch(section_op) {
  case OP_PRGRAM:
    g_current_section_kind = 0;
    break;
  case OP_CONST:
    g_current_section_kind = 1;
    break;
  case OP_DATA:
    g_current_section_kind = 2;
    break;
  case OP_BSS:
    g_current_section_kind = 3;
  }
  if (g_current_section != (request_section *)0x0) {
    for (i = 0; i < 4; i = i + 1) {
      g_current_section->layout->section_number[i] = g_section_numbers[i];
      g_current_section->layout->location[i] = *(int *)(&g_section_location_counters)[i];
      g_current_section->layout->object_offset[i] = *(int *)(&g_section_object_offsets + i * 4);
    }
  }
  g_current_section = find_section_by_id(g_current_request,rec->filno);
  for (i = 0; i < 4; i = i + 1) {
    g_section_numbers[i] = g_current_section->layout->section_number[i];
    *(int *)(&g_section_location_counters)[i] = g_current_section->layout->location[i];
    *(int *)(&g_section_object_offsets + i * 4) = g_current_section->layout->object_offset[i];
  }
  if (g_current_request->code == 1) {
    if ((g_current_request->show & 2) != 0) {
      format_listing_section_column(g_current_section_kind);
    }
  }
  else {
    put_text_at_column(2,s__SECTION_00441e40,1);
    build_section_name(section_name,g_current_section,g_current_section_kind);
    put_text_at_column(2,section_name,2);
    put_char_at_column(2,',',2);
    put_text_at_column(2,(&PTR_DAT_00441eb0)[g_current_section_kind],2);
    if (((g_current_request->flags_13d & 8) == 0) || (section_op != OP_PRGRAM)) {
      if ((g_current_request->align16 == '\0') || (section_op != OP_PRGRAM)) {
        if ((g_current_request->cpu == 4) && (section_op != OP_PRGRAM)) {
          put_text_at_column(2,s__ALIGN_8_00441e10,2);
        }
        else {
          put_text_at_column(2,s__ALIGN_4_00441e00,2);
        }
      }
      else {
        put_text_at_column(2,s__ALIGN_16_00441e20,2);
      }
    }
    else {
      put_text_at_column(2,s__ALIGN_32_00441e30,2);
    }
    flush_output_line(2);
  }
  return;
#undef i
#undef section_name
}
