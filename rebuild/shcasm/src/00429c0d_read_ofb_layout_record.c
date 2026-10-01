#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_layout_record_tail
#define g_layout_record_tail (*(layout_record * *)(g_sd + 0x13158))
#undef g_layout_symbol_pass0
#define g_layout_symbol_pass0 (*(symbol * *)(g_sd + 0xccf8))
#undef g_ofb_input
#define g_ofb_input (*(FILE * *)(g_sd + 0xd12c))


// entry: 00429c0d
// name : read_ofb_layout_record
// size : 3568
// sig  : layout_record * read_ofb_layout_record(char op)


layout_record * __cdecl read_ofb_layout_record(char op)

{
  unsigned char _frec_10[16];
#define labno_count (*(int *)(_frec_10 + 0))
#define need_labno2 (*(int *)(_frec_10 + 4))
#define cur_ref (*(label_ref * *)(_frec_10 + 8))
  layout_record *new_item;
  label_ref *new_ref;
  uint nread;
  
  new_item = alloc_layout_record();
  new_item->op = op;
  switch(op) {
  case '\x10':
    nread = read_file_bytes(g_ofb_input,(char *)&new_item->location,4);
    if (nread == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    nread = read_file_bytes(g_ofb_input,(char *)&new_item->value,4);
    if (nread == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    break;
  case '\x11':
    nread = read_file_bytes(g_ofb_input,&new_item->size,1);
    if (nread == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    nread = read_file_bytes(g_ofb_input,(char *)&new_item->location,4);
    if (nread == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    nread = read_file_bytes(g_ofb_input,(char *)&new_item->pool_size,2);
    if (nread == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    nread = read_file_bytes(g_ofb_input,(char *)&new_item->label,2);
    if (nread == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    nread = read_file_bytes(g_ofb_input,(char *)&new_item->value,4);
    if (nread == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    nread = read_file_bytes(g_ofb_input,(char *)&new_item->labels,4);
    if (nread == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    break;
  default:
    report_message_at_source_line(0,0,0x1374,(char *)0x0);
    break;
  case '\x14':
    nread = read_file_bytes(g_ofb_input,(char *)&new_item->value,4);
    if (nread == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    nread = read_file_bytes(g_ofb_input,(char *)&new_item->location,4);
    if (nread == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    break;
  case ' ':
    nread = read_file_bytes(g_ofb_input,&new_item->size,1);
    if (nread == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    break;
  case '!':
    nread = read_file_bytes(g_ofb_input,&new_item->size,1);
    if (nread == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    nread = read_file_bytes(g_ofb_input,(char *)&new_item->location,4);
    if (nread == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    nread = read_file_bytes(g_ofb_input,(char *)&new_item->pool_size,2);
    if (nread == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    break;
  case '\"':
  case '$':
    nread = read_file_bytes(g_ofb_input,&new_item->size,1);
    if (nread == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    nread = read_file_bytes(g_ofb_input,(char *)&new_item->location,4);
    if (nread == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    nread = read_file_bytes(g_ofb_input,(char *)&new_item->value,4);
    if (nread == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    nread = read_file_bytes(g_ofb_input,(char *)&labno_count,4);
    if (nread == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    if (labno_count != 0) {
      cur_ref = pool_alloc(8);
      new_item->labels = cur_ref;
      nread = read_file_bytes(g_ofb_input,(char *)&cur_ref->labno1,2);
      if (nread == 0xffffffff) {
        report_message_at_source_line(0,0,0xce6,(char *)0x0);
      }
      need_labno2 = 1;
      while (labno_count = labno_count + -1, labno_count != 0) {
        if (need_labno2 == 1) {
          nread = read_file_bytes(g_ofb_input,(char *)&cur_ref->labno2,2);
          if (nread == 0xffffffff) {
            report_message_at_source_line(0,0,0xce6,(char *)0x0);
          }
          need_labno2 = 0;
        }
        else {
          new_ref = pool_alloc(8);
          cur_ref->next = new_ref;
          cur_ref = cur_ref->next;
          nread = read_file_bytes(g_ofb_input,(char *)&cur_ref->labno1,2);
          if (nread == 0xffffffff) {
            report_message_at_source_line(0,0,0xce6,(char *)0x0);
          }
          need_labno2 = 1;
        }
      }
    }
    nread = read_file_bytes(g_ofb_input,(char *)&new_item->pool_size,2);
    if (nread == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    break;
  case '#':
  case '%':
  case '&':
  case ')':
  case '+':
    nread = read_file_bytes(g_ofb_input,&new_item->size,1);
    if (nread == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    if (((op == '&') || (op == '%')) &&
       (nread = read_file_bytes(g_ofb_input,(char *)&new_item->misc,1), nread == 0xffffffff)) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    nread = read_file_bytes(g_ofb_input,(char *)&new_item->location,4);
    if (nread == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    nread = read_file_bytes(g_ofb_input,(char *)&new_item->value,4);
    if (nread == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    nread = read_file_bytes(g_ofb_input,(char *)&labno_count,4);
    if (nread == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    if (labno_count != 0) {
      cur_ref = pool_alloc(8);
      new_item->labels = cur_ref;
      nread = read_file_bytes(g_ofb_input,(char *)&cur_ref->labno1,2);
      if (nread == 0xffffffff) {
        report_message_at_source_line(0,0,0xce6,(char *)0x0);
      }
      need_labno2 = 1;
      while (labno_count = labno_count + -1, labno_count != 0) {
        if (need_labno2 == 1) {
          nread = read_file_bytes(g_ofb_input,(char *)&cur_ref->labno2,2);
          if (nread == 0xffffffff) {
            report_message_at_source_line(0,0,0xce6,(char *)0x0);
          }
          need_labno2 = 0;
        }
        else {
          new_ref = pool_alloc(8);
          cur_ref->next = new_ref;
          cur_ref = cur_ref->next;
          nread = read_file_bytes(g_ofb_input,(char *)&cur_ref->labno1,2);
          if (nread == 0xffffffff) {
            report_message_at_source_line(0,0,0xce6,(char *)0x0);
          }
          need_labno2 = 1;
        }
      }
    }
    break;
  case '\'':
    nread = read_file_bytes(g_ofb_input,&new_item->size,1);
    if (nread == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    nread = read_file_bytes(g_ofb_input,(char *)&new_item->flg,1);
    if (nread == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    nread = read_file_bytes(g_ofb_input,(char *)&new_item->misc,1);
    if (nread == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    nread = read_file_bytes(g_ofb_input,(char *)&new_item->value,4);
    if (nread == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    nread = read_file_bytes(g_ofb_input,(char *)&new_item->labels,4);
    if (nread == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    break;
  case '(':
    nread = read_file_bytes(g_ofb_input,&new_item->size,1);
    if (nread == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    nread = read_file_bytes(g_ofb_input,(char *)&new_item->flg,1);
    if (nread == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    nread = read_file_bytes(g_ofb_input,(char *)&new_item->value,4);
    if (nread == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    nread = read_file_bytes(g_ofb_input,(char *)&new_item->labels,4);
    if (nread == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    break;
  case '*':
  case ',':
    nread = read_file_bytes(g_ofb_input,&new_item->size,1);
    if (nread == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    nread = read_file_bytes(g_ofb_input,(char *)&new_item->flg,1);
    if (nread == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    nread = read_file_bytes(g_ofb_input,(char *)&new_item->value,4);
    if (nread == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    nread = read_file_bytes(g_ofb_input,(char *)&labno_count,4);
    if (nread == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    if (labno_count != 0) {
      cur_ref = pool_alloc(8);
      new_item->labels = cur_ref;
      nread = read_file_bytes(g_ofb_input,(char *)&cur_ref->labno1,2);
      if (nread == 0xffffffff) {
        report_message_at_source_line(0,0,0xce6,(char *)0x0);
      }
      need_labno2 = 1;
      while (labno_count = labno_count + -1, labno_count != 0) {
        if (need_labno2 == 1) {
          nread = read_file_bytes(g_ofb_input,(char *)&cur_ref->labno2,2);
          if (nread == 0xffffffff) {
            report_message_at_source_line(0,0,0xce6,(char *)0x0);
          }
          need_labno2 = 0;
        }
        else {
          new_ref = pool_alloc(8);
          cur_ref->next = new_ref;
          cur_ref = cur_ref->next;
          nread = read_file_bytes(g_ofb_input,(char *)&cur_ref->labno1,2);
          if (nread == 0xffffffff) {
            report_message_at_source_line(0,0,0xce6,(char *)0x0);
          }
          need_labno2 = 1;
        }
      }
    }
    break;
  case '.':
    nread = read_file_bytes(g_ofb_input,&new_item->size,1);
    if (nread == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    nread = read_file_bytes(g_ofb_input,(char *)&new_item->flg,1);
    if (nread == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    break;
  case -0x72:
  case -0x6e:
  case -0x6c:
  case -0x6a:
    nread = read_file_bytes(g_ofb_input,&new_item->size,1);
    if (nread == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    nread = read_file_bytes(g_ofb_input,(char *)&new_item->location,4);
    if (nread == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    nread = read_file_bytes(g_ofb_input,(char *)&new_item->pool_size,2);
    if (nread == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
    nread = read_file_bytes(g_ofb_input,(char *)&new_item->misc,1);
    if (nread == 0xffffffff) {
      report_message_at_source_line(0,0,0xce6,(char *)0x0);
    }
  }
  if (g_layout_record_tail == (layout_record *)0x0) {
    g_layout_symbol_pass0->layout_records = new_item;
  }
  else {
    g_layout_record_tail->next = new_item;
  }
  g_layout_record_tail = new_item;
  return new_item;
#undef labno_count
#undef need_labno2
#undef cur_ref
}



