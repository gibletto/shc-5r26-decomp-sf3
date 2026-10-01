#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_asb_output
#define g_asb_output (*(FILE * *)(g_sd + 0x5d20))
#undef g_aux_record_table
#define g_aux_record_table (*(aux_record * *)(g_sd + 0x6d50))
#undef g_current_input_record
#define g_current_input_record (*(psd * *)(g_sd + 0x5bbc))
#undef g_current_symbol
#define g_current_symbol (*(symbol * *)(g_sd + 0x6d4c))
#undef g_last_symbol_record
#define g_last_symbol_record (*(symbol * *)(g_sd + 0x5d28))
#undef g_sua_input
#define g_sua_input (*(FILE * *)(g_sd + 0x5c00))
#undef g_sub_output
#define g_sub_output (*(FILE * *)(g_sd + 0x5bfc))
#undef g_symbol_records
#define g_symbol_records (*(symbol * *)(g_sd + 0x5d10))


// entry: 0040b560
// name : run_prep_pass_and_emit_backend_files
// size : 756
// sig  : void run_prep_pass_and_emit_backend_files(void)


int __cdecl run_prep_pass_and_emit_backend_files(void)

{
  unsigned char _frec_2[2];
#define ch (*(char *)(_frec_2 + 0))
#define out_byte (*(uchar *)(_frec_2 + 1))
  uint write_rc;
  byte kind;
  uint rc;
  
  rc = 0xffffffff;
  g_input_finished = 0;
  g_copy_rest_verbatim = 0;
  g_reuse_input_record = 0;
  g_current_input_record = alloc_zeroed(0x18);
  g_reg_remap_expno = 0;
  advance_sua_record_stream();
  while (g_input_finished != 1) {
    while ((g_in_program_section == 1 && (g_input_finished != 1))) {
      optimize_current_node_list();
    }
    advance_sua_record_stream();
    if (g_copy_rest_verbatim == 1) {
      write_sub_record(g_sub_output,g_current_input_record);
      while (rc != 0) {
        rc = read_file_bytes(g_sua_input,&ch,1);
        if (rc == 0xffffffff) {
          report_fatal_message(0,0,0xce6);
        }
        if (rc == 0) break;
        write_rc = write_file_bytes(g_sub_output,&ch,1);
        if (write_rc == 0xffffffff) {
          report_fatal_message(0,0,0xce7);
        }
      }
      g_input_finished = 1;
    }
  }
  write_asb_tag6_record();
  if (g_symbol_records <= g_last_symbol_record) {
    do {
      out_byte = g_symbol_records->attr;
      kind = g_symbol_records->type & 0x1f;
      if (6 < kind) {
        if (kind < 0xc) {
          g_current_symbol = g_symbol_records;
          write_asb_symbol_record();
          write_asb_symbol_name();
          rc = write_file_bytes(g_asb_output,(char *)&out_byte,1);
          if (rc == 0xffffffff) {
            report_fatal_message(0,0,0xce7);
          }
          out_byte = g_symbol_records->attr2;
          rc = write_file_bytes(g_asb_output,(char *)&out_byte,1);
        }
        else {
          if (kind != 0xc) goto LAB_0040b81d;
          g_current_symbol = g_symbol_records;
          write_asb_function_aux_record();
          write_asb_symbol_name();
          rc = write_file_bytes(g_asb_output,
                                (char *)&g_aux_record_table[g_current_symbol->aux_index].asb_word,4)
          ;
          if (rc == 0xffffffff) {
            report_fatal_message(0,0,0xce7);
          }
          rc = write_file_bytes(g_asb_output,(char *)&out_byte,1);
          if (rc == 0xffffffff) {
            report_fatal_message(0,0,0xce7);
          }
          rc = write_file_bytes(g_asb_output,
                                (char *)g_aux_record_table[g_current_symbol->aux_index].asb_bytes,
                                0x17);
          if (rc == 0xffffffff) {
            report_fatal_message(0,0,0xce7);
          }
          rc = write_file_bytes(g_asb_output,&g_aux_record_table[g_current_symbol->aux_index].reg28,
                                1);
        }
        if (rc == 0xffffffff) {
          report_fatal_message(0,0,0xce7);
        }
      }
LAB_0040b81d:
      g_symbol_records = g_symbol_records + 1;
    } while (g_symbol_records <= g_last_symbol_record);
  }
  write_asb_trailer_record();
  write_asb_label_count_record();
  pool_free(g_current_input_record,0x18);
  return;
#undef ch
#undef out_byte
}



