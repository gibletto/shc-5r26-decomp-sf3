/* GEN_OR_INDEX_EARLY: emit independent indexed-OR displacement loads early.

   The original constant-OR hazard prevents a large indexed LHS from taking R0
   before RHS allocation. Once the prepared assignment emits, a register OR may
   in fact leave R0 untouched. Scope the refinement to that assignment writer,
   preserve all original preparation/template expansion, and validate the whole
   emitted footprint before placing its displacement load first.

   GEN_OR_INDEX_EARLY=0 and SHC_REBUILD_UPDATED=0 retain original behavior. No name, source
   line, register assignment other than R0's architectural role, or literal
   value from an individual routine is used. ROM evidence and private tests:
   r30/origin_second/layout_plan07/or_census08 (two for, none against in 10066 C;
   the same two in all 140 available GEN-output bundles).
*/
#if SHC_REBUILD_UPDATED
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <process.h>
#include "decls.h"
#include "imports.h"
#include "orindexrules.h"

#undef g_request
#define g_request (*(request **)(g_sd + 0x1eea0))

static int scope_active;
static int holding;
static int flushing;
static int count;
static psd pending[4];
static gen_node *scope_node;
extern char *gen_function_name;

static int enabled(void)
{
  static int value = -1;
  const char *setting;
  if (value < 0) {
    setting = getenv("GEN_OR_INDEX_EARLY");
    value = !setting || (setting[0] == '1' && setting[1] == 0);
  }
  return value;
}

/* Diagnostic only. A single %d in the path expands to the process ID so a
   parallel build can retain one complete GEN observation stream per unit. */
static FILE *site_log(void)
{
  static int opened;
  static FILE *file;
  const char *setting, *mark;
  char path[1024];
  if (!opened) {
    opened = 1;
    setting = getenv("GEN_OR_INDEX_LOG");
    if (setting && *setting) {
      mark = strstr(setting, "%d");
      if (mark)
        _snprintf(path, sizeof path, "%.*s%d%s", (int)(mark - setting), setting, _getpid(), mark + 2);
      else
        _snprintf(path, sizeof path, "%s", setting);
      path[sizeof path - 1] = 0;
      file = fopen(path, "a");
      if (file) {
        fprintf(file, "RULE\tGEN_OR_INDEX_EARLY\tversion=1\tpid=%d\tmode=%d\tdefault=1\tsource=%s\n",
                _getpid(), enabled(), g_request && g_request->source_name ? g_request->source_name : "?");
        fflush(file);
      }
    }
  }
  return file;
}

static void observe(gen_node *node, const char *decision)
{
  FILE *file = site_log();
  gen_node *left = node->child, *right = left->next;
  if (file) {
    fprintf(file, "SITE\t%s\tline=%d\tdecision=%s\tmode=%d\ttype=%02x\tleft_ea=%d\tbase=%d\tdisp=%d\tresult_ea=%d\tresult=%d\n",
            gen_function_name ? gen_function_name : "?", node->line, decision, enabled(), node->type,
            left->desc ? left->desc->value.type : -1, left->desc ? left->desc->value.base : -1,
            left->desc ? left->desc->value.disp : 0, right->desc ? right->desc->value.type : -1,
            right->desc ? right->desc->value.base : -1);
    fflush(file);
  }
}

#define REJECT(reason) do { observe(node, reason); return 0; } while (0)

static int reg_operand(ea *operand)
{
  return operand && operand->type == 1 && operand->base > 0 &&
         operand->base < 16 && operand->labels == 0;
}

static int constant_operand(ea *operand)
{
  return operand && operand->type == 7 && operand->labels == 0;
}

/* A descriptor with no post-handler transfer, saved registers, stack/address
   materialization, condition emission or alternate emitter. */
