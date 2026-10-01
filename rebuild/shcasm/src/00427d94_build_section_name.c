#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))


// entry: 00427d94
// name : build_section_name
// size : 516
// sig  : int build_section_name(char * out, request_section * section, short kind)


int __cdecl build_section_name(char *out,request_section *section,short kind)

{
  uint uVar1;
  uint *puVar2;
  char full_name_len;
  
  if ((section->id == 2) || (section->id == 3)) {
    if (section->id == 2) {
      stock_strcpy((uint *)out,(uint *)&s_dollar_G0_00442080);
    }
    else {
      stock_strcpy((uint *)out,(uint *)&s_dollar_G1_00442084);
    }
    uVar1 = stock_strlen(out);
  }
  else {
    switch(kind) {
    case 0:
      uVar1 = stock_strlen(g_current_request->section_program);
      full_name_len = (char)uVar1;
      break;
    case 1:
      uVar1 = stock_strlen(g_current_request->section_const);
      full_name_len = (char)uVar1;
      break;
    case 2:
      uVar1 = stock_strlen(g_current_request->section_data);
      full_name_len = (char)uVar1;
      break;
    case 3:
      uVar1 = stock_strlen(g_current_request->section_bss);
      full_name_len = (char)uVar1;
    }
    full_name_len = (char)section->name_len + full_name_len;
    if (full_name_len < ' ') {
      switch(kind) {
      case 0:
        stock_strcpy((uint *)out,(uint *)g_current_request->section_program);
        break;
      case 1:
        stock_strcpy((uint *)out,(uint *)g_current_request->section_const);
        break;
      case 2:
        stock_strcpy((uint *)out,(uint *)g_current_request->section_data);
        break;
      case 3:
        stock_strcpy((uint *)out,(uint *)g_current_request->section_bss);
      }
      puVar2 = (uint *)0x0;
      if (section->name_len != 0) {
        puVar2 = stock_strcat((uint *)out,(uint *)section->name);
      }
    }
    else {
      report_message_at_source_line(0,0,0xa96,(char *)0x0);
      g_max_error_severity = 3;
      full_name_len = '\x01';
      *out = (&s_PCDB_00442078)[kind];
      out[1] = '\0';
      puVar2 = (uint *)out;
    }
    uVar1 = CONCAT31((int3)((uint)puVar2 >> 8),full_name_len);
  }
  return uVar1;
}



