#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_section
#define g_current_section (*(request_section * *)(g_sd + 0x1f9b8))
#undef g_int_file
#define g_int_file (*(FILE * *)(g_sd + 0x1f98c))
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))
#undef g_sud_buffer_cursor
#define g_sud_buffer_cursor (*(char * *)(g_sd + 0x1f9f4))
#undef g_sud_buffer_start
#define g_sud_buffer_start (*(char * *)(g_sd + 0x1fe64))
#undef g_sud_file
#define g_sud_file (*(FILE * *)(g_sd + 0x1f9f0))
#undef g_symbol_table
#define g_symbol_table (*(sym_entry * *)(g_sd + 0x1f9b0))


// entry: 00408970
// name : write_sud_initialized_data
// size : 869
// sig  : void write_sud_initialized_data(void)


int __cdecl write_sud_initialized_data(void)

{
  unsigned char _frec_a[10];
#define const_tag (*(char *)(_frec_a + 0))
#define data_tag (*(char *)(_frec_a + 1))
#define saved_holds_data (*(char *)(_frec_a + 2))
#define any_written (*(char *)(_frec_a + 3))
#define in_attr_run (*(char *)(_frec_a + 4))
#define init_type (*(byte *)(_frec_a + 5))
#define sym_index (*(uint *)(_frec_a + 6))
  short sVar1;
  uint nread;
  uint uVar2;
  short saved_const_section;
  short saved_data_section;
  short *bytes;
  
  g_sud_hold_length = 0;
  const_tag = '\r';
  data_tag = '\x0e';
  any_written = '\0';
  in_attr_run = '\0';
  g_sud_const_section = 0;
  g_sud_data_section = 0;
  saved_data_section = (short)sym_index;
  saved_const_section = (short)sym_index;
  do {
    g_int_nesting_depth = 0;
    nread = read_count_or_fail((char *)&g_sud_symx,2,g_int_file);
    if ((short)nread == 0) break;
    g_sud_symx = g_sud_symx + 0xb6;
    read_bytes_or_fail((char *)&init_type,1,g_int_file);
    while (init_type == 0xe8) {
      g_int_nesting_depth = g_int_nesting_depth + 1;
      read_bytes_or_fail((char *)&init_type,1,g_int_file);
    }
    sym_index = (uint)g_sud_symx;
    uVar2 = (int)sym_index >> 0x1f;
    if ((g_symbol_table[sym_index].attr & 3) == 0) {
      if (in_attr_run != '\0') {
        sVar1 = saved_const_section;
        if (saved_holds_data != '\0') {
          sVar1 = g_sud_const_section;
          g_sud_data_section = saved_data_section;
        }
        g_sud_const_section = sVar1;
        in_attr_run = '\0';
        g_sud_buffer_holds_data = saved_holds_data;
      }
    }
    else {
      if (in_attr_run == '\0') {
        in_attr_run = '\x01';
        saved_holds_data = g_sud_buffer_holds_data;
        if (g_sud_buffer_holds_data == '\0') {
          g_sud_data_section = 0;
          saved_const_section = g_sud_const_section;
        }
        else {
          g_sud_const_section = 0;
          saved_data_section = g_sud_data_section;
        }
      }
      if (((g_symbol_table[(sym_index ^ uVar2) - uVar2].type & 1) == 0) ||
         ((g_symbol_table[(sym_index ^ uVar2) - uVar2].type & 2) != 0)) {
        g_sud_buffer_holds_data = '\0';
      }
      else {
        g_sud_buffer_holds_data = '\x01';
      }
    }
    if (((g_symbol_table[(sym_index ^ uVar2) - uVar2].type & 1) == 0) ||
       ((g_symbol_table[(sym_index ^ uVar2) - uVar2].type & 2) != 0)) {
      if ((g_sud_data_section == 0) || (g_symbol_table[sym_index].short_06 != g_sud_data_section)) {
        append_sud_bytes(&data_tag,1,'\0');
        g_current_section = find_section_record(g_request,g_symbol_table[g_sud_symx].short_06);
        g_sud_data_section = g_current_section->id;
        bytes = &g_sud_data_section;
        goto LAB_00408c49;
      }
      if (g_current_section->id != g_sud_data_section) {
        g_current_section = find_section_record(g_request,g_sud_data_section);
      }
    }
    else if ((g_sud_const_section == 0) ||
            (g_symbol_table[sym_index].short_06 != g_sud_const_section)) {
      if ((any_written == '\0') && (g_sud_buffer_holds_data == '\0')) {
        g_sud_buffer_holds_data = '\x01';
      }
      append_sud_bytes(&const_tag,1,'\0');
      g_current_section = find_section_record(g_request,g_symbol_table[g_sud_symx].short_06);
      g_sud_const_section = g_current_section->id;
      bytes = &g_sud_const_section;
LAB_00408c49:
      append_sud_bytes((char *)bytes,2,'\0');
    }
    else if (g_current_section->id != g_sud_const_section) {
      g_current_section = find_section_record(g_request,g_sud_const_section);
    }
    any_written = '\x01';
    write_sud_variable_initializer((ushort)init_type);
    g_symbol_table[g_sud_symx].flags = g_symbol_table[g_sud_symx].flags | 0x40;
  } while (0 < (short)nread);
  if (g_sud_hold_length != 0) {
    write_bytes_or_fail(&g_sud_hold_buffer,g_sud_hold_length,g_sud_file);
  }
  if (1 < (int)g_sud_buffer_cursor - (int)g_sud_buffer_start) {
    write_bytes_or_fail(g_sud_buffer_start,(int)g_sud_buffer_cursor - (int)g_sud_buffer_start,
                        g_sud_file);
  }
  return;
#undef const_tag
#undef data_tag
#undef saved_holds_data
#undef any_written
#undef in_attr_run
#undef init_type
#undef sym_index
}



