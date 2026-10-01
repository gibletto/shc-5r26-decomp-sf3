#include "decls.h"
#include "imports.h"

// entry: 00403fd0
// name : delete_extensions_before_narrow_stores
// size : 1238
// sig  : void delete_extensions_before_narrow_stores(code_node * node)


int __cdecl delete_extensions_before_narrow_stores(code_node *node)

{
  uchar clobbered_reg;
  uchar used_reg;
  byte size;
  byte kind;
  char ok;
  uchar changed;
  psd *rec;
  uint is_volatile;
  psd *scan;
  psd *new_overwrite;
  ea *operand;
  byte dst_kind;
  psd *ext;
  psd *overwrite;
  int call_mode;
  int i;
  bool blocked;
  bool needs_r0;
  psd_op op;
  
  call_mode = 0;
  while( true ) {
    if (node == (code_node *)0x0) {
      return;
    }
    i = 0;
    ext = node->psd;
    if (ext != (psd *)0x0) break;
LAB_00404493:
    node = node->next;
  }
LAB_00404002:
  if (i < 0xf) {
    if ((ext->op == OP_EXTS) || (ext->op == OP_EXTU)) {
      size = ext->flg & 3;
      clobbered_reg = ext->ea1->base;
      used_reg = ext->ea2->base;
      rec = find_next_psd_record(node,ext);
      while (rec != (psd *)0x0) {
        if ((((rec->op == OP_MOV) && ((rec->flg & 3U) == size)) && ((rec->ea2->type & 0x80) == 0))
           && (((((is_volatile = is_record_volatile(rec), is_volatile == 0 &&
                  (kind = rec->ea2->type & 0x1f, kind != 3)) && (kind != 4)) &&
                ((kind == 2 || ((7 < kind && (kind < 0xd)))))) &&
               (ok = operands_equal(ext->ea2,rec->ea1), ok != '\0')))) {
          if ((((used_reg == clobbered_reg) || (used_reg != '\0')) ||
              ((kind = rec->ea2->type & 0x1f, kind != 8 && (kind != 0xb)))) &&
             (((scan = find_next_psd_record(node,rec), scan == (psd *)0x0 ||
               (used_reg == clobbered_reg)) ||
              (ok = no_use_after_register_clobbered(node,scan,used_reg,clobbered_reg), ok != '\0')))
             ) {
            overwrite = (psd *)0x0;
            blocked = false;
            goto joined_r0x004041b0;
          }
          break;
        }
        if (((((rec->ea1 == (ea *)0x0) ||
              (ok = operand_uses_register(rec,used_reg,'\x01'), ok == '\0')) &&
             ((rec->ea2 == (ea *)0x0 ||
              (ok = operand_uses_register(rec,used_reg,'\x02'), ok == '\0')))) &&
            (((((changed = record_changes_register(rec,used_reg), changed == '\0' &&
                (changed = record_changes_register(rec,clobbered_reg), changed == '\0')) &&
               (op = rec->op, op != OP_CALL)) && ((op != OP_JSR && (op != OP_BSR)))) &&
             (op != OP_TRAPA)))) && (op != OP_BSRF)) {
          rec = find_next_psd_record(node,rec);
        }
        else {
          rec = (psd *)0x0;
        }
      }
    }
    goto LAB_00404484;
  }
  goto LAB_00404493;
joined_r0x004041b0:
  new_overwrite = overwrite;
  if ((scan == (psd *)0x0) || (blocked)) goto LAB_004043fe;
  if (used_reg == '\0') {
    op = scan->op;
    if (((op != OP_CMP_EQ) && (op != OP_TST)) || ((scan->ea1->type & 0x1f) != 7)) {
      if (op == OP_MOV) {
        operand = scan->ea1;
        if ((scan->flg & 3U) == 2) {
          kind = operand->type & 0x1f;
          if (((kind == 9) || (dst_kind = scan->ea2->type & 0x1f, dst_kind == 9)) ||
             ((kind == 0xb || (dst_kind == 0xb)))) goto LAB_00404253;
          needs_r0 = false;
        }
        else {
          kind = operand->type & 0x1f;
          if ((kind != 8) || (operand->disp == 0)) {
            dst_kind = scan->ea2->type & 0x1f;
            if (((dst_kind != 8) || (scan->ea2->disp == 0)) &&
               ((((kind != 9 && (dst_kind != 9)) && (kind != 0xb)) &&
                (needs_r0 = false, dst_kind != 0xb)))) goto LAB_00404258;
          }
LAB_00404253:
          needs_r0 = true;
        }
LAB_00404258:
        if (needs_r0) goto LAB_004042a2;
      }
      if ((((op == OP_CASEJMP) || ((OP_BEND < op && (op < OP_NON_1C)))) ||
          ((op == OP_CTBL ||
           ((((op == OP_CENT || (op == OP_LINE)) || (op == OP_NON_10)) || (op == OP_PROGRAM)))))) ||
         (((scan->ea1 == (ea *)0x0 || ((scan->ea1->type & 0x1f) != 0xc)) &&
          ((scan->ea2 == (ea *)0x0 || ((scan->ea2->type & 0x1f) != 0xc)))))) goto LAB_004042af;
    }
LAB_004042a2:
    blocked = true;
    goto joined_r0x004041b0;
  }
LAB_004042af:
  if (((scan->ea1 != (ea *)0x0) && (ok = operand_uses_register(scan,used_reg,'\x01'), ok != '\0'))
     && ((scan->flg & 3U) != size)) {
    blocked = true;
  }
  if (((scan->ea2 != (ea *)0x0) && (ok = operand_uses_register(scan,used_reg,'\x02'), ok != '\0'))
     && ((scan->flg & 3U) != size)) {
    blocked = true;
  }
  changed = record_changes_register(scan,used_reg);
  if (changed == '\0') {
    op = scan->op;
    if (((op == OP_CALL) || (op == OP_JSR)) ||
       ((op == OP_BSR || ((op == OP_TRAPA || (op == OP_BSRF)))))) {
      new_overwrite = psd_overwrites_register(scan,used_reg);
      if (new_overwrite != (psd *)0x0) {
        if (((ext->misc & 0x10U) != 0) && ((rec->misc & 0x10U) != 0)) {
          call_mode = 1;
        }
        ok = call_register_effect(scan,used_reg,call_mode);
        new_overwrite = scan;
        if (ok == '\x01') goto LAB_004043fe;
        if (ok == '\0') goto LAB_00404381;
      }
      blocked = true;
      new_overwrite = overwrite;
      goto LAB_004043fe;
    }
LAB_00404381:
    scan = find_next_psd_record(node,scan);
    goto joined_r0x004041b0;
  }
  overwrite = psd_overwrites_register(scan,used_reg);
  new_overwrite = overwrite;
  if (overwrite != (psd *)0x0) {
    if (!blocked) goto LAB_00404405;
    if (((*(short *)(&g_op_dest_operand + (uint)overwrite->op * 2) == 2) &&
        (overwrite->ea1 != (ea *)0x0)) &&
       (ok = operand_uses_register(overwrite,used_reg,'\x01'), ok == '\0')) {
      blocked = false;
    }
  }
LAB_004043fe:
  overwrite = new_overwrite;
  if (!blocked) {
LAB_00404405:
    if (overwrite != (psd *)0x0) {
      scan = find_next_psd_record(node,rec);
      if (scan != (psd *)0x0) {
        do {
          if ((overwrite == scan) ||
             (ok = rename_register_until_redefined(scan,used_reg,clobbered_reg), ok != '\0')) break;
          scan = find_next_psd_record(node,scan);
        } while (scan != (psd *)0x0);
        if (scan != (psd *)0x0) {
          rename_register_until_redefined(scan,used_reg,clobbered_reg);
        }
      }
      operand = copy_ea(ext->ea1);
      rec->ea1 = operand;
      delete_psd_record(ext);
    }
  }
LAB_00404484:
  i = i + 1;
  ext = ext + 1;
  if (ext == (psd *)0x0) goto LAB_00404493;
  goto LAB_00404002;
}



