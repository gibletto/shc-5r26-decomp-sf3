#include "decls.h"
#include "imports.h"
/* the types Ghidra's decompiler used for these globals in this function */
#undef g_aux_record_table
#define g_aux_record_table (*(aux_record * *)(g_sd + 0x6d50))
#undef g_pool_carried_has_word
#define g_pool_carried_has_word (*(char *)(g_sd + 0x3c74))
#undef g_pool_carried_literal_bytes
#define g_pool_carried_literal_bytes (*(unsigned int *)(g_sd + 0x3c6c))
#undef g_pool_segment_has_word
#define g_pool_segment_has_word (*(char *)(g_sd + 0x3c78))
#undef g_request
#define g_request (*(request * *)(g_sd + 0x6e04))


// entry: 004179a0
// name : decide_literal_pool_placement
// size : 4759
// sig  : uint decide_literal_pool_placement(psd * rec, FILE * lit_out)


/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

#if SHC_REBUILD_UPDATED
#include <stdio.h>
#include <stdlib.h>
static int pepk(const char *name, int dflt) {
    char *v = getenv(name);
    return v ? (int)strtol(v, 0, 0) : dflt;
}
static void peplog(const char *kind, int op, int c68, int c64, int l4, int i11, int c70, int c6c, int lim, int dec) {
    static FILE *lf; static int opened;
    if (!opened) { char *p = getenv("PEP_LOG"); opened = 1; if (p) lf = fopen(p, "a"); }
    if (lf) { fprintf(lf, "%s %x %d %d %d %d %d %d %d %d\n", kind, op, c68, c64, l4, i11, c70, c6c, lim, dec); fflush(lf); }
}
/* PEP_WFROM / PEP_LFROM: measure the word (long) literal window from the first instruction that references a pending
   word (long) literal instead of from the last pool. pep_segw/l: offset in the current branch segment of the first
   such reference (-1 none); pep_w/l: its offset from the window start once the segment is behind a kept branch */
static int pep_w = -1, pep_l = -1, pep_segw = -1, pep_segl = -1;
#define PEPK(n, d) pepk("PEP_" #n, d)
#define PEPLOG(k, dec) peplog(k, rec->op, g_pool_code_bytes, _g_pool_pending_literal_bytes, local_4, literal_bytes, g_pool_carried_code_bytes, _g_pool_carried_literal_bytes, iVar2, dec)
static int pepadj(int word, int c70) {
    int f;
    if (word) {
        if (!PEPK(WFROM, 0)) return 0;
        f = pep_w >= 0 ? pep_w : (pep_segw >= 0 ? c70 + pep_segw : -1);
    } else {
        if (!PEPK(LFROM, 0)) return 0;
        f = pep_l >= 0 ? pep_l : (pep_segl >= 0 ? c70 + pep_segl : -1);
    }
    return f > 0 ? f : 0;
}
#define PEPADJ() pepadj(g_pool_carried_has_word == 1 || g_pool_segment_has_word == 1, (int)g_pool_carried_code_bytes)
#define PEPTRACK() do { if (literal_bytes == 2 && pep_segw < 0) pep_segw = g_pool_code_bytes; \
                        if (literal_bytes == 4 && pep_segl < 0) pep_segl = g_pool_code_bytes; } while (0)
#define PEPKEEP() do { if (pep_w < 0 && pep_segw >= 0) pep_w = (int)g_pool_carried_code_bytes + pep_segw; \
                       if (pep_l < 0 && pep_segl >= 0) pep_l = (int)g_pool_carried_code_bytes + pep_segl; \
                       pep_segw = pep_segl = -1; } while (0)
#define PEPFLUSH() do { pep_w = pep_segw; pep_l = pep_segl; pep_segw = pep_segl = -1; } while (0)
#define PEPRESET() do { pep_w = pep_l = pep_segw = pep_segl = -1; } while (0)
#else
#define PEPK(n, d) (d)
#define PEPLOG(k, dec) ((void)0)
#define PEPADJ() 0
#define PEPTRACK() ((void)0)
#define PEPKEEP() ((void)0)
#define PEPFLUSH() ((void)0)
#define PEPRESET() ((void)0)
#endif

uint __cdecl decide_literal_pool_placement(psd *rec,FILE *lit_out)

