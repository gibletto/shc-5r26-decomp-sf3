#include "decls.h"
#include "imports.h"

// entry: 004030aa
// name : read_pseudo_op_record_payload
// size : 3438
// sig  : uint read_pseudo_op_record_payload(psd * rec)


uint __cdecl read_pseudo_op_record_payload(psd *rec)

{
  unsigned char _frec_24[36];
#define buf (*(reg *)(_frec_24 + 0))
#define local_23 (*(reg *)(_frec_24 + 1))
#define local_22 (*(reg *)(_frec_24 + 2))
#define local_21 (*(char *)(_frec_24 + 3))
#define local_20 (*(undefined2 *)(_frec_24 + 4))
#define local_1e (*(undefined1 *)(_frec_24 + 6))
#define local_1d (*(undefined1 *)(_frec_24 + 7))
#define local_19 (*(undefined1 *)(_frec_24 + 11))
#define local_18 (*(undefined1 *)(_frec_24 + 12))
#define local_17 (*(undefined1 *)(_frec_24 + 13))
#define local_16 (*(undefined1 *)(_frec_24 + 14))
#define status (*(uint *)(_frec_24 + 16))
#define base_reg (*(reg *)(_frec_24 + 20))
#define ref_count (*(int *)(_frec_24 + 28))
  ea *new_ea;
  
  status = 0;
  status = read_backend_stream_bytes((char *)&buf,8);
  if (status == 0) {
    status = 0xffffffff;
  }
  else {
    *(reg *)&rec->filno = buf;
    *(reg *)((int)&rec->filno + 1) = local_23;
    *(reg *)&rec->linno = local_22;
    *(char *)((int)&rec->linno + 1) = local_21;
    *(char *)&rec->expno = (char)local_20;
    *(undefined1 *)((int)&rec->expno + 1) = (*(unsigned char *)((char *)&local_20 + 1));
    *(undefined1 *)((int)&rec->expno + 2) = local_1e;
    *(undefined1 *)((int)&rec->expno + 3) = local_1d;
    switch(rec->op) {
    case OP_RETURN:
      status = read_branch_label_operand(rec);
      if (status != 0xffffffff) {
        rec->flg = '\0';
        rec->tmp = '\x01';
      }
      break;
    case OP_CALL:
      status = read_backend_stream_bytes((char *)&buf,1);
      if (status == 0) {
        return 0xffffffff;
      }
      rec->misc = buf & REG_NON_80;
    case OP_JUMP:
    case OP_JUMPT:
    case OP_JUMPF:
      status = read_branch_label_operand(rec);
      if (status == 0xffffffff) {
        status = 0xffffffff;
      }
      else {
        status = read_backend_stream_bytes((char *)&buf,1);
        if (status == 0) {
          status = 0xffffffff;
        }
        else {
          rec->flg = '\0';
          rec->tmp = buf;
        }
      }
      break;
    case OP_MV_LOC:
      status = read_backend_stream_bytes((char *)&buf,4);
      if (status == 0) {
        status = 0xffffffff;
      }
      else {
        rec->flg = buf & REG_NON_E3;
        rec->misc = local_23 & REG_NON_C0;
        new_ea = pool_alloc(0xc);
        rec->ea1 = new_ea;
        if (rec->ea1 == (ea *)0x0) {
          report_message_at_source_line(0,0,0xbcd,(char *)0x0);
        }
        new_ea = pool_alloc(0xc);
        rec->ea2 = new_ea;
        if (rec->ea2 == (ea *)0x0) {
          report_message_at_source_line(0,0,0xbcd,(char *)0x0);
        }
        base_reg = local_22;
        rec->tmp = local_21;
        if ((rec->misc & 0x80U) == 0) {
          rec->ea2->type = '\x01';
          rec->ea2->base = local_22;
          rec->ea1->base = REG_FP;
          status = read_backend_stream_bytes(&local_21,1);
          if (status == 0) {
            return 0xffffffff;
          }
          status = read_backend_stream_bytes((char *)&local_20,4);
          if (status == 0) {
            return 0xffffffff;
          }
          store_immediate_in_operand(&local_20,rec->ea1,4);
          if (rec->ea1->disp == 0) {
            rec->ea1->type = '\x02';
          }
          else {
            rec->ea1->type = '\b';
          }
        }
        else {
          rec->ea1->type = '\x01';
          rec->ea1->base = local_22;
          rec->ea2->base = REG_FP;
          status = read_backend_stream_bytes(&local_21,1);
          if (status == 0) {
            return 0xffffffff;
          }
          status = read_backend_stream_bytes((char *)&local_20,4);
          if (status == 0) {
            return 0xffffffff;
          }
          store_immediate_in_operand(&local_20,rec->ea2,4);
          if (rec->ea2->disp == 0) {
            rec->ea2->type = '\x02';
          }
          else {
            rec->ea2->type = '\b';
          }
        }
        status = read_backend_stream_bytes((char *)&buf,4);
        if (status == 0) {
          status = 0xffffffff;
        }
        else {
          status = read_backend_stream_bytes((char *)&buf,4);
          if (status == 0) {
            status = 0xffffffff;
          }
          else {
            *(reg *)&rec->sptravel = buf;
            *(reg *)((int)&rec->sptravel + 1) = local_23;
            *(reg *)((int)&rec->sptravel + 2) = local_22;
            *(char *)((int)&rec->sptravel + 3) = local_21;
          }
        }
      }
      break;
    case OP_MVA_LC:
      status = read_backend_stream_bytes((char *)&buf,0xf);
      if (status == 0) {
        status = 0xffffffff;
      }
      else {
        rec->flg = buf & REG_NON_E3;
        new_ea = pool_alloc(0xc);
        rec->ea1 = new_ea;
        if (rec->ea1 == (ea *)0x0) {
          report_message_at_source_line(0,0,0xbcd,(char *)0x0);
        }
        new_ea = pool_alloc(0xc);
        rec->ea2 = new_ea;
        if (rec->ea2 == (ea *)0x0) {
          report_message_at_source_line(0,0,0xbcd,(char *)0x0);
        }
        rec->ea2->base = local_23;
        rec->ea2->type = '\x01';
        rec->ea1->base = REG_FP;
        *(char *)&rec->ea1->disp = local_21;
        *(char *)((int)&rec->ea1->disp + 1) = (char)local_20;
        *(undefined1 *)((int)&rec->ea1->disp + 2) = (*(unsigned char *)((char *)&local_20 + 1));
        *(undefined1 *)((int)&rec->ea1->disp + 3) = local_1e;
        if (rec->ea1->disp == 0) {
          rec->ea1->type = '\x02';
        }
        else {
          rec->ea1->type = '\b';
        }
        *(undefined1 *)&rec->sptravel = local_19;
        *(undefined1 *)((int)&rec->sptravel + 1) = local_18;
        *(undefined1 *)((int)&rec->sptravel + 2) = local_17;
        *(undefined1 *)((int)&rec->sptravel + 3) = local_16;
      }
      break;
    case OP_MVA_PC:
      status = read_backend_stream_bytes((char *)&buf,2);
      if (status == 0) {
        status = 0xffffffff;
      }
      else {
        rec->flg = '\0';
        new_ea = pool_alloc(0xc);
        rec->ea1 = new_ea;
        if (rec->ea1 == (ea *)0x0) {
          report_message_at_source_line(0,0,0xbcd,(char *)0x0);
        }
        new_ea = pool_alloc(0xc);
        rec->ea2 = new_ea;
        if (rec->ea2 == (ea *)0x0) {
          report_message_at_source_line(0,0,0xbcd,(char *)0x0);
        }
        rec->ea2->base = buf;
        rec->ea2->type = '\x01';
        rec->ea1->type = '\a';
        status = read_backend_stream_bytes((char *)&buf,4);
        if (status == 0) {
          status = 0xffffffff;
        }
        else {
          *(reg *)&rec->ea1->disp = buf;
          *(reg *)((int)&rec->ea1->disp + 1) = local_23;
          *(reg *)((int)&rec->ea1->disp + 2) = local_22;
          *(char *)((int)&rec->ea1->disp + 3) = local_21;
          status = read_backend_stream_bytes((char *)&ref_count,4);
          if (status == 0) {
            status = 0xffffffff;
          }
          else {
            read_operand_label_refs(ref_count,rec->ea1);
          }
        }
      }
      break;
    case OP_MOVI:
      status = read_backend_stream_bytes((char *)&buf,3);
      if (status == 0) {
        status = 0xffffffff;
      }
      else {
        rec->flg = buf & REG_NON_E3;
        rec->misc = local_23 & REG_DR0;
        new_ea = pool_alloc(0xc);
        rec->ea1 = new_ea;
        if (rec->ea1 == (ea *)0x0) {
          report_message_at_source_line(0,0,0xbcd,(char *)0x0);
        }
        new_ea = pool_alloc(0xc);
        rec->ea2 = new_ea;
        if (rec->ea2 == (ea *)0x0) {
          report_message_at_source_line(0,0,0xbcd,(char *)0x0);
        }
        rec->ea2->base = local_22;
        rec->ea2->type = '\x01';
        status = read_backend_stream_bytes(&local_21,1);
        if (status == 0) {
          status = 0xffffffff;
        }
        else {
          rec->ea1->type = '\a';
          status = read_backend_stream_bytes((char *)&local_20,4);
          if (status == 0) {
            status = 0xffffffff;
          }
          else {
            *(char *)&rec->ea1->disp = (char)local_20;
            *(undefined1 *)((int)&rec->ea1->disp + 1) = (*(unsigned char *)((char *)&local_20 + 1));
            *(undefined1 *)((int)&rec->ea1->disp + 2) = local_1e;
            *(undefined1 *)((int)&rec->ea1->disp + 3) = local_1d;
            status = read_backend_stream_bytes((char *)&ref_count,4);
            if (status == 0) {
              status = 0xffffffff;
            }
            else {
              read_operand_label_refs(ref_count,rec->ea1);
            }
          }
        }
      }
      break;
    case OP_MVA_FC:
      status = read_backend_stream_bytes((char *)&buf,2);
      if (status == 0) {
        status = 0xffffffff;
      }
      else {
        rec->flg = buf & REG_NON_E3;
        new_ea = pool_alloc(0xc);
        rec->ea1 = new_ea;
        if (rec->ea1 == (ea *)0x0) {
          report_message_at_source_line(0,0,0xbcd,(char *)0x0);
        }
        new_ea = pool_alloc(0xc);
        rec->ea2 = new_ea;
        if (rec->ea2 == (ea *)0x0) {
          report_message_at_source_line(0,0,0xbcd,(char *)0x0);
        }
        rec->tmp = local_23 & REG_R15;
        base_reg = (reg)(((int)(char)local_23 & 0xf0U) >> 4);
        rec->ea2->type = '\x01';
        rec->ea2->base = base_reg;
        status = read_backend_stream_bytes((char *)&local_22,1);
        if (status == 0) {
          status = 0xffffffff;
        }
        else {
          rec->ea1->type = '\a';
          status = read_backend_stream_bytes(&local_21,4);
          if (status == 0) {
            status = 0xffffffff;
          }
          else {
            *(char *)&rec->ea1->disp = local_21;
            *(char *)((int)&rec->ea1->disp + 1) = (char)local_20;
            *(undefined1 *)((int)&rec->ea1->disp + 2) = (*(unsigned char *)((char *)&local_20 + 1));
            *(undefined1 *)((int)&rec->ea1->disp + 3) = local_1e;
            status = read_backend_stream_bytes((char *)&ref_count,4);
            if (status == 0) {
              status = 0xffffffff;
            }
            else {
              read_operand_label_refs(ref_count,rec->ea1);
            }
          }
        }
      }
      break;
    case OP_MOVIF:
      status = read_backend_stream_bytes((char *)&buf,4);
      if (status == 0) {
        status = 0xffffffff;
      }
      else {
        rec->flg = buf & REG_NON_E3;
        rec->misc = local_23;
        new_ea = pool_alloc(0xc);
        rec->ea1 = new_ea;
        if (rec->ea1 == (ea *)0x0) {
          report_message_at_source_line(0,0,0xbcd,(char *)0x0);
        }
        new_ea = pool_alloc(0xc);
        rec->ea2 = new_ea;
        if (rec->ea2 == (ea *)0x0) {
          report_message_at_source_line(0,0,0xbcd,(char *)0x0);
        }
        rec->ea2->base = local_22;
        rec->tmp = local_21;
        rec->ea2->type = '\x01';
        status = read_backend_stream_bytes(&local_21,1);
        if (status == 0) {
          status = 0xffffffff;
        }
        else {
          rec->ea1->type = '\a';
          status = read_backend_stream_bytes((char *)&local_20,4);
          if (status == 0) {
            status = 0xffffffff;
          }
          else {
            *(char *)&rec->ea1->disp = (char)local_20;
            *(undefined1 *)((int)&rec->ea1->disp + 1) = (*(unsigned char *)((char *)&local_20 + 1));
            *(undefined1 *)((int)&rec->ea1->disp + 2) = local_1e;
            *(undefined1 *)((int)&rec->ea1->disp + 3) = local_1d;
            status = read_backend_stream_bytes((char *)&ref_count,4);
            if (status == 0) {
              status = 0xffffffff;
            }
            else {
              read_operand_label_refs(ref_count,rec->ea1);
            }
          }
        }
      }
      break;
    default:
      report_message_at_source_line(0,0,0x131f,(char *)0x0);
      break;
    case OP_FPRSET:
      status = read_backend_stream_bytes((char *)&buf,3);
      if (status == 0) {
        status = 0xffffffff;
      }
      else {
        rec->flg = buf & REG_NON_E3;
        new_ea = pool_alloc(0xc);
        rec->ea1 = new_ea;
        if (rec->ea1 == (ea *)0x0) {
          report_message_at_source_line(0,0,0xbcd,(char *)0x0);
        }
        rec->ea1->base = local_23;
        rec->ea1->type = '\x01';
        new_ea = pool_alloc(0xc);
        rec->ea2 = new_ea;
        if (rec->ea2 == (ea *)0x0) {
          report_message_at_source_line(0,0,0xbcd,(char *)0x0);
        }
        rec->ea2->base = local_22;
        rec->ea2->type = '\x01';
      }
      break;
    case OP_EXTLD:
      status = read_backend_stream_bytes((char *)&buf,1);
      if (status == 0) {
        status = 0xffffffff;
      }
      else {
        rec->flg = '\0';
        new_ea = pool_alloc(0xc);
        rec->ea1 = new_ea;
        if (rec->ea1 == (ea *)0x0) {
          report_message_at_source_line(0,0,0xbcd,(char *)0x0);
        }
        rec->ea1->base = buf;
        rec->ea1->type = '\x04';
        new_ea = pool_alloc(0xc);
        rec->ea2 = new_ea;
        if (rec->ea2 == (ea *)0x0) {
          report_message_at_source_line(0,0,0xbcd,(char *)0x0);
        }
        rec->ea2->base = REG_XMTRX;
        rec->ea2->type = '\x01';
      }
      break;
    case OP_EXTST:
      status = read_backend_stream_bytes((char *)&buf,1);
      if (status == 0) {
        status = 0xffffffff;
      }
      else {
        rec->flg = '\0';
        new_ea = pool_alloc(0xc);
        rec->ea1 = new_ea;
        if (rec->ea1 == (ea *)0x0) {
          report_message_at_source_line(0,0,0xbcd,(char *)0x0);
        }
        rec->ea1->base = REG_XMTRX;
        rec->ea1->type = '\x01';
        new_ea = pool_alloc(0xc);
        rec->ea2 = new_ea;
        if (rec->ea2 == (ea *)0x0) {
          report_message_at_source_line(0,0,0xbcd,(char *)0x0);
        }
        rec->ea2->base = buf;
        rec->ea2->type = '\x02';
      }
    }
  }
  return status;
#undef buf
#undef local_23
#undef local_22
#undef local_21
#undef local_20
#undef local_1e
#undef local_1d
#undef local_19
#undef local_18
#undef local_17
#undef local_16
#undef status
#undef base_reg
#undef ref_count
}



