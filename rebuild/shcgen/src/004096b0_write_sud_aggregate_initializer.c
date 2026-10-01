#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_int_file
#define g_int_file (*(FILE * *)(g_sd + 0x1f98c))
#undef g_sud_const_dc_count_field
#define g_sud_const_dc_count_field (*(char * *)(g_sd + 0x1fe58))
#undef g_sud_data_dc_count_field
#define g_sud_data_dc_count_field (*(char * *)(g_sd + 0x1fa1c))
#undef g_symbol_table
#define g_symbol_table (*(sym_entry * *)(g_sd + 0x1f9b0))


// entry: 004096b0
// name : write_sud_aggregate_initializer
// size : 801
// sig  : int write_sud_aggregate_initializer(ushort elem_type)


int __cdecl write_sud_aggregate_initializer(ushort elem_type)

{
  unsigned char _frec_b[11];
#define gap_tag (*(char *)(_frec_b + 0))
#define gap_pad (*(char *)(_frec_b + 1))
#define next_type (*(byte *)(_frec_b + 2))
#define init_result (*(int *)(_frec_b + 3))
#define gap_size (*(int *)(_frec_b + 7))
  uint uVar1;
  int byte_i;
  ushort i;
  
  init_result = 0;
  g_sud_dc_run_closed = '\0';
  g_sud_dc_elem_type = elem_type;
  align_sud_location_counter();
  set_symbol_address_from_location_counter();
  write_sud_symbol_label();
  if (g_symbol_table[g_sud_symx].sclass == '\t') {
    init_result = write_sud_scalar_initializer(elem_type);
    skip_int_close_marker();
  }
  else {
    if (elem_type != 0xe0) {
      begin_sud_dc_record(elem_type);
    }
joined_r0x0040972b:
    if (0 < g_int_nesting_depth) {
      switch(elem_type) {
      case 0x98:
        g_sud_dc_elem_type = elem_type;
        init_result = write_sud_scalar_initializer(elem_type);
        read_bytes_or_fail((char *)&next_type,1,g_int_file);
        elem_type = (ushort)next_type;
        break;
      default:
        if ((elem_type != g_sud_dc_elem_type) || (g_sud_dc_run_closed == '\x01')) {
          g_sud_dc_run_closed = '\0';
          g_sud_dc_elem_type = elem_type;
          begin_sud_dc_record(elem_type);
          break;
        }
        uVar1 = (int)g_sud_symx >> 0x1f;
        if (((g_symbol_table[((int)g_sud_symx ^ uVar1) - uVar1].type & 1) == 0) ||
           ((g_symbol_table[((int)g_sud_symx ^ uVar1) - uVar1].type & 2) != 0)) {
          if (0xff < g_sud_dc_unit + g_sud_data_dc_count) {
            begin_sud_dc_record(elem_type);
            break;
          }
          i = 0;
          g_sud_data_dc_count = g_sud_dc_unit + g_sud_data_dc_count;
          do {
            byte_i = (int)(short)i;
            i = i + 1;
            g_sud_data_dc_count_field[byte_i] = *(char *)((int)&g_sud_data_dc_count + byte_i);
          } while (i < 4);
        }
        else {
          if (0xff < g_sud_dc_unit + g_sud_const_dc_count) {
            begin_sud_dc_record(elem_type);
            break;
          }
          i = 0;
          g_sud_const_dc_count = g_sud_dc_unit + g_sud_const_dc_count;
          do {
            byte_i = (int)(short)i;
            i = i + 1;
            g_sud_const_dc_count_field[byte_i] = *(char *)((int)&g_sud_const_dc_count + byte_i);
          } while (i < 4);
        }
        if (g_int_nesting_depth < 1) {
          return init_result;
        }
        init_result = write_sud_scalar_initializer(elem_type);
        read_bytes_or_fail((char *)&next_type,1,g_int_file);
        elem_type = (ushort)next_type;
        break;
      case 0xe0:
        read_bytes_or_fail((char *)&gap_size,4,g_int_file);
        gap_pad = '\0';
        gap_tag = '\t';
        append_sud_bytes(&gap_tag,1,'\0');
        append_sud_bytes(&gap_pad,1,'\0');
        append_sud_bytes((char *)&gap_size,4,'\0');
        advance_sud_location_counter(gap_size);
        uVar1 = (int)g_sud_symx >> 0x1f;
        if (((g_symbol_table[((int)g_sud_symx ^ uVar1) - uVar1].type & 1) == 0) ||
           ((g_symbol_table[((int)g_sud_symx ^ uVar1) - uVar1].type & 2) != 0)) {
          g_sud_data_dc_count = 0;
        }
        else {
          g_sud_const_dc_count = 0;
        }
        read_bytes_or_fail((char *)&next_type,1,g_int_file);
        g_sud_dc_run_closed = '\x01';
        elem_type = (ushort)next_type;
        break;
      case 0xe8:
        while (elem_type == 0xe8) {
          g_int_nesting_depth = g_int_nesting_depth + 1;
          read_bytes_or_fail((char *)&next_type,1,g_int_file);
          elem_type = (ushort)next_type;
        }
        break;
      case 0xf0:
        while (elem_type == 0xf0) {
          g_int_nesting_depth = g_int_nesting_depth + -1;
          if (g_int_nesting_depth < 1) {
            return init_result;
          }
          read_bytes_or_fail((char *)&next_type,1,g_int_file);
          elem_type = (ushort)next_type;
        }
      }
      goto joined_r0x0040972b;
    }
  }
  return init_result;
#undef gap_tag
#undef gap_pad
#undef next_type
#undef init_result
#undef gap_size
}