{
  unsigned char _frec_9[9];
#define local_9 (*(bool *)(_frec_9 + 0))
#define local_8 (*(ea * *)(_frec_9 + 1))
#define local_4 (*(uint *)(_frec_9 + 5))
  byte use_ea2;
  short sVar1;
  ushort stack_kind;
  label_ref *lref;
  int found_frame;
  uint attr_bits;
  int iVar2;
  ea *labels_ea;
  ea *disp_ea;
  int literal_bytes;
  uint pool_bytes;
  bool fits;
  psd_op op;
  literal_table *table;
  
  literal_bytes = 0;
  pool_bytes = 0;
  op = rec->op;
  iVar2 = 0;
  PEPLOG("R", 0);
  local_8 = (ea *)0x0;
  local_4 = 0;
  if (op == OP_CASEJMP) {
LAB_00418aea:
    PEPLOG("E", op);
    if (op == OP_NON_10 || (op == OP_CASEJMP && PEPK(LAT11, 0))) {
LAB_00418af2:
      if (g_pool_code_bytes + _g_pool_pending_literal_bytes + (PEPK(LCARRY, 0) ? _g_pool_carried_literal_bytes : 0) != 0) {
        fits = (int)(g_pool_code_bytes + _g_pool_pending_literal_bytes + g_pool_carried_code_bytes +
                    _g_pool_carried_literal_bytes) <=
               (int)((-(uint)(g_pool_carried_has_word == '\x01') & 0xfffffe02) + 0x3cc);
        if (fits) {
          pool_bytes = CONCAT22((short)(_g_pool_pending_literal_bytes >> 0x10),
                                (short)_g_pool_pending_literal_bytes + g_pool_carried_literal_bytes)
          ;
        }
        else {
          pool_bytes = _g_pool_pending_literal_bytes & 0xffff;
        }
        local_9 = !fits;
        PEPLOG("L", local_9);
        if ((short)pool_bytes == 0) {
          g_pool_flush_pending = 1;
        }
        else {
          attr_bits = write_file_bytes(lit_out,&local_9,1);
          if (attr_bits == 0xffffffff) {
            report_compiler_message(0,0,0xce7,(char *)0x0);
          }
          g_pool_flush_pending = 0;
        }
      }
    }
    if (rec->op == OP_CASEJMP) {
      pool_bytes = CONCAT22((short)(pool_bytes >> 0x10),0x400);
    }
    clear_pool_literal_table(&g_word_literal_table);
    clear_pool_literal_table(&g_long_literal_table);
    clear_pool_literal_table(&g_frame_offset_literal_table);
    if (_g_pool_pending_literal_bytes + _g_pool_carried_literal_bytes == 0) {
      if (g_pool_carried_code_bytes < 0x400) {
        g_pool_carried_code_bytes = 0;
      }
    }
    else {
      g_pool_carried_code_bytes = 0x400;
    }
    _g_pool_carried_literal_bytes = 0;
    g_pool_code_bytes = 0;
    _g_pool_pending_literal_bytes = 0;
    g_pool_segment_has_word = '\0';
    g_pool_carried_has_word = '\0';
    goto LAB_00418c0c;
  }
  if ((((op == OP_CTBL) || (op == OP_PROGRAM)) || (op == OP_CENT)) ||
     ((op == OP_NON_10 && (rec->ea2 == (ea *)0x0)))) {
    if (op == OP_CASEJMP) goto LAB_00418aea;
    if (op != OP_NON_10) {
      if (op == OP_PROGRAM) {
        g_pool_carried_code_bytes = 0x400;
      }
      goto LAB_00418c0c;
    }
    goto LAB_00418af2;
  }
  sVar1 = compute_record_code_size(rec);
  local_4 = (uint)sVar1;
  switch(rec->op) {
  case OP_ENTER:
    if (((g_aux_record_table[g_current_aux_index].flags & 0x4000) != 0) &&
       (stack_kind = g_aux_record_table[g_current_aux_index].flags & 0x1800, stack_kind != 0)) {
      if (stack_kind == 0x800) {
        attr_bits = g_aux_record_table[g_current_aux_index].stack_value;
        if (((int)attr_bits < -0x80) || (0x7f < (int)attr_bits)) {
          if (((int)attr_bits < -0x8000) || (0x7fff < (int)attr_bits)) {
            iVar2 = find_pool_literal(&g_long_literal_table,attr_bits,(label_ref *)0x0);
            if (iVar2 == 0) {
              literal_bytes = 4;
            }
          }
          else {
            iVar2 = find_pool_literal(&g_word_literal_table,attr_bits,(label_ref *)0x0);
            if (iVar2 == 0) {
              g_pool_segment_has_word = '\x01';
              literal_bytes = 2;
            }
          }
        }
      }
      else {
        lref = alloc_zeroed(8);
        lref->labno1 = (short)g_aux_record_table[g_current_aux_index].stack_value;
        lref->labno2 = 0;
        attr_bits = get_symbol_attr_low_bits(lref->labno1);
        if ((attr_bits != 1) &&
           ((attr_bits = get_symbol_attr_low_bits(lref->labno1), attr_bits == 0 ||
            (((byte)(g_aux_record_table[g_current_aux_index].flags >> 8) & 0x18) != 0x10)))) {
          iVar2 = get_symbol_attr_bit5_or_forced(lref->labno1);
          if (iVar2 == 0) {
            iVar2 = find_pool_literal(&g_long_literal_table,0,lref);
            if (iVar2 == 0) {
              literal_bytes = 4;
            }
          }
          else {
            iVar2 = find_pool_literal(&g_word_literal_table,0,lref);
            if (iVar2 == 0) {
              g_pool_segment_has_word = '\x01';
              literal_bytes = 2;
            }
          }
        }
        pool_free(lref,8);
      }
    }
    iVar2 = g_aux_record_table[g_current_aux_index].frame_size;
    if ((iVar2 < -0x7f) || (0x80 < iVar2)) {
      if ((iVar2 < 0x8001) && (-0x8000 < iVar2)) {
        iVar2 = find_pool_literal(&g_word_literal_table,-iVar2,(label_ref *)0x0);
        if (iVar2 == 0) {
          g_pool_segment_has_word = '\x01';
          literal_bytes = literal_bytes + 2;
        }
      }
      else {
        iVar2 = find_pool_literal(&g_long_literal_table,-iVar2,(label_ref *)0x0);
        if (iVar2 == 0) {
          literal_bytes = literal_bytes + 4;
        }
      }
    }
    break;
  case OP_EXIT:
    attr_bits = g_aux_record_table[g_current_aux_index].sp_adjust +
                g_aux_record_table[g_current_aux_index].frame_size;
    if (((int)attr_bits < 0x80) && (-0x81 < (int)attr_bits)) break;
    if ((-0x8001 < (int)attr_bits) && ((int)attr_bits < 0x8000)) {
      iVar2 = find_pool_literal(&g_word_literal_table,attr_bits,(label_ref *)0x0);
      if (iVar2 == 0) {
        g_pool_segment_has_word = '\x01';
        literal_bytes = 2;
      }
      break;
    }
    iVar2 = find_pool_literal(&g_long_literal_table,attr_bits,(label_ref *)0x0);
    if (iVar2 != 0) break;
    goto LAB_004180c0;
  case OP_RETURN:
    sVar1 = count_saved_registers((short)g_current_aux_index);
    if (sVar1 < 2) {
      attr_bits = g_aux_record_table[g_current_aux_index].sp_adjust +
                  g_aux_record_table[g_current_aux_index].frame_size;
      if ((0x7f < (int)attr_bits) || ((int)attr_bits < -0x80)) {
        if (((int)attr_bits < -0x8000) || (0x7fff < (int)attr_bits)) {
          iVar2 = find_pool_literal(&g_long_literal_table,attr_bits,(label_ref *)0x0);
          goto joined_r0x004180be;
        }
        iVar2 = find_pool_literal(&g_word_literal_table,attr_bits,(label_ref *)0x0);
        if (iVar2 == 0) {
          g_pool_segment_has_word = '\x01';
          literal_bytes = 2;
        }
      }
    }
    else {
      lref = alloc_zeroed(8);
      lref->labno1 = rec->ea1->labels->labno1;
      if (g_request->pic == 0) {
        iVar2 = find_pool_literal(&g_long_literal_table,0,lref);
        if (iVar2 == 0) {
          literal_bytes = 4;
        }
      }
      else {
        lref->labno2 = -g_literal_label_serial;
        g_literal_label_serial = g_literal_label_serial + 1;
        iVar2 = find_pool_literal(&g_long_literal_table,0xfffffffc,lref);
        if (iVar2 == 0) {
          literal_bytes = 4;
        }
        else {
          report_compiler_message(0,0,0x12f3,(char *)0x0);
        }
      }
      pool_free(lref,8);
    }
    break;
  case OP_CALL:
  case OP_JUMP:
  case OP_JUMPT:
  case OP_JUMPF:
  case OP_MOVA_FC:
    lref = alloc_zeroed(8);
    sVar1 = rec->ea1->labels->labno1;
    lref->labno1 = sVar1;
    if (g_request->pic == 0) {
      iVar2 = get_symbol_attr_bit5_or_forced(sVar1);
      if (iVar2 == 0) {
        iVar2 = find_pool_literal(&g_long_literal_table,0,lref);
        if (iVar2 == 0) {
          literal_bytes = 4;
        }
      }
      else {
        iVar2 = find_pool_literal(&g_word_literal_table,0,lref);
        if (iVar2 == 0) {
          g_pool_segment_has_word = '\x01';
          literal_bytes = 2;
        }
      }
    }
    else {
      lref->labno2 = -g_literal_label_serial;
      g_literal_label_serial = g_literal_label_serial + 1;
      iVar2 = find_pool_literal(&g_long_literal_table,(rec->op == OP_MOVA_FC) - 1 & 0xfffffffc,lref)
      ;
      if (iVar2 == 0) {
        literal_bytes = 4;
      }
      else {
        report_compiler_message(0,0,0x12f3,(char *)0x0);
      }
    }
    pool_free(lref,8);
    break;
  case OP_MOV_LOC:
    if ((rec->misc & 0x80U) == 0) {
      labels_ea = rec->ea1;
    }
    else {
      labels_ea = rec->ea2;
    }
    iVar2 = frame_offset_to_sp_displacement(labels_ea->disp,rec->sptravel);
    if ((0x7f < iVar2) || (iVar2 < -0x80)) {
      use_ea2 = rec->misc & 0x80;
      if (use_ea2 == 0) {
        labels_ea = rec->ea1;
      }
      else {
        labels_ea = rec->ea2;
      }
      if (use_ea2 == 0) {
        disp_ea = rec->ea1;
      }
      else {
        disp_ea = rec->ea2;
      }
      found_frame = find_pool_literal(&g_frame_offset_literal_table,disp_ea->disp,labels_ea->labels)
      ;
      if (found_frame == 0) {
        if ((0x7fff < iVar2) || (literal_bytes = 2, iVar2 < -0x8000)) {
          literal_bytes = 4;
        }
        if ((iVar2 < 0x8002) && (-0x8001 < iVar2)) {
          g_pool_segment_has_word = '\x01';
        }
      }
    }
    break;
  case OP_MOVA_LC:
    iVar2 = frame_offset_to_sp_displacement(rec->ea1->disp,rec->sptravel);
    if (((0x7f < iVar2) || (iVar2 < -0x80)) &&
       (found_frame = find_pool_literal(&g_frame_offset_literal_table,rec->ea1->disp,
                                        rec->ea1->labels), found_frame == 0)) {
      if ((0x7fff < iVar2) || (literal_bytes = 2, iVar2 < -0x8000)) {
        literal_bytes = 4;
      }
      if ((iVar2 < 0x8002) && (-0x8001 < iVar2)) {
        g_pool_segment_has_word = '\x01';
      }
    }
    break;
  case OP_MOVA_PC:
  case OP_MOVI:
    if (rec->op == OP_MOVI) {
      lref = rec->ea1->labels;
      if ((((lref == (label_ref *)0x0) && (iVar2 = rec->ea1->disp, -0x81 < iVar2)) && (iVar2 < 0x80)
          ) || (iVar2 = get_marked_symbol_kind(lref), iVar2 == 1)) break;
    }
    if ((((rec->op == OP_MOVI) && (rec->ea1->labels == (label_ref *)0x0)) &&
        (attr_bits = rec->ea1->disp, -0x8001 < (int)attr_bits)) && ((int)attr_bits < 0x8000)) {
      iVar2 = find_pool_literal(&g_word_literal_table,attr_bits,(label_ref *)0x0);
      if (iVar2 == 0) {
        g_pool_segment_has_word = '\x01';
        literal_bytes = 2;
      }
    }
    else {
      iVar2 = is_word_symbol_literal(rec->ea1->disp,rec->ea1->labels);
      if ((iVar2 == 0) && (iVar2 = get_marked_symbol_kind(rec->ea1->labels), iVar2 == 0)) {
        iVar2 = find_pool_literal(&g_long_literal_table,rec->ea1->disp,rec->ea1->labels);
        goto joined_r0x004180be;
      }
      iVar2 = find_pool_literal(&g_word_literal_table,rec->ea1->disp,rec->ea1->labels);
      if (iVar2 == 0) {
        g_pool_segment_has_word = '\x01';
        literal_bytes = 2;
      }
    }
    break;
  case OP_NON_2C:
    iVar2 = find_pool_literal(&g_long_literal_table,rec->ea1->disp,(label_ref *)0x0);
    goto joined_r0x004180be;
  case OP_NON_2E:
    iVar2 = find_pool_literal(&g_long_literal_table,
                              (-(uint)((rec->flg & 3U) == 3) & 0x200001) - 0x180001,(label_ref *)0x0
                             );
joined_r0x004180be:
    if (iVar2 == 0) {
LAB_004180c0:
      literal_bytes = 4;
    }
  }
  op = rec->op;
  if ((((op == OP_RTS) || (op == OP_RTE)) || (op == OP_BRA)) ||
     (((op == OP_JUMP || (op == OP_JMP)) || ((op == OP_EXIT || (op == OP_RETURN)))))) {
    if ((g_request->flags_13d & 8) == 0) {
      if (g_request->pool_flag_14b != '\0') {
        literal_bytes = literal_bytes + PEPK(ADD_E, 0xe);
      }
    }
    else {
      literal_bytes = literal_bytes + PEPK(ADD_3C, 0x3c);
    }
    if ((g_pool_carried_has_word == '\x01') || (iVar2 = PEPK(LIM_L, 0x3fc), g_pool_segment_has_word == '\x01')) {
      iVar2 = PEPK(LIM_W, 0x1fe);
    }
    PEPLOG("B", -1);
    if ((iVar2 - PEPK(MARGIN, 0x30) <
         (int)(g_pool_code_bytes + _g_pool_pending_literal_bytes + local_4 + literal_bytes + PEPK(CARRY, 1) * (int)(g_pool_carried_code_bytes + _g_pool_carried_literal_bytes)) - PEPADJ()) ||
       (g_pool_flush_pending == 1)) {
      local_9 = true;
      PEPLOG("D", 1);
      PEPFLUSH();
      _g_pool_carried_literal_bytes = _g_pool_pending_literal_bytes + literal_bytes;
      pool_bytes = _g_pool_carried_literal_bytes & 0xffff;
      g_pool_carried_code_bytes = g_pool_code_bytes + local_4;
      if ((g_word_literal_table.head == (literal_entry *)0x0) && (g_pool_segment_has_word != '\x01')
         ) {
        g_pool_carried_has_word = '\0';
      }
      else {
        g_pool_carried_has_word = '\x01';
      }
      g_pool_flush_pending = 0;
    }
    else {
      local_9 = false;
      PEPLOG("D", 0);
      PEPKEEP();
      _g_pool_carried_literal_bytes =
           _g_pool_carried_literal_bytes + _g_pool_pending_literal_bytes + literal_bytes;
      pool_bytes = _g_pool_carried_literal_bytes & 0xffff;
      g_pool_carried_code_bytes = g_pool_carried_code_bytes + g_pool_code_bytes + local_4;
      if ((g_word_literal_table.head != (literal_entry *)0x0) || (g_pool_segment_has_word == '\x01')
         ) {
        g_pool_carried_has_word = '\x01';
      }
    }
    attr_bits = write_file_bytes(lit_out,&local_9,1);
    if (attr_bits == 0xffffffff) {
      report_compiler_message(0,0,0xce7,(char *)0x0);
    }
    clear_pool_literal_table(&g_word_literal_table);
    literal_bytes = 0;
    clear_pool_literal_table(&g_long_literal_table);
    clear_pool_literal_table(&g_frame_offset_literal_table);
    local_4 = 0;
    g_pool_code_bytes = 0;
    _g_pool_pending_literal_bytes = 0;
    g_pool_segment_has_word = '\0';
  }
  else {
    sVar1 = (short)_g_pool_pending_literal_bytes;
    if ((g_word_literal_table.head == (literal_entry *)0x0) && (g_pool_segment_has_word != '\x01'))
    {
      if (PEPK(FORCE_L, 0x3cc) < (int)(g_pool_code_bytes + _g_pool_pending_literal_bytes + local_4 + literal_bytes)) {
        pool_bytes = _g_pool_pending_literal_bytes & 0xffff;
        _g_pool_carried_literal_bytes = _g_pool_pending_literal_bytes;
        if (((g_request->flags_13d & 8) == 0) || (sVar1 == 0)) {
          if ((g_request->pool_flag_14b != '\0') && (sVar1 != 0)) {
            pool_bytes = (uint)(ushort)(sVar1 + 0xe);
          }
        }
        else {
          pool_bytes = (uint)(ushort)(sVar1 + 0x3c);
        }
        local_9 = true;
        PEPLOG("F", 1);
        PEPRESET();
        g_pool_carried_has_word = '\0';
        g_pool_carried_code_bytes = g_pool_code_bytes + 4;
        if ((short)pool_bytes == 0) {
          g_pool_flush_pending = 1;
        }
        else {
          attr_bits = write_file_bytes(lit_out,&local_9,1);
          if (attr_bits == 0xffffffff) {
            report_compiler_message(0,0,0xce7,(char *)0x0);
          }
          g_pool_flush_pending = 0;
        }
        clear_pool_literal_table(&g_word_literal_table);
        clear_pool_literal_table(&g_long_literal_table);
        clear_pool_literal_table(&g_frame_offset_literal_table);
        g_pool_code_bytes = 0;
        _g_pool_pending_literal_bytes = 0;
        if (rec->op == OP_NON_10) {
          g_pool_carried_code_bytes = 0x400;
          local_4 = 0;
        }
      }
    }
    else if (PEPK(FORCE_W, 0x1ce) < (int)(g_pool_code_bytes + _g_pool_pending_literal_bytes + local_4 + literal_bytes)) {
      pool_bytes = _g_pool_pending_literal_bytes & 0xffff;
      _g_pool_carried_literal_bytes = _g_pool_pending_literal_bytes;
      if (((g_request->flags_13d & 8) == 0) || (sVar1 == 0)) {
        if ((g_request->pool_flag_14b != '\0') && (sVar1 != 0)) {
          pool_bytes = (uint)(ushort)(sVar1 + 0xe);
        }
      }
      else {
        pool_bytes = (uint)(ushort)(sVar1 + 0x3c);
      }
      g_pool_carried_code_bytes = g_pool_code_bytes + 4;
      local_9 = true;
      PEPLOG("F", 2);
      PEPRESET();
      g_pool_carried_has_word = '\x01';
      if ((short)pool_bytes == 0) {
        g_pool_flush_pending = 1;
      }
      else {
        attr_bits = write_file_bytes(lit_out,&local_9,1);
        if (attr_bits == 0xffffffff) {
          report_compiler_message(0,0,0xce7,(char *)0x0);
        }
        g_pool_flush_pending = 0;
      }
      clear_pool_literal_table(&g_word_literal_table);
      clear_pool_literal_table(&g_long_literal_table);
      clear_pool_literal_table(&g_frame_offset_literal_table);
      g_pool_code_bytes = 0;
      _g_pool_pending_literal_bytes = 0;
      g_pool_segment_has_word = '\0';
      if (rec->op == OP_NON_10) {
        g_pool_carried_code_bytes = 0x400;
        local_4 = 0;
      }
    }
  }
  switch(rec->op) {
  case OP_ENTER:
    literal_bytes = 0;
    if (((g_aux_record_table[g_current_aux_index].flags & 0x4000) != 0) &&
       (stack_kind = g_aux_record_table[g_current_aux_index].flags & 0x1800, stack_kind != 0)) {
      if (stack_kind == 0x800) {
        attr_bits = g_aux_record_table[g_current_aux_index].stack_value;
        if (((int)attr_bits < -0x80) || (0x7f < (int)attr_bits)) {
          if (((int)attr_bits < -0x8000) || (0x7fff < (int)attr_bits)) {
            iVar2 = find_pool_literal(&g_long_literal_table,attr_bits,(label_ref *)0x0);
            if (iVar2 == 0) {
              literal_bytes = 4;
              add_pool_literal(&g_long_literal_table,attr_bits,(label_ref *)0x0);
            }
          }
          else {
            iVar2 = find_pool_literal(&g_word_literal_table,attr_bits,(label_ref *)0x0);
            if (iVar2 == 0) {
              literal_bytes = 2;
              add_pool_literal(&g_word_literal_table,attr_bits,(label_ref *)0x0);
            }
          }
        }
      }
      else {
        lref = alloc_zeroed(8);
        lref->labno1 = (short)g_aux_record_table[g_current_aux_index].stack_value;
        lref->labno2 = 0;
        attr_bits = get_symbol_attr_low_bits(lref->labno1);
        if ((attr_bits != 1) &&
           ((attr_bits = get_symbol_attr_low_bits(lref->labno1), attr_bits == 0 ||
            (((byte)(g_aux_record_table[g_current_aux_index].flags >> 8) & 0x18) != 0x10)))) {
          iVar2 = get_symbol_attr_bit5_or_forced(lref->labno1);
          if (iVar2 == 0) {
            iVar2 = find_pool_literal(&g_long_literal_table,0,lref);
            if (iVar2 == 0) {
              literal_bytes = 4;
              table = &g_long_literal_table;
LAB_00418645:
              add_pool_literal(table,0,lref);
            }
          }
          else {
            iVar2 = find_pool_literal(&g_word_literal_table,0,lref);
            if (iVar2 == 0) {
              literal_bytes = 2;
              table = &g_word_literal_table;
              goto LAB_00418645;
            }
          }
        }
        pool_free(lref,8);
      }
    }
    iVar2 = g_aux_record_table[g_current_aux_index].frame_size;
    if ((iVar2 < -0x7f) || (0x80 < iVar2)) {
      if ((0x8000 < iVar2) || (iVar2 < -0x7fff)) {
        attr_bits = -iVar2;
        iVar2 = find_pool_literal(&g_long_literal_table,attr_bits,(label_ref *)0x0);
        goto joined_r0x00418a4e;
      }
      attr_bits = -iVar2;
      iVar2 = find_pool_literal(&g_word_literal_table,attr_bits,(label_ref *)0x0);
      if (iVar2 != 0) break;
      literal_bytes = literal_bytes + 2;
      table = &g_word_literal_table;
      goto LAB_00418a5b;
    }
    break;
  case OP_CALL:
  case OP_JUMPT:
  case OP_JUMPF:
  case OP_MOVA_FC:
    lref = alloc_zeroed(8);
    sVar1 = rec->ea1->labels->labno1;
    lref->labno1 = sVar1;
    if (g_request->pic == 0) {
      iVar2 = get_symbol_attr_bit5_or_forced(sVar1);
      if (iVar2 == 0) {
        iVar2 = find_pool_literal(&g_long_literal_table,0,lref);
        if (iVar2 == 0) {
          literal_bytes = 4;
          add_pool_literal(&g_long_literal_table,0,lref);
        }
      }
      else {
        iVar2 = find_pool_literal(&g_word_literal_table,0,lref);
        if (iVar2 == 0) {
          literal_bytes = 2;
          add_pool_literal(&g_word_literal_table,0,lref);
        }
      }
    }
    else {
      lref->labno2 = -g_literal_label_serial;
      g_literal_label_serial = g_literal_label_serial + 1;
      iVar2 = find_pool_literal(&g_long_literal_table,(rec->op == OP_MOVA_FC) - 1 & 0xfffffffc,lref)
      ;
      if (iVar2 == 0) {
        literal_bytes = 4;
      }
      else {
        report_compiler_message(0,0,0x12f3,(char *)0x0);
      }
    }
    pool_free(lref,8);
    break;
  case OP_MOV_LOC:
    if ((rec->misc & 0x80U) == 0) {
      labels_ea = rec->ea1;
    }
    else {
      labels_ea = rec->ea2;
    }
    iVar2 = frame_offset_to_sp_displacement(labels_ea->disp,rec->sptravel);
    if ((0x7f < iVar2) || (iVar2 < -0x80)) {
      use_ea2 = rec->misc & 0x80;
      if (use_ea2 == 0) {
        labels_ea = rec->ea1;
      }
      else {
        labels_ea = rec->ea2;
      }
      if (use_ea2 == 0) {
        disp_ea = rec->ea1;
      }
      else {
        disp_ea = rec->ea2;
      }
      found_frame = find_pool_literal(&g_frame_offset_literal_table,disp_ea->disp,labels_ea->labels)
      ;
      if (found_frame == 0) {
        if ((0x7fff < iVar2) || (literal_bytes = 2, iVar2 < -0x8000)) {
          literal_bytes = 4;
        }
        if ((iVar2 < 0x8002) && (-0x8001 < iVar2)) {
          g_pool_segment_has_word = '\x01';
        }
        if ((rec->misc & 0x80U) == 0) {
          local_8 = rec->ea1;
        }
        else {
          local_8 = rec->ea2;
        }
      }
    }
    break;
  case OP_MOVA_LC:
    iVar2 = frame_offset_to_sp_displacement(rec->ea1->disp,rec->sptravel);
    if (((0x7f < iVar2) || (iVar2 < -0x80)) &&
       (found_frame = find_pool_literal(&g_frame_offset_literal_table,rec->ea1->disp,
                                        rec->ea1->labels), found_frame == 0)) {
      if ((0x7fff < iVar2) || (literal_bytes = 2, iVar2 < -0x8000)) {
        literal_bytes = 4;
      }
      if ((iVar2 < 0x8002) && (-0x8001 < iVar2)) {
        g_pool_segment_has_word = '\x01';
      }
      local_8 = rec->ea1;
    }
    break;
  case OP_MOVA_PC:
  case OP_MOVI:
    if (rec->op == OP_MOVI) {
      lref = rec->ea1->labels;
      if ((((lref == (label_ref *)0x0) && (iVar2 = rec->ea1->disp, -0x81 < iVar2)) && (iVar2 < 0x80)
          ) || (iVar2 = get_marked_symbol_kind(lref), iVar2 == 1)) break;
    }
    if (((rec->op == OP_MOVI) && (rec->ea1->labels == (label_ref *)0x0)) &&
       ((attr_bits = rec->ea1->disp, -0x8001 < (int)attr_bits && ((int)attr_bits < 0x8000)))) {
      iVar2 = find_pool_literal(&g_word_literal_table,attr_bits,(label_ref *)0x0);
      if (iVar2 == 0) {
        literal_bytes = 2;
        local_8 = rec->ea1;
      }
    }
    else {
      iVar2 = is_word_symbol_literal(rec->ea1->disp,rec->ea1->labels);
      if ((iVar2 == 0) && (iVar2 = get_marked_symbol_kind(rec->ea1->labels), iVar2 == 0)) {
        iVar2 = find_pool_literal(&g_long_literal_table,rec->ea1->disp,rec->ea1->labels);
        if (iVar2 == 0) {
          literal_bytes = 4;
          local_8 = rec->ea1;
        }
      }
      else {
        iVar2 = find_pool_literal(&g_word_literal_table,rec->ea1->disp,rec->ea1->labels);
        if (iVar2 == 0) {
          literal_bytes = 2;
          local_8 = rec->ea1;
        }
      }
    }
    break;
  case OP_NON_2C:
    iVar2 = find_pool_literal(&g_long_literal_table,rec->ea1->disp,(label_ref *)0x0);
    if (iVar2 == 0) {
      literal_bytes = 4;
      local_8 = rec->ea1;
    }
    break;
  case OP_NON_2E:
    attr_bits = (-(uint)((rec->flg & 3U) == 3) & 0x200001) - 0x180001;
    iVar2 = find_pool_literal(&g_long_literal_table,attr_bits,(label_ref *)0x0);
joined_r0x00418a4e:
    if (iVar2 == 0) {
      literal_bytes = literal_bytes + 4;
      table = &g_long_literal_table;
LAB_00418a5b:
      add_pool_literal(table,attr_bits,(label_ref *)0x0);
    }
  }
  if (local_8 != (ea *)0x0) {
    if ((rec->op == OP_MOV_LOC) || (rec->op == OP_MOVA_LC)) {
      add_pool_literal(&g_frame_offset_literal_table,local_8->disp,local_8->labels);
    }
    else if (literal_bytes == 2) {
      add_pool_literal(&g_word_literal_table,local_8->disp,local_8->labels);
    }
    else {
      add_pool_literal(&g_long_literal_table,local_8->disp,local_8->labels);
    }
  }
LAB_00418c0c:
  PEPTRACK();
  _g_pool_pending_literal_bytes = _g_pool_pending_literal_bytes + literal_bytes;
  g_pool_code_bytes = g_pool_code_bytes + local_4;
  if ((short)pool_bytes != 0) {
    return pool_bytes + 2;
  }
  return local_4 & 0xffff0000;
#undef local_9
#undef local_8
#undef local_4
}