static int plain_descriptor(gen_node *node)
{
  node_desc *d = node ? node->desc : 0;
  return d && !(node->type & 2) && (node->type & 0xe0) != 0x20 &&
         !(d->flags2 & ~0x42) && !(d->flags7 & ~0x20) &&
         d->dest.type == 0 && !d->target_regs && !d->ftarget_regs &&
         !d->saved_regs && !d->saved_ea && !d->saved_reg_ea &&
         !d->mem_ea && !d->addr_reg_ea && !d->template_labels;
}

/* Quiet operands are already-resolved constants, variables or no-op casts.
   Their original emit_node_code path emits no PSD and cannot change SP/labels. */
static int quiet_value(gen_node *node, int depth)
{
  node_desc *d;
  if (depth > 4 || !plain_descriptor(node))
    return 0;
  d = node->desc;
  if (d->usage != 2 || d->tmpl || d->flags7 ||
      (d->flags3 != 0x80 && d->flags3 != 0x88))
    return 0;
  if (node->op == IL_CONST)
    return !node->child && constant_operand(&d->value);
  if (node->op == IL_ID)
    return !node->child && reg_operand(&d->value);
  if (node->op == IL_CAST && node->child && !node->child->next)
    return quiet_value(node->child, depth + 1) &&
           reg_operand(&d->value) &&
           d->value.base == node->child->desc->value.base;
  return 0;
}

int gen_or_index_begin(gen_node *node)
{
  gen_node *left, *right, *address, *operand, *base, *constant, *rhs_value, *rhs_constant;
  node_desc *desc;
  FILE *log = site_log();
  if ((!enabled() && !log) || scope_active || !node || node->op != IL_ASSIGN)
    return 0;
  desc = node->desc;
  left = node->child;
  right = left ? left->next : 0;
  if (!left || !right || right->next || left->op != IL_ASTER || right->op != IL_B_OR)
    return 0;
  if (g_request->cpu != 1 || (node->type & 0xf8) != 8 || !plain_descriptor(node))
    REJECT("reject_assignment");
  if (!desc || desc->usage != 0 || (desc->flags2 & 0x80) ||
      !(desc->flags7 & 0x20) ||
      !plain_descriptor(left) || !plain_descriptor(right) ||
      !reg_operand(&right->desc->value))
    REJECT("reject_children");
  /* Fixed stock template forms prove that only a pure load+OR and a pure
     displacement-load+store can be constructed. No call, label or stack entry. */
  if (desc->tmpl != (tmpl_header *)(g_sd + 0x15f50) || desc->flags3 ||
      right->desc->tmpl != (tmpl_header *)(g_sd + 0xfe90) ||
      right->desc->flags3 || right->desc->flags2 || right->desc->usage != 2 ||
      right->desc->regs_2c[0] != right->desc->value.base || desc->regs_34[0] != 0)
    REJECT("reject_templates");
  if (left->desc->usage != 3 || left->desc->value.type != 8 ||
      left->desc->value.base <= 0 || left->desc->value.base >= 16 ||
      left->desc->value.disp < 31 || left->desc->value.labels ||
      left->desc->tmpl || left->desc->flags3 != 0x88)
    REJECT("reject_address");
  address = left->child;
  if (!address || address->op != IL_ADD || !address->child ||
      !plain_descriptor(address) || address->desc->usage != 2 ||
      address->desc->tmpl || address->desc->flags3 != 0x88)
    REJECT("reject_address_tree");
  operand = address->child;
  if (operand->op != IL_CONST)
    operand = operand->next;
  if (!operand || operand->op != IL_CONST)
    REJECT("reject_offset_node");
  constant = operand;
  base = operand == address->child ? operand->next : address->child;
  if (!base || !address->child->next || address->child->next->next ||
      !quiet_value(base, 0) || !quiet_value(constant, 0) ||
      !reg_operand(&base->desc->value) ||
      base->desc->value.base != left->desc->value.base ||
      constant->desc->value.disp != left->desc->value.disp)
    REJECT("reject_address_inputs");
  operand = right->child;
  if (!operand)
    REJECT("reject_rhs_empty");
  if (operand->op != IL_CONST)
    operand = operand->next;
  if (!operand || operand->op != IL_CONST || operand->val < 0 || operand->val >= 256)
    REJECT("reject_rhs_constant");
  rhs_constant = operand;
  rhs_value = right->child;
  /* The counted template loads operand2 then ORs operand1 into its slot. */
  if (!rhs_value || rhs_value == rhs_constant || rhs_value->next != rhs_constant ||
      rhs_constant->next || !quiet_value(rhs_value, 0) || !quiet_value(rhs_constant, 0) ||
      !reg_operand(&rhs_value->desc->value) ||
      rhs_constant->desc->value.disp != rhs_constant->val)
    REJECT("reject_rhs_inputs");
  observe(node, enabled() ? "armed" : "eligible_off");
  if (!enabled())
    return 0;
  scope_node = node;
  scope_active = holding = 1;
  count = 0;
  return 1;
}

