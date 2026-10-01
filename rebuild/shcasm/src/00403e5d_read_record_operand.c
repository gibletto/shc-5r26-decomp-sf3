#include "decls.h"
#include "imports.h"

// entry: 00403e5d
// name : read_record_operand
// size : 1131
// sig  : uint read_record_operand(psd * rec, int which)


uint __cdecl read_record_operand(psd *rec,int which)

{
  unsigned char _frec_20[32];
#define gbr_disp (*(int *)(_frec_20 + 0))
#define buf (*(reg (*)[3])(_frec_20 + 4))
#define disp16 (*(short (*)[2])(_frec_20 + 7))
#define status (*(uint *)(_frec_20 + 12))
#define i (*(short *)(_frec_20 + 16))
#define operand (*(ea * *)(_frec_20 + 20))
#define ref_count (*(int *)(_frec_20 + 24))
  uint count;
  
  status = 0;
  for (i = 0; i < 5; i = i + 1) {
    buf[i] = REG_R0;
  }
  operand = pool_alloc(0xc);
  if (operand == (ea *)0x0) {
    report_message_at_source_line(0,0,0xbcd,(char *)0x0);
  }
  if (which == 1) {
    rec->ea1 = operand;
  }
  else if (which == 2) {
    rec->ea2 = operand;
  }
  else {
    report_message_at_source_line(0,0,0x131e,(char *)0x0);
  }
  status = read_backend_stream_bytes((char *)buf,1);
  if (status == 0) {
    status = 0xffffffff;
  }
  else {
    operand->type = buf[0] & REG_FR15 | operand->type;
    operand->type = buf[0] & REG_NON_80 | operand->type;
    switch(operand->type & 0x1f) {
    case 0:
      break;
    case 1:
    case 2:
    case 3:
    case 4:
    case 0xf:
    case 0x10:
      status = read_backend_stream_bytes((char *)buf,1);
      if (status == 0) {
        status = 0xffffffff;
      }
      else {
        operand->base = buf[0];
      }
      break;
    case 5:
      status = read_backend_stream_bytes((char *)buf,1);
      if (status == 0) {
        status = 0xffffffff;
      }
      else {
        operand->base = buf[0] + REG_SR;
      }
      break;
    case 6:
      status = read_backend_stream_bytes((char *)buf,1);
      if (status == 0) {
        status = 0xffffffff;
      }
      else {
        operand->base = buf[0] + REG_MACH;
      }
      break;
    case 7:
      count = operand_size_from_flags(rec);
      status = read_backend_stream_bytes((char *)buf,count);
      if (status == 0) {
        status = 0xffffffff;
      }
      else {
        store_immediate_in_operand((short *)buf,operand,count);
        if ((((rec->op == OP_AND) || (rec->op == OP_OR)) || (rec->op == OP_TST)) ||
           ((rec->op == OP_XOR || (rec->op == OP_TRAPA)))) {
          operand->disp = operand->disp & 0xff;
        }
        status = read_backend_stream_bytes((char *)&ref_count,4);
        if (status == 0) {
          status = 0xffffffff;
        }
        else {
          read_operand_label_refs(ref_count,operand);
        }
      }
      break;
    case 8:
      status = read_backend_stream_bytes((char *)buf,1);
      if (status == 0) {
        status = 0xffffffff;
      }
      else {
        operand->base = buf[0];
        status = read_backend_stream_bytes((char *)disp16,2);
        if (status == 0) {
          status = 0xffffffff;
        }
        else {
          operand->disp = (int)disp16[0];
        }
      }
      break;
    case 9:
      status = read_backend_stream_bytes((char *)buf,1);
      if (status == 0) {
        status = 0xffffffff;
      }
      else {
        operand->index = buf[0] & REG_R15;
        operand->base = (reg)(((int)(char)buf[0] & 0xf0U) >> 4);
      }
      break;
    case 10:
      status = read_backend_stream_bytes((char *)disp16,2);
      if (status == 0) {
        status = 0xffffffff;
      }
      else {
        operand->disp = (int)disp16[0];
        operand->base = REG_PC;
      }
      break;
    case 0xb:
      status = read_backend_stream_bytes((char *)&gbr_disp,4);
      if (status == 0) {
        status = 0xffffffff;
      }
      else {
        operand->disp = gbr_disp;
        operand->base = REG_GBR;
        status = read_backend_stream_bytes((char *)&ref_count,4);
        if (status == 0) {
          status = 0xffffffff;
        }
        else {
          read_operand_label_refs(ref_count,operand);
        }
      }
      break;
    case 0xc:
      status = read_backend_stream_bytes((char *)buf,1);
      if (status == 0) {
        status = 0xffffffff;
      }
      else {
        operand->index = buf[0];
        operand->base = REG_GBR;
      }
      break;
    default:
      report_message_at_source_line(0,0,0x1320,(char *)0x0);
    }
  }
  return status;
#undef gbr_disp
#undef buf
#undef disp16
#undef status
#undef i
#undef operand
#undef ref_count
}



