#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))
#undef g_swi_file
#define g_swi_file (*(FILE * *)(g_sd + 0x1feec))
#undef g_switch_cases
#define g_switch_cases (*(int * *)(g_sd + 0x1fee0))


// entry: 00420600
// name : read_switch_case_table
// size : 752
// sig  : void read_switch_case_table(gen_node * sw)


int __cdecl read_switch_case_table(gen_node *sw)

{
  unsigned char _frec_12[18];
#define case_label (*(short *)(_frec_12 + 0))
#define buf (*(char *)(_frec_12 + 2))
#define local_f (*(undefined1 *)(_frec_12 + 3))
#define swi_offset (*(LONG *)(_frec_12 + 10))
#define case_value (*(int *)(_frec_12 + 14))
  int iVar1;
  uint nread;
  int *case_rec;
  int msg_no;
  
  g_switch_min_case = 0;
  g_switch_max_case = 0;
  g_switch_cases = (int *)0x0;
  iVar1 = find_keyed_offset(g_request,(int)sw->symx,&swi_offset);
  if (iVar1 == 0) {
    report_codegen_message(0x1218,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
  }
  stock_fseek(g_swi_file,swi_offset,0);
  nread = read_file_bytes(g_swi_file,&buf,2);
  if ((int)nread < 2) {
    if (nread == 0xffffffff) {
      iVar1 = 0xce6;
    }
    else {
      iVar1 = 0x1217;
    }
    report_codegen_message(iVar1,1,0,0,(char *)0x0);
  }
  nread = read_file_bytes(g_swi_file,&buf,1);
  if ((int)nread < 1) {
    if (nread == 0xffffffff) {
      iVar1 = 0xce6;
    }
    else {
      iVar1 = 0x1217;
    }
    report_codegen_message(iVar1,1,0,0,(char *)0x0);
  }
  if (buf == '\0') {
    g_switch_default_label = 0;
  }
  else {
    nread = read_file_bytes(g_swi_file,&buf,2);
    if ((int)nread < 2) {
      if (nread == 0xffffffff) {
        iVar1 = 0xce6;
      }
      else {
        iVar1 = 0x1217;
      }
      report_codegen_message(iVar1,1,0,0,(char *)0x0);
    }
    g_switch_default_label = CONCAT11(local_f,buf);
    g_switch_default_label =
         g_switch_default_label + (short)*(undefined4 *)g_request->unknown_0b0 + 0xb6;
  }
  nread = read_file_bytes(g_swi_file,&buf,2);
  if ((int)nread < 2) {
    if (nread == 0xffffffff) {
      iVar1 = 0xce6;
    }
    else {
      iVar1 = 0x1217;
    }
    report_codegen_message(iVar1,1,0,0,(char *)0x0);
  }
  g_switch_case_count = CONCAT11(local_f,buf);
  if (g_switch_case_count != 0) {
    case_rec = stock_malloc((int)g_switch_case_count << 3);
    g_switch_cases = case_rec;
    if (case_rec == (int *)0x0) {
      report_codegen_message(0xbcd,1,0,0,(char *)0x0);
    }
    else {
      iVar1 = 0;
      g_switch_min_case = 0x7fffffff;
      g_switch_max_case = -0x80000000;
      if (0 < g_switch_case_count) {
        do {
          nread = read_file_bytes(g_swi_file,(char *)&case_value,4);
          if ((int)nread < 4) {
            if (nread == 0xffffffff) {
              msg_no = 0xce6;
            }
            else {
              msg_no = 0x1217;
            }
            report_codegen_message(msg_no,1,0,0,(char *)0x0);
          }
          *case_rec = case_value;
          nread = read_file_bytes(g_swi_file,(char *)&case_label,2);
          if ((int)nread < 2) {
            if (nread == 0xffffffff) {
              msg_no = 0xce6;
            }
            else {
              msg_no = 0x1217;
            }
            report_codegen_message(msg_no,1,0,0,(char *)0x0);
          }
          *(short *)(case_rec + 1) =
               (short)*(undefined4 *)g_request->unknown_0b0 + case_label + 0xb6;
          if (*case_rec < g_switch_min_case) {
            g_switch_min_case = *case_rec;
          }
          if (g_switch_max_case < *case_rec) {
            g_switch_max_case = *case_rec;
          }
          iVar1 = iVar1 + 1;
          case_rec = case_rec + 2;
        } while (iVar1 < g_switch_case_count);
        return;
      }
    }
  }
  return;
#undef case_label
#undef buf
#undef local_f
#undef swi_offset
#undef case_value
}