/* emit_psd_record normally consumes both EAs. A held record owns them until
   this call to the original writer, and is never copied or freed elsewhere. */
static void flush(int rotate)
{
  int i;
  static const int early[4] = {2, 0, 1, 3};
  flushing = 1;
  for (i = 0; i < count; ++i)
    emit_psd_record(&pending[rotate ? early[i] : i], 0);
  count = 0;
  flushing = 0;
}

static int pure_record(psd *record)
{
  if (!record || record->misc || record->sptravel != pending[0].sptravel)
    return 0;
  if (record->op == OP_MOVI)
    return record->flg == 2 && constant_operand(record->ea1) && record->ea2 &&
           record->ea2->type == 1 && record->ea2->base >= 0 &&
           record->ea2->base < 16 && !record->ea2->labels;
  if (record->op == OP_OR)
    return record->flg == 2 && reg_operand(record->ea1) && reg_operand(record->ea2);
  if (record->op == OP_MOV)
    return record->flg == 1 && reg_operand(record->ea1) && record->ea2 &&
           record->ea2->type == 9 && record->ea2->base > 0 &&
           record->ea2->base < 16 && record->ea2->index == 0 &&
           !record->ea2->labels;
  return 0;
}

int gen_or_index_hold(psd *record, int pool_size)
{
  if (!scope_active || !holding || flushing)
    return 0;
  if (count == 0)
    pending[0] = *record;
  if (pool_size || count == 4 || !pure_record(record) ||
      record->expno != pending[0].expno || record->filno != pending[0].filno ||
      record->linno != pending[0].linno) {
    holding = 0;
    flush(0);
    return 0;
  }
  pending[count++] = *record;
  return 1;
}

void gen_or_index_end(int owner)
{
  psd *c, *o, *d, *s;
  int rotate = 0;
  if (!owner)
    return;
  if (holding && count == 4) {
    c = &pending[0]; o = &pending[1]; d = &pending[2]; s = &pending[3];
    if (c->op == OP_MOVI && o->op == OP_OR && d->op == OP_MOVI && s->op == OP_MOV &&
        c->ea1->disp >= 0 && c->ea1->disp < 256 && d->ea1->disp >= 31 &&
        d->ea2->base == 0 && c->ea2->base == o->ea2->base &&
        o->ea2->base == s->ea1->base)
      rotate = 1;
  }
  observe(scope_node, rotate ? "rotate" : "fallback");
  if (rotate && site_log()) {
    fprintf(site_log(), "FOOTPRINT\t%s\tline=%d\tconstant=%d\tdisplacement=%d\tsource=%d\tresult=%d\tbase=%d\texpression=%d\tfile=%d\n",
            gen_function_name ? gen_function_name : "?", scope_node->line,
            c->ea1->disp, d->ea1->disp, o->ea1->base, o->ea2->base,
            s->ea2->base, c->expno, c->filno);
    fflush(site_log());
  }
  holding = 0;
  flush(rotate);
  scope_active = 0;
}
#endif
