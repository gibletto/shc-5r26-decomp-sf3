#include "decls.h"
#include "imports.h"

// entry: 0040b3e0
// name : record_superscalar_entry_operands
// size : 1432
// sig  : void __cdecl record_superscalar_entry_operands(psd *rec,char classify_only)


int __cdecl record_superscalar_entry_operands(psd *rec,char classify_only)

{
  switch(rec->op) {
  case OP_MOVT:
  case OP_SHAL:
  case OP_SHLL:
  case OP_SHLL2:
  case OP_SHLL8:
  case OP_SHLL16:
  case OP_ROTL:
  case OP_ROTCL:
  case OP_CMP_PZ:
  case OP_CMP_PL:
  case OP_SHAR:
  case OP_SHLR:
  case OP_SHLR2:
  case OP_SHLR8:
  case OP_SHLR16:
  case OP_ROTR:
  case OP_ROTCR:
  case OP_TAS:
  case OP_DT:
  case OP_JMP:
  case OP_JSR:
  case OP_BSRF:
  case OP_BRAF:
  case OP_PREF:
  case OP_FLDI0:
  case OP_FLDI1:
  case OP_FNEG:
  case OP_FABS:
  case OP_FSQRT:
  case OP_FSRRA:
    if (classify_only == '\0') {
      if ((((rec->ea1 != (ea *)0x0) && ((rec->ea1->type & 0x1f) == 8)) && (rec->ea1->disp == 0)) &&
         (rec->ea1->labels == (label_ref *)0x0)) {
        rec->ea1->type = rec->ea1->type & 0xf0 | 2;
      }
      g_superscalar_window[g_pipeline_window_last_index].src_reg = rec->ea1->base;
      g_superscalar_window[g_pipeline_window_last_index].src_kind = rec->ea1->type & 0x1f;
      g_superscalar_window[g_pipeline_window_last_index].dst_reg = REG_R0;
      g_superscalar_window[g_pipeline_window_last_index].dst_kind = '\0';
    }
    else {
      if ((rec->ea1->base < REG_FR0) || (REG_FR15 < rec->ea1->base)) {
        if ((rec->ea1->base < REG_DR0) || (REG_DR14 < rec->ea1->base)) {
          if ((rec->ea1->base < REG_FV0) || (REG_FV12 < rec->ea1->base)) {
            if ((rec->ea1->base < REG_XF0) || (REG_XF15 < rec->ea1->base)) {
              if ((rec->ea1->base < REG_XD0) || (REG_XD14 < rec->ea1->base)) {
                g_operand1_register_class = '\0';
              }
              else {
                g_operand1_register_class = 'P';
              }
            }
            else {
              g_operand1_register_class = '@';
            }
          }
          else {
            g_operand1_register_class = '0';
          }
        }
        else {
          g_operand1_register_class = ' ';
        }
      }
      else {
        g_operand1_register_class = '\x10';
      }
      g_operand2_register_class = '\0';
    }
    break;
  default:
    if (classify_only == '\0') {
      if ((((rec->ea1 != (ea *)0x0) && ((rec->ea1->type & 0x1f) == 8)) && (rec->ea1->disp == 0)) &&
         (rec->ea1->labels == (label_ref *)0x0)) {
        rec->ea1->type = rec->ea1->type & 0xf0 | 2;
      }
      if (((rec->ea2 != (ea *)0x0) && ((rec->ea2->type & 0x1f) == 8)) &&
         ((rec->ea2->disp == 0 && (rec->ea2->labels == (label_ref *)0x0)))) {
        rec->ea2->type = rec->ea2->type & 0xf0 | 2;
      }
      g_superscalar_window[g_pipeline_window_last_index].src_reg = rec->ea1->base;
      g_superscalar_window[g_pipeline_window_last_index].dst_reg = rec->ea2->base;
      g_superscalar_window[g_pipeline_window_last_index].src_kind = rec->ea1->type & 0x1f;
      g_superscalar_window[g_pipeline_window_last_index].dst_kind = rec->ea2->type & 0x1f;
    }
    else {
      if ((rec->ea1->base < REG_FR0) || (REG_FR15 < rec->ea1->base)) {
        if ((rec->ea1->base < REG_DR0) || (REG_DR14 < rec->ea1->base)) {
          if ((rec->ea1->base < REG_FV0) || (REG_FV12 < rec->ea1->base)) {
            if ((rec->ea1->base < REG_XF0) || (REG_XF15 < rec->ea1->base)) {
              if ((rec->ea1->base < REG_XD0) || (REG_XD14 < rec->ea1->base)) {
                g_operand1_register_class = '\0';
              }
              else {
                g_operand1_register_class = 'P';
              }
            }
            else {
              g_operand1_register_class = '@';
            }
          }
          else {
            g_operand1_register_class = '0';
          }
        }
        else {
          g_operand1_register_class = ' ';
        }
      }
      else {
        g_operand1_register_class = '\x10';
      }
      if ((rec->ea2->base < REG_FR0) || (REG_FR15 < rec->ea2->base)) {
        if ((rec->ea2->base < REG_DR0) || (REG_DR14 < rec->ea2->base)) {
          if ((rec->ea2->base < REG_FV0) || (REG_FV12 < rec->ea2->base)) {
            if ((rec->ea2->base < REG_XF0) || (REG_XF15 < rec->ea2->base)) {
              if ((rec->ea2->base < REG_XD0) || (REG_XD14 < rec->ea2->base)) {
                g_operand2_register_class = '\0';
              }
              else {
                g_operand2_register_class = 'P';
              }
            }
            else {
              g_operand2_register_class = '@';
            }
          }
          else {
            g_operand2_register_class = '0';
          }
        }
        else {
          g_operand2_register_class = ' ';
        }
      }
      else {
        g_operand2_register_class = '\x10';
      }
    }
    break;
  case OP_DIV0U:
  case OP_NOP:
  case OP_CLRT:
  case OP_RTE:
  case OP_SETT:
  case OP_BF:
  case OP_BT:
  case OP_BRA:
  case OP_BSR:
  case OP_RTS:
  case OP_BT_S:
  case OP_BF_S:
  case OP_CLRMAC:
  case OP_TRAPA:
  case OP_SLEEP:
  case OP_FRCHG:
    if (classify_only == '\0') {
      g_superscalar_window[g_pipeline_window_last_index].src_reg = REG_R0;
      g_superscalar_window[g_pipeline_window_last_index].src_kind = '\0';
      g_superscalar_window[g_pipeline_window_last_index].dst_reg = REG_R0;
      g_superscalar_window[g_pipeline_window_last_index].dst_kind = '\0';
    }
    else {
      g_operand1_register_class = '\0';
      g_operand2_register_class = '\0';
    }
  }
  return;
}
