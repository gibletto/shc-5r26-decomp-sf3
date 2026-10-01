#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_request
#define g_request (*(request * *)(g_sd + 0x1eea0))


// entry: 00420e10
// name : emit_psd_instruction
// size : 1383
// sig  : void emit_psd_instruction(ushort op, char tmp, char flag_20, uchar size, uchar misc, ea * src, ea * dst)


int __cdecl emit_psd_instruction(ushort op,char tmp,char flag_20,uchar size,uchar misc,ea *src,ea *dst)

{
  byte bVar1;
  short sVar2;
  int iVar3;
  byte dst_kind;
  int iVar4;
  bool bVar5;
  psd *rec;
  byte *bit_byte;
  label_ref *labels;
  
  if (op == 0) {
    return;
  }
  if ((op == 0x40) && (sVar2 = ea_operands_equal(src,dst), sVar2 != 0)) {
    return;
  }
  if ((op == 0x1200) && (sVar2 = ea_operands_equal(src,dst), sVar2 != 0)) {
    return;
  }
  if ((op == 0x1300) && (sVar2 = ea_operands_equal(src,dst), sVar2 != 0)) {
    return;
  }
  if ((op == 0x1400) && (sVar2 = ea_operands_equal(src,dst), sVar2 != 0)) {
    return;
  }
  if ((((op == 0x60) && ((src->type & 0x1f) == 7)) && (src->disp == 0)) &&
     (src->labels == (label_ref *)0x0)) {
    return;
  }
  if (((op == 0x81) && ((src->type & 0x1f) == 7)) &&
     ((src->disp == 0 && (src->labels == (label_ref *)0x0)))) {
    return;
  }
  if (op < 0x2f) {
    if ((op != 0x2e) && (op != 0x27)) {
      size = 2;
    }
  }
  else if (op < 0x73) {
    if (op != 0x72) {
      if (op == 0x40) {
        bVar1 = src->type & 0x1f;
        if (((bVar1 == 4) && (src->base == '\x0f')) ||
           (((dst_kind = dst->type & 0x1f, dst_kind == 3 && (dst->base == '\x0f')) ||
            (((bVar1 == 1 || (bVar1 == 7)) && (dst_kind == 1)))))) {
          size = 2;
        }
      }
      else {
        size = 2;
      }
    }
  }
  else if (op < 0x83) {
    if (op < 0x80) {
      if (op < 0x7b) goto switchD_00420fb7_caseD_b9;
      if (op < 0x7d) {
        if ((((src->type & 0x1f) == 4) && (src->base == '\x0f')) ||
           (((dst->type & 0x1f) == 3 && (dst->base == '\x0f')))) {
          size = 2;
        }
      }
      else {
        size = 2;
      }
    }
    else {
LAB_004210c3:
      size = ((dst->type & 0x1f) == 0xc) - 1U & 2;
LAB_004211cf:
      if ((src->type & 0x1f) == 7) {
        src->disp = (uint)(byte)src->disp;
      }
    }
  }
  else if (op < 0x9f) {
    if (op == 0x9e) goto LAB_004211cf;
    if (op == 0x85) goto LAB_004210c3;
    if (op == 0x86) {
      size = 0;
    }
    else {
      size = 2;
    }
  }
  else if (op < 0xb7) {
    if (op < 0xb5) {
      if (op == 0xb0) {
        if (((((src->type & 0x1f) == 1) && (src->base < ' ')) && ('\x0f' < src->base)) ||
           ((((dst->type & 0x1f) == 1 && (dst->base < ' ')) && ('\x0f' < dst->base)))) {
          size = 2;
        }
        else {
          report_codegen_message(0x1231,g_msg_filn,(uint)g_msg_line,(int)g_msg_listno,(char *)0x0);
        }
      }
      else {
        size = 2;
      }
    }
    else {
      size = 3;
    }
  }
  else if (op < 200) {
    if (op == 199) {
LAB_0042116c:
      if ((((src->type & 0x1f) == 1) && (src->base < '/')) && ('\x1f' < src->base)) {
        size = 3;
      }
      else {
        size = 2;
      }
    }
    else {
      switch(op) {
      case 0xb8:
      case 0xba:
      case 0xbc:
      case 0xbe:
      case 0xc0:
      case 0xc1:
switchD_00420fb7_caseD_b8:
        if (((((src->type & 0x1f) == 1) && (src->base < '/')) && ('\x1f' < src->base)) ||
           ((((dst->type & 0x1f) == 1 && (dst->base < '/')) && ('\x1f' < dst->base)))) {
          size = 3;
        }
        else {
          size = 2;
        }
        break;
      default:
switchD_00420fb7_caseD_b9:
        size = 2;
      }
    }
  }
  else if (op < 0xde) {
    if (0xdb < op) goto switchD_00420fb7_caseD_b8;
    if (((op == 0xd0) || (op == 0xd2)) || (op == 0xd4)) goto LAB_0042116c;
    size = 2;
  }
  else if (op < 0x1301) {
    if ((op == 0x1300) || (op == 0x1200)) {
LAB_00421187:
      if (op == 0x1200) {
        op = 0x40;
        size = 0;
      }
      else {
        bVar5 = op == 0x1300;
        op = 0x40;
        size = 2 - bVar5;
      }
    }
    else {
      size = 2;
    }
  }
  else {
    if (op < 0x1801) {
      if (op != 0x1800) {
        if (op == 0x1400) goto LAB_00421187;
        size = 2;
        goto LAB_004211e7;
      }
    }
    else if ((op != 0x1900) && (op != 0x1a00)) goto switchD_00420fb7_caseD_b9;
    if (op == 0x1800) {
      op = 0x27;
      size = 0;
    }
    else {
      bVar5 = op == 0x1900;
      op = 0x27;
      size = 2 - bVar5;
    }
  }
LAB_004211e7:
  if ((op == 0x27) && ((src->type & 0x1f) == 1)) {
    misc = misc | 0x80;
  }
  if ((src != (ea *)0x0) && ((src->type & 0x80) != 0)) {
    size = size | 0x80;
  }
  if ((dst != (ea *)0x0) && ((dst->type & 0x80) != 0)) {
    size = size | 0x80;
  }
  if (flag_20 == '\x01') {
    size = size | 0x20;
  }
  if (g_template_value_unused == 1) {
    misc = misc | 0x20;
  }
  fill_psd_record((psd *)&g_psd_scratch,(psd_op)op,size,misc,g_stmt_serial,g_msg_filn,g_msg_line,src
                  ,dst,g_sptravel,tmp);
  if (op == 0x23) {
    if (src->labels == (label_ref *)0x0) {
      sVar2 = 0;
    }
    else {
      sVar2 = src->labels->labno1;
    }
    if (0xb6 < sVar2) goto LAB_00421363;
    *(ushort *)(g_current_aux_record + 10) = *(ushort *)(g_current_aux_record + 10) & 0x7fff;
    labels = src->labels;
    iVar3 = 0;
    if (labels != (label_ref *)0x0) {
      iVar3 = (int)labels->labno1;
    }
    iVar4 = 0;
    if (labels != (label_ref *)0x0) {
      iVar4 = (int)labels->labno1;
    }
    bit_byte = (byte *)(g_current_aux_record + 0x2c +
                       ((int)(iVar3 + -1 + (iVar3 + -1 >> 0x1f & 7U)) >> 3));
    bVar1 = (byte)(iVar4 + -1 >> 0x1f);
    iVar3 = 0;
    *bit_byte = *bit_byte |
                (byte)(0x80 >> ((((byte)(iVar4 + -1) ^ bVar1) - bVar1 & 7 ^ bVar1) - bVar1 & 0x1f));
    labels = src->labels;
    if (labels != (label_ref *)0x0) {
      iVar3 = (int)labels->labno1;
    }
    if ((&g_routine_stack_adjust)[iVar3] == 0) goto LAB_00421363;
    if (g_request->cpu == 4) {
      sVar2 = 0;
      if (labels != (label_ref *)0x0) {
        sVar2 = labels->labno1;
      }
      if (sVar2 != 0x38) goto LAB_00421363;
      sVar2 = 0;
      if (labels != (label_ref *)0x0) {
        sVar2 = labels->labno1;
      }
      if (sVar2 != 0x34) goto LAB_00421363;
    }
    iVar3 = 0;
    if (labels != (label_ref *)0x0) {
      iVar3 = (int)labels->labno1;
    }
    rec = (psd *)0x0;
    iVar3 = (&g_routine_stack_adjust)[iVar3];
    iVar4 = 1;
  }
  else {
    rec = (psd *)&g_psd_scratch;
    iVar3 = 0;
    iVar4 = 0;
  }
  update_stack_travel(iVar4,iVar3,rec);
LAB_00421363:
  emit_psd_record((psd *)&g_psd_scratch,0);
  return;
}



