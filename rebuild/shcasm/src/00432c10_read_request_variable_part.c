#include "decls.h"
#include "imports.h"

// entry: 00432c10
// name : read_request_variable_part
// size : 846
// sig  : void __cdecl read_request_variable_part(request *req,FILE *in)


int __cdecl read_request_variable_part(request *req,FILE *in)

{
  unsigned char _frec_2[2];
#define format_version (*(short *)(_frec_2 + 0))
  request_cpp_block **block;
  uint result;
  int cmp;
  byte *str;
  char *expected;
  bool below;
  byte ch;
  
  result = read_file_bytes(in,(char *)&format_version,2);
  check_request_read_result(result);
  read_request_string(&req->source_name,in);
  read_request_string(&req->temp_list_path,in);
  read_request_string(&req->object_path,in);
  read_request_string(&req->section_program,in);
  read_request_string(&req->section_const,in);
  read_request_string(&req->section_data,in);
  read_request_string(&req->section_bss,in);
  read_request_string(&req->message_path,in);
  read_request_string(&req->ila_path,in);
  read_request_string(&req->ilb_path,in);
  read_request_string(&req->sym_path,in);
  read_request_string(&req->swi_path,in);
  read_request_string(&req->int_path,in);
  read_request_string(&req->db1_path,in);
  read_request_string(&req->db2_path,in);
  read_request_string(&req->reg_path,in);
  read_request_string(&req->sua_path,in);
  read_request_string(&req->sub_path,in);
  read_request_string(&req->sud_path,in);
  read_request_string(&req->ofa_path,in);
  read_request_string(&req->ofb_path,in);
  read_request_string(&req->asa_path,in);
  read_request_string(&req->asb_path,in);
  read_request_string(&req->asl_path,in);
  read_request_string(&req->lit_path,in);
  read_request_string(&req->log_path,in);
  read_request_string(&req->list_path,in);
  read_request_string(&req->extra_temp,in);
  read_request_string(&req->compiler_version,in);
  block = &req->cpp_block;
  read_request_string(&req->copyright,in);
  if (*block == (request_cpp_block *)0x0) {
    str = (byte *)req->compiler_version;
    expected = s_request_compiler_version;
    do {
      ch = *str;
      below = ch < (byte)*expected;
      if (ch != *expected) {
LAB_00432e1e:
        cmp = (1 - (uint)below) - (uint)(below != 0);
        goto LAB_00432e23;
      }
      if (ch == 0) break;
      ch = str[1];
      below = ch < (byte)expected[1];
      if (ch != expected[1]) goto LAB_00432e1e;
      str = str + 2;
      expected = expected + 2;
    } while (ch != 0);
    cmp = 0;
LAB_00432e23:
    if (cmp == 0) {
      str = (byte *)req->copyright;
      expected = s_request_copyright;
      do {
        ch = *str;
        below = ch < (byte)*expected;
        if (ch != *expected) {
LAB_00432e4f:
          cmp = (1 - (uint)below) - (uint)(below != 0);
          goto LAB_00432e54;
        }
        if (ch == 0) break;
        ch = str[1];
        below = ch < (byte)expected[1];
        if (ch != expected[1]) goto LAB_00432e4f;
        str = str + 2;
        expected = expected + 2;
      } while (ch != 0);
      cmp = 0;
LAB_00432e54:
      if (cmp == 0) goto LAB_00432e63;
    }
    g_request_version_mismatch = 1;
  }
  else {
LAB_00432e63:
    g_request_version_mismatch = 0;
  }
  if (format_version != 0x1e) {
    report_message_by_code(req->source_name,0,0x12c1,(char *)0x0);
    stock_exit(0xb);
  }
  req->sections = (request_section *)0x0;
  read_request_section_list(&req->sections,in);
  req->defines = (request_string *)0x0;
  read_request_string_list_040(&req->defines,in);
  req->include_dirs = (request_string12 *)0x0;
  read_request_string_list_048(&req->include_dirs,in);
  req->preincludes = (request_sized_string *)0x0;
  read_request_sized_string_list(&req->preincludes,in);
  req->source_files = (request_source_file *)0x0;
  read_request_source_file_list(&req->source_files,in);
  req->entry11_list_0b8 = (request_entry *)0x0;
  read_request_11byte_entry_list(&req->entry11_list_0b8,in);
  req->entry11_list_0bc = (request_entry *)0x0;
  read_request_11byte_entry_list(&req->entry11_list_0bc,in);
  req->entry12_list_0c0 = (request_entry *)0x0;
  read_request_12byte_entry_list(&req->entry12_list_0c0,in);
  *block = (request_cpp_block *)0x0;
  read_request_cpp_block(block,in);
  read_request_string(&req->obl_path,in);
  return;
#undef format_version
}
