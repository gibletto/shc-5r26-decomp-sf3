#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_current_request
#define g_current_request (*(request * *)(g_sd + 0xcf0c))
#undef g_lit_input
#define g_lit_input (*(FILE * *)(g_sd + 0x10c84))
#undef g_ofb_input
#define g_ofb_input (*(FILE * *)(g_sd + 0xd12c))


// entry: 00429605
// name : finish_layout_passes
// size : 689
// sig  : void finish_layout_passes(void)


int __cdecl finish_layout_passes(void)

{
  int close_status;
  request_section *cur_section;
  int i;
  bool overflow;
  
  g_program_size = 0;
  rewind_size_decision_stream();
  close_status = _fclose(g_ofb_input);
  if (close_status == -1) {
    report_message_at_source_line(0,0,0xce5,(char *)0x0);
  }
  close_status = _fclose(g_lit_input);
  if (close_status == -1) {
    report_message_at_source_line(0,0,0xce5,(char *)0x0);
  }
  overflow = false;
  for (cur_section = g_current_request->sections; cur_section != (request_section *)0x0;
      cur_section = cur_section->next) {
    cur_section->size[0] =
         cur_section->size[0] -
         (cur_section->layout->shrink_pass1 + cur_section->layout->shrink_pass0);
    for (i = 0; i < 4; i = i + 1) {
      if ((-g_program_size - 1U < (uint)cur_section->size[i]) || (overflow)) {
        g_program_size = 1;
        overflow = true;
      }
      else {
        g_program_size = cur_section->size[i] + g_program_size;
      }
    }
  }
  if (g_current_request->code == 1) {
    if (overflow) {
      report_message_at_source_line(0,0,0xc81,(char *)0x0);
    }
  }
  else if (overflow) {
    for (cur_section = g_current_request->sections; cur_section != (request_section *)0x0;
        cur_section = cur_section->next) {
      cur_section->size[3] = 1;
      cur_section->size[2] = cur_section->size[3];
      cur_section->size[1] = cur_section->size[2];
      cur_section->size[0] = cur_section->size[1];
    }
  }
  else {
    g_program_size = (int)(g_program_size != 0);
    for (cur_section = g_current_request->sections; cur_section != (request_section *)0x0;
        cur_section = cur_section->next) {
      if (cur_section->size[0] == 0) {
        cur_section->size[0] = 0;
      }
      else {
        cur_section->size[0] = 1;
      }
      if (cur_section->size[1] == 0) {
        cur_section->size[1] = 0;
      }
      else {
        cur_section->size[1] = 1;
      }
      if (cur_section->size[2] == 0) {
        cur_section->size[2] = 0;
      }
      else {
        cur_section->size[2] = 1;
      }
      if (cur_section->size[3] == 0) {
        cur_section->size[3] = 0;
      }
      else {
        cur_section->size[3] = 1;
      }
    }
  }
  return;
}
