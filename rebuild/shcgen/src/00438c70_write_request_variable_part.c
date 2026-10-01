#include "decls.h"
#include "imports.h"

// entry: 00438c70
// name : write_request_variable_part
// size : 631
// sig  : void write_request_variable_part(request * req, FILE * out)


int __cdecl write_request_variable_part(request *req,FILE *out)

{
  unsigned char _frec_2[2];
#define version_tag (*(char (*)[2])(_frec_2 + 0))
  uint result;
  
  version_tag[0] = '\x1e';
  version_tag[1] = '\0';
  result = write_file_bytes(out,version_tag,2);
  check_request_write_result(result);
  write_request_string(&req->source_name,out);
  write_request_string(&req->string_038,out);
  write_request_string(&req->string_03c,out);
  write_request_string(&req->path_050,out);
  write_request_string(&req->path_054,out);
  write_request_string(&req->path_058,out);
  write_request_string(&req->path_05c,out);
  write_request_string(&req->message_path,out);
  write_request_string(&req->ila_path,out);
  write_request_string(&req->ilb_path,out);
  write_request_string(&req->sym_path,out);
  write_request_string(&req->swi_path,out);
  write_request_string(&req->int_path,out);
  write_request_string(&req->db1_path,out);
  write_request_string(&req->db2_path,out);
  write_request_string(&req->reg_path,out);
  write_request_string(&req->sua_path,out);
  write_request_string(&req->sub_path,out);
  write_request_string(&req->sud_path,out);
  write_request_string(&req->ofa_path,out);
  write_request_string(&req->ofb_path,out);
  write_request_string(&req->asa_path,out);
  write_request_string(&req->asb_path,out);
  write_request_string(&req->asl_path,out);
  write_request_string(&req->lit_path,out);
  write_request_string(&req->path_0a8,out);
  write_request_string(&req->string_114,out);
  write_request_string(&req->string_140,out);
  write_request_string(&req->compiler_version,out);
  write_request_string(&req->copyright,out);
  write_request_section_list(&req->sections,out);
  write_request_string_list_040(&req->string_list_040,out);
  write_request_string_list_048(&req->string_list_048,out);
  write_request_sized_string_list(&req->sized_string_list_04c,out);
  write_request_source_file_list(&req->source_files,out);
  write_request_11byte_entry_list(&req->entry11_list_0b8,out);
  write_request_11byte_entry_list(&req->entry11_list_0bc,out);
  write_request_12byte_entry_list(&req->entry12_list_0c0,out);
  write_request_cpp_block(&req->cpp_block,out);
  write_request_string(&req->string_15c,out);
  return;
#undef version_tag
}



