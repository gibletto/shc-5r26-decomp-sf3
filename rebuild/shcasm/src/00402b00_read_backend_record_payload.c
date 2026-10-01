#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_backend_stream
#define g_backend_stream (*(FILE * *)(g_sd + 0x8f98))


// entry: 00402b00
// name : read_backend_record_payload
// size : 1314
// sig  : uint read_backend_record_payload(FILE * stream, psd * rec, uchar op)


uint __cdecl read_backend_record_payload(FILE *stream,psd *rec,uchar op)

{
  unsigned char _frec_1c[28];
#define buf (*(char *)(_frec_1c + 0))
#define local_1b (*(undefined1 *)(_frec_1c + 1))
#define local_1a (*(undefined1 *)(_frec_1c + 2))
#define local_19 (*(undefined1 *)(_frec_1c + 3))
#define local_18 (*(undefined1 *)(_frec_1c + 4))
#define local_17 (*(undefined1 *)(_frec_1c + 5))
#define local_16 (*(undefined1 *)(_frec_1c + 6))
#define local_15 (*(undefined1 *)(_frec_1c + 7))
#define local_14 (*(byte *)(_frec_1c + 8))
#define local_13 (*(byte *)(_frec_1c + 9))
#define local_12 (*(char *)(_frec_1c + 10))
#define local_11 (*(undefined1 *)(_frec_1c + 11))
#define local_10 (*(undefined1 *)(_frec_1c + 12))
#define local_f (*(undefined1 *)(_frec_1c + 13))
#define local_e (*(undefined1 *)(_frec_1c + 14))
#define local_d (*(undefined1 *)(_frec_1c + 15))
#define status (*(uint *)(_frec_1c + 16))
#define op_no (*(ushort *)(_frec_1c + 20))
  
  g_backend_stream = stream;
  status = 0;
  op_no = (ushort)op;
  switch(*(undefined2 *)(&g_backend_op_payload_format + (short)op_no * 2)) {
  case 1:
    break;
  case 2:
    status = read_backend_stream_bytes(&buf,0x10);
    if (status == 0) {
      status = 0xffffffff;
    }
    else {
      *(char *)&rec->expno = buf;
      *(undefined1 *)((int)&rec->expno + 1) = local_1b;
      *(undefined1 *)((int)&rec->expno + 2) = local_1a;
      *(undefined1 *)((int)&rec->expno + 3) = local_19;
      *(undefined1 *)&rec->filno = local_18;
      *(undefined1 *)((int)&rec->filno + 1) = local_17;
      *(undefined1 *)&rec->linno = local_16;
      *(undefined1 *)((int)&rec->linno + 1) = local_15;
      *(byte *)&rec->ea1 = local_14;
      *(byte *)((int)&rec->ea1 + 1) = local_13;
      *(char *)((int)&rec->ea1 + 2) = local_12;
      *(undefined1 *)((int)&rec->ea1 + 3) = local_11;
      *(undefined1 *)&rec->ea2 = local_10;
      *(undefined1 *)((int)&rec->ea2 + 1) = local_f;
      *(undefined1 *)((int)&rec->ea2 + 2) = local_e;
      *(undefined1 *)((int)&rec->ea2 + 3) = local_d;
    }
    break;
  case 3:
    status = read_backend_stream_bytes(&buf,4);
    if (status == 0) {
      status = 0xffffffff;
    }
    else {
      *(char *)&rec->filno = buf;
      *(undefined1 *)((int)&rec->filno + 1) = local_1b;
      *(undefined1 *)&rec->linno = local_1a;
      *(undefined1 *)((int)&rec->linno + 1) = local_19;
    }
    break;
  case 4:
    status = read_backend_stream_bytes(&buf,2);
    if (status == 0) {
      status = 0xffffffff;
    }
    else {
      *(char *)&rec->ea1 = buf;
      *(undefined1 *)((int)&rec->ea1 + 1) = local_1b;
    }
    break;
  case 5:
    status = read_backend_stream_bytes(&buf,6);
    if (status == 0) {
      status = 0xffffffff;
    }
    else {
      *(char *)&rec->ea1 = buf;
      *(undefined1 *)((int)&rec->ea1 + 1) = local_1b;
      *(undefined1 *)&rec->sptravel = local_1a;
      *(undefined1 *)((int)&rec->sptravel + 1) = local_19;
      *(undefined1 *)((int)&rec->sptravel + 2) = local_18;
      *(undefined1 *)((int)&rec->sptravel + 3) = local_17;
    }
    break;
  case 6:
    status = read_backend_stream_bytes(&buf,5);
    if (status == 0) {
      status = 0xffffffff;
    }
    else {
      *(char *)&rec->filno = buf;
      *(undefined1 *)((int)&rec->filno + 1) = local_1b;
      *(undefined1 *)&rec->linno = local_1a;
      *(undefined1 *)((int)&rec->linno + 1) = local_19;
      *(undefined1 *)&rec->ea1 = local_18;
    }
    break;
  case 7:
    break;
  case 8:
    status = read_backend_stream_bytes(&buf,0xb);
    if (status == 0) {
      status = 0xffffffff;
    }
    else {
      *(char *)&rec->filno = buf;
      *(undefined1 *)((int)&rec->filno + 1) = local_1b;
      *(undefined1 *)&rec->linno = local_1a;
      *(undefined1 *)((int)&rec->linno + 1) = local_19;
      *(undefined1 *)&rec->expno = local_18;
      *(undefined1 *)((int)&rec->expno + 1) = local_17;
      *(undefined1 *)((int)&rec->expno + 2) = local_16;
      *(undefined1 *)((int)&rec->expno + 3) = local_15;
      rec->flg = local_14 & 0xe3;
      rec->misc = local_13 & 0xa0;
      if (local_12 == '\0') {
        rec->ea1 = (ea *)0x0;
        rec->ea2 = (ea *)0x0;
      }
      else if (local_12 == '\x01') {
        status = read_record_operand(rec,1);
        if (status != 0xffffffff) {
          rec->ea2 = (ea *)0x0;
        }
      }
      else if (local_12 == '\x02') {
        status = read_record_operand(rec,1);
        if (status == 0xffffffff) {
          status = 0xffffffff;
        }
        else {
          status = read_record_operand(rec,2);
        }
      }
      else {
        report_message_at_source_line(0,0,0x131e,(char *)0x0);
      }
    }
    break;
  case 9:
    status = read_pseudo_op_record_payload(rec);
    break;
  case 10:
    status = read_backend_stream_bytes(&buf,4);
    if (status == 0) {
      status = 0xffffffff;
    }
    else {
      *(char *)&rec->filno = buf;
      *(undefined1 *)((int)&rec->filno + 1) = local_1b;
      *(undefined1 *)&rec->linno = local_1a;
      *(undefined1 *)((int)&rec->linno + 1) = local_19;
    }
    break;
  case 0xb:
    status = read_backend_stream_bytes(&buf,0xc);
    if (status == 0) {
      status = 0xffffffff;
    }
    else {
      *(char *)&rec->filno = buf;
      *(undefined1 *)((int)&rec->filno + 1) = local_1b;
      *(undefined1 *)&rec->linno = local_1a;
      *(undefined1 *)((int)&rec->linno + 1) = local_19;
      *(undefined1 *)&rec->ea1 = local_18;
      *(undefined1 *)((int)&rec->ea1 + 1) = local_17;
      *(undefined1 *)((int)&rec->ea1 + 2) = local_16;
      *(undefined1 *)((int)&rec->ea1 + 3) = local_15;
      *(byte *)&rec->ea2 = local_14;
      *(byte *)((int)&rec->ea2 + 1) = local_13;
      *(char *)((int)&rec->ea2 + 2) = local_12;
      *(undefined1 *)((int)&rec->ea2 + 3) = local_11;
    }
    break;
  case 0xc:
    status = read_backend_stream_bytes(&buf,2);
    if (status == 0) {
      status = 0xffffffff;
    }
    else {
      *(char *)&rec->filno = buf;
      *(undefined1 *)((int)&rec->filno + 1) = local_1b;
    }
    break;
  default:
    report_message_at_source_line(0,0,0x131d,(char *)0x0);
  }
  return status;
#undef buf
#undef local_1b
#undef local_1a
#undef local_19
#undef local_18
#undef local_17
#undef local_16
#undef local_15
#undef local_14
#undef local_13
#undef local_12
#undef local_11
#undef local_10
#undef local_f
#undef local_e
#undef local_d
#undef status
#undef op_no
}



