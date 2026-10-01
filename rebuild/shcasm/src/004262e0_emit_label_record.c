#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef PTR_DAT_00441ee4
#define PTR_DAT_00441ee4 (*(unsigned char * *)(g_sd + 0x6ee4))
#undef g_aux_record_table
#define g_aux_record_table (*(aux_record * *)(g_sd + 0x10c74))
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))
#undef g_section_location_counters
#define g_section_location_counters (*(unsigned char * *)(g_sd + 0x1ef8))


// entry: 004262e0
// name : emit_label_record
// size : 1589
// sig  : void __cdecl emit_label_record(psd *rec)


int __cdecl emit_label_record(psd *rec)

{
  unsigned char _frec_124[292];
#define out_channel (*(short *)(_frec_124 + 0))
#define bit (*(int *)(_frec_124 + 4))
#define routine_group (*(int *)(_frec_124 + 8))
#define save_area_bytes (*(int *)(_frec_124 + 16))
#define mangled_name (*(char *)(_frec_124 + 24))
#define mangled_rest (*(uint (*)[63])(_frec_124 + 25))
#define demangled (*(char * *)(_frec_124 + 280))
#define labno (*(short *)(_frec_124 + 284))
  short sVar1;
  symbol *sym;
  bool first_routine;
  uchar used_bits;
  
  first_routine = true;
  labno = *(short *)&rec->ea1;
  sym = find_symbol_by_id(labno);
  if ((sym->kind & 0x1f) == 1) {
    sVar1 = count_saved_registers(sym->aux_index);
    save_area_bytes = sVar1 * 4;
    if (((int)(short)g_aux_record_table[sym->aux_index].flags & 0x8000U) == 0) {
      save_area_bytes = save_area_bytes + 4;
    }
    if ((g_aux_record_table[sym->aux_index].flags & 0x1800) != 0) {
      save_area_bytes = save_area_bytes + 4;
    }
    if (0x7fffffff - save_area_bytes < g_aux_record_table[sym->aux_index].max_stack) {
      report_message_at_source_line(rec->filno,(uint)rec->linno,0xc84,(char *)0x0);
    }
  }
  if ((g_current_section_kind == 0) && (*(int *)g_section_location_counters != sym->value)) {
    emit_alignment_fill((-(uint)(g_current_request->align16 == '\0') & 0x10) + 0x10,
                        sym->value - *(int *)g_section_location_counters);
  }
  if ((g_current_request->code != 1) || ((g_current_request->show & 2) != 0)) {
    if ((g_current_request->show & 2) == 0) {
      out_channel = 2;
    }
    else {
      format_listing_location(*(int *)(&g_section_location_counters)[g_current_section_kind]);
      out_channel = 3;
    }
    write_label_name(out_channel,labno,0);
    switch(sym->kind & 0x1f) {
    case 0:
      break;
    case 1:
      if (sym->name != (char *)0x0) {
        put_text_at_column(out_channel,PTR_s___function__00441ee0,3);
        if (g_current_request->cpp_block == (request_cpp_block *)0x0) {
          put_text_at_column(out_channel,sym->name,3);
        }
        else {
          mangled_name = '_';
          stock_strcpy(mangled_rest,(uint *)sym->name);
          demangled = (char *)0x0;
          sVar1 = demangle_cpp_symbol_name(&mangled_name,&demangled);
          if (sVar1 == 0) {
            put_text_at_column(out_channel,demangled,3);
          }
          else {
            put_text_at_column(out_channel,&mangled_name,3);
          }
        }
      }
      flush_output_line(out_channel);
      put_text_at_column(out_channel,s___frame_size__00441f48,3);
      write_decimal(out_channel,save_area_bytes + g_aux_record_table[sym->aux_index].max_stack,3);
      for (routine_group = 0;
          (routine_group < 0x17 &&
          (g_aux_record_table[sym->aux_index].runtime_routines_used[routine_group] == '\0'));
          routine_group = routine_group + 1) {
      }
      if (routine_group != 0x17) {
        flush_output_line(out_channel);
        put_text_at_column(out_channel,s___used_runtime_library_name__00441f58,3);
        flush_output_line(out_channel);
        put_char_at_column(out_channel,';',3);
        for (routine_group = 0; routine_group < 0x17; routine_group = routine_group + 1) {
          used_bits = g_aux_record_table[sym->aux_index].runtime_routines_used[routine_group];
          if (used_bits != '\0') {
            for (bit = 0; bit < 8; bit = bit + 1) {
              if ((1 << (7U - (char)bit & 0x1f) & (int)(char)used_bits) != 0) {
                if (first_routine) {
                  first_routine = false;
                }
                else {
                  put_char_at_column(out_channel,',',3);
                }
                put_text_at_column(out_channel,&s_sp_us_00441f78,3);
                put_text_at_column(out_channel,(&PTR_s__divbs_0043cb24)[routine_group * 8 + bit],3);
              }
            }
          }
        }
      }
      break;
    case 2:
    case 0x10:
      put_text_at_column(out_channel,PTR_DAT_00441ee4,3);
      break;
    case 3:
      put_text_at_column(out_channel,PTR_s___case_label_00441ee8,3);
      break;
    case 4:
      put_text_at_column(out_channel,PTR_s___default_label_00441eec,3);
      break;
    case 5:
      if (sym->name != (char *)0x0) {
        put_text_at_column(out_channel,PTR_s___label__00441ef0,3);
        put_text_at_column(out_channel,sym->name,3);
      }
      break;
    case 6:
      break;
    case 7:
    case 8:
    case 9:
      if (sym->name != (char *)0x0) {
        put_text_at_column(out_channel,PTR_s___static__00441ef4,3);
        put_text_at_column(out_channel,sym->name,3);
      }
      break;
    case 10:
    case 0xb:
    case 0xc:
    case 0xd:
    case 0xe:
    case 0xf: ;
    }
    flush_output_line(out_channel);
  }
  return;
#undef out_channel
#undef bit
#undef routine_group
#undef save_area_bytes
#undef mangled_name
#undef mangled_rest
#undef demangled
#undef labno
}
