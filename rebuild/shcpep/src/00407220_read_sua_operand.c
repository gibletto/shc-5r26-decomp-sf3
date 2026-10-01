#include "decls.h"
#include "imports.h"

// entry: 00407220
// name : read_sua_operand
// size : 889
// sig  : uint read_sua_operand(psd * rec, int which)


uint __cdecl read_sua_operand(psd *rec,int which)

{
  unsigned char _frec_10[16];
#define buf (*(byte (*)[8])(_frec_10 + 0))
#define n_labels (*(int *)(_frec_10 + 8))
#define gbr_disp (*(int *)(_frec_10 + 12))
  byte new_type;
  ea *op;
  uint uVar1;
  uint nread;
  byte old_type;
  psd_op opcode;
  
  buf[0] = 0;
  buf[1] = 0;
  buf[2] = 0;
  buf[3] = 0;
  buf[4] = 0;
  op = alloc_zeroed(0xc);
  if (op == (ea *)0x0) {
    report_compiler_message(0,0,0xbcd,(char *)0x0);
  }
  if (which == 1) {
    rec->ea1 = op;
  }
  else if (which == 2) {
    rec->ea2 = op;
  }
  else {
    report_compiler_message(0,0,0x131e,(char *)0x0);
  }
  uVar1 = read_sua_bytes((char *)buf,1);
  if (uVar1 == 0) {
    return 0xffffffff;
  }
  old_type = op->type;
  new_type = buf[0] & 0x1f | old_type;
  op->type = new_type;
  op->type = buf[0] & 0x80 | new_type;
  switch(buf[0] & 0x1f | old_type & 0x1f) {
  case 0:
    return uVar1;
  case 1:
  case 2:
  case 3:
  case 4:
  case 0xf:
  case 0x10:
    uVar1 = read_sua_bytes((char *)buf,1);
    if (uVar1 != 0) {
      op->base = buf[0];
      return uVar1;
    }
    return 0xffffffff;
  case 5:
    uVar1 = read_sua_bytes((char *)buf,1);
    if (uVar1 != 0) {
      op->base = buf[0] + 0x61;
      return uVar1;
    }
    return 0xffffffff;
  case 6:
    uVar1 = read_sua_bytes((char *)buf,1);
    if (uVar1 != 0) {
      op->base = buf[0] + 100;
      return uVar1;
    }
    return 0xffffffff;
  case 7:
    break;
  case 8:
    uVar1 = read_sua_bytes((char *)buf,1);
    if (uVar1 == 0) {
      return 0xffffffff;
    }
    op->base = buf[0];
    uVar1 = read_sua_bytes((char *)(buf + 3),2);
    if (uVar1 != 0) {
      op->disp = (int)CONCAT11(buf[4],buf[3]);
      return uVar1;
    }
    return 0xffffffff;
  case 9:
    uVar1 = read_sua_bytes((char *)buf,1);
    if (uVar1 != 0) {
      op->index = buf[0] & 0xf;
      op->base = buf[0] >> 4;
      return uVar1;
    }
    return 0xffffffff;
  case 10:
    uVar1 = read_sua_bytes((char *)(buf + 3),2);
    if (uVar1 != 0) {
      op->disp = (int)CONCAT11(buf[4],buf[3]);
      op->base = 'k';
      return uVar1;
    }
    return 0xffffffff;
  case 0xb:
    uVar1 = read_sua_bytes((char *)&gbr_disp,4);
    if (uVar1 == 0) {
      return 0xffffffff;
    }
    op->disp = gbr_disp;
    op->base = 'b';
    uVar1 = read_sua_bytes((char *)&n_labels,4);
    if (uVar1 != 0) {
      read_sua_label_refs(n_labels,op);
      return uVar1;
    }
    return 0xffffffff;
  case 0xc:
    uVar1 = read_sua_bytes((char *)buf,1);
    if (uVar1 != 0) {
      op->index = buf[0];
      op->base = 'b';
      return uVar1;
    }
    return 0xffffffff;
  default:
    report_compiler_message(0,0,0x1320,(char *)0x0);
    return uVar1;
  }
  uVar1 = psd_operand_size_bytes(rec);
  nread = read_sua_bytes((char *)buf,uVar1);
  if (nread == 0) {
    return 0xffffffff;
  }
  set_ea_disp_sign_extended((short *)buf,op,uVar1);
  opcode = rec->op;
  if ((((opcode == OP_AND) || (opcode == OP_OR)) || (opcode == OP_TST)) ||
     ((opcode == OP_XOR || (opcode == OP_TRAPA)))) {
    op->disp = op->disp & 0xff;
  }
  uVar1 = read_sua_bytes((char *)&n_labels,4);
  if (uVar1 != 0) {
    read_sua_label_refs(n_labels,op);
    return uVar1;
  }
  return 0xffffffff;
#undef buf
#undef n_labels
#undef gbr_disp
}



