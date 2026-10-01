#include "decls.h"
#include "imports.h"

// entry: 0041cd10
// name : read_request_variable_part
// size : 846
// sig  : void read_request_variable_part(request * req, FILE * in)


int __cdecl read_request_variable_part(request *req,FILE *in)

{
  unsigned char _frec_2[2];
#define version_tag (*(short *)(_frec_2 + 0))
  request_cpp_block **block;
  uint result;
  int cmp;
  byte *s1;
  char *s2;
  bool below;
  byte ch;
  
  result = read_file_bytes(in,(char *)&version_tag,2);
  check_request_read_result(result);
  read_request_string(&req->source_name,in);
  read_request_string(&req->string_038,in);
  read_request_string(&req->string_03c,in);
  read_request_string(&req->path_050,in);
  read_request_string(&req->path_054,in);
  read_request_string(&req->path_058,in);
  read_request_string(&req->path_05c,in);
  read_request_string(&req->message_path,in);
  read_request_string(&req->path_064,in);
  read_request_string(&req->path_068,in);
  read_request_string(&req->path_06c,in);
  read_request_string(&req->path_070,in);
  read_request_string(&req->path_074,in);
  read_request_string(&req->path_078,in);
  read_request_string(&req->path_07c,in);
  read_request_string(&req->path_080,in);
  read_request_string(&req->sua_path,in);
  read_request_string(&req->sub_path,in);
  read_request_string(&req->sud_path,in);
  read_request_string(&req->path_090,in);
  read_request_string(&req->ofb_path,in);
  read_request_string(&req->asa_path,in);
  read_request_string(&req->asb_path,in);
  read_request_string(&req->path_0a0,in);
  read_request_string(&req->lit_path,in);
  read_request_string(&req->path_0a8,in);
  read_request_string(&req->string_114,in);
  read_request_string(&req->string_140,in);
  read_request_string(&req->compiler_version,in);
  block = &req->cpp_block;
  read_request_string(&req->copyright,in);
  if (*block == (request_cpp_block *)0x0) {
    s1 = (byte *)req->compiler_version;
    s2 = s_SH_SERIES_C_Compiler_Ver__5_0_Re_00425ca0;
    do {
      ch = *s1;
      below = ch < (byte)*s2;
      if (ch != *s2) {
LAB_0041cf1e:
        cmp = (1 - (uint)below) - (uint)(below != 0);
        goto LAB_0041cf23;
      }
      if (ch == 0) break;
      ch = s1[1];
      below = ch < (byte)s2[1];
      if (ch != s2[1]) goto LAB_0041cf1e;
      s1 = s1 + 2;
      s2 = s2 + 2;
    } while (ch != 0);
    cmp = 0;
LAB_0041cf23:
    if (cmp == 0) {
      s1 = (byte *)req->copyright;
      s2 = s_Copyright__c__1992_1996_Hitachi__00425cd0;
      do {
        ch = *s1;
        below = ch < (byte)*s2;
        if (ch != *s2) {
LAB_0041cf4f:
          cmp = (1 - (uint)below) - (uint)(below != 0);
          goto LAB_0041cf54;
        }
        if (ch == 0) break;
        ch = s1[1];
        below = ch < (byte)s2[1];
        if (ch != s2[1]) goto LAB_0041cf4f;
        s1 = s1 + 2;
        s2 = s2 + 2;
      } while (ch != 0);
      cmp = 0;
LAB_0041cf54:
      if (cmp == 0) goto LAB_0041cf63;
    }
    g_request_version_mismatch = 1;
  }
  else {
LAB_0041cf63:
    g_request_version_mismatch = 0;
  }
  if (version_tag != 0x1e) {
    report_message_by_code(req->source_name,0,0x12c1,(char *)0x0);
    stock_exit(0xb);
  }
  req->sections = (request_section *)0x0;
  read_request_section_list(&req->sections,in);
  req->string_list_040 = (request_string *)0x0;
  read_request_string_list_040(&req->string_list_040,in);
  req->string_list_048 = (request_string12 *)0x0;
  read_request_string_list_048(&req->string_list_048,in);
  req->sized_string_list_04c = (request_sized_string *)0x0;
  read_request_sized_string_list(&req->sized_string_list_04c,in);
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
  read_request_string(&req->string_15c,in);
  return;
#undef version_tag
}



