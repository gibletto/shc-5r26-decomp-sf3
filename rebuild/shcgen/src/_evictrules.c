/* GEN_EVICT_ORDER (only with SHC_REBUILD_UPDATED=1): the order of the two steps that make room for a new register
   content record.

   The stage remembers what r0..r3 hold (at most two records for the four registers). Before it records a new
   content for a register, Release 26 first drops that register's own old record (invalidate_register_contents) and
   then calls evict_oldest_register_content, which counts the records left and drops the older one when there are
   two. So the register's own old record never counts, and one other record always survives.

   With the two steps the other way round the register's own old record still counts: when it holds one and one
   other register holds one, the count is two and the older of the two goes (the higher register when both were
   recorded in the same statement). If that is the other register's, only the new record is left afterwards. This
   happens when the address of an array is loaded: the register is recorded as holding the constant and then, in
   the same statement, as holding the variable. The arcade's code is the second order's for a variable record: after
   an array's address is loaded, the register that held an older address or constant counts as free again.

   In Street Fighter III 3rd Strike the state arises 136 times, always as a variable record over the register's own
   constant record of the same statement, and the two orders differ in 110 of them. One routine is known where the
   arcade keeps the other register's record (set_tenguiwa); the record state and the expression around it are the
   same there as in routines that agree (Setup_Comp_Bonus, grade_set_round_result), so no narrower condition is
   known.

   GEN_EVICT_ORDER=<bits> (unset: 1; 0 = Release 26): 1 = record_variable_in_register evicts before it invalidates,
   2 = record_constant_in_register does (in the game the state never arises for a constant record).
   GEN_EVICT_LOG=<file>: two lines for each new record made while the register holds an old one and exactly one
   other register holds one (the only state in which the orders differ). First line: function, V or C, statement
   serial, the register and its old record (value/flags/type/stamp), the other register and its record, the label
   of each constant record (or the other record's lreg), and the variable recorded (symx/type/lreg). Second line
   (variable records): the node's size and its four nearest ancestors as op/type(operand ops[their operand ops]). */
#if SHC_REBUILD_UPDATED
#include <stdio.h>
#include <stdlib.h>
#include "decls.h"
#include "imports.h"
#include "evictrules.h"

extern char *gen_function_name;

int gen_evict_order(void)
{
  static int v = -1;
  if (v < 0) {
    const char *p = getenv("GEN_EVICT_ORDER");
    v = (p && *p) ? atoi(p) : 1;
  }
  return v;
}

static int holds(reg_content *c)
{
  return (c->flags & 0x40) != 0 || c->value != 0;
}

static void log_operands(FILE *f, gen_node *c, int depth)
{
  for (; c; c = c->next) {
    fprintf(f, "%02x", c->op);
    if (c->op == IL_CONST) fprintf(f, "=%d", c->val);
    if (depth > 0 && c->child) {
      fputc('[', f);
      log_operands(f, c->child, depth - 1);
      fputc(']', f);
    }
    if (c->next) fputc(',', f);
  }
}

void gen_evict_log(int kind, reg_content *contents, int reg, gen_node *node)
{
  static int loaded = 0;
  static FILE *f = 0;
  int i, other = -1, n = 0, d;
  reg_content *own, *oth;
  gen_node *p;
  if (!loaded) {
    const char *name = getenv("GEN_EVICT_LOG");
    loaded = 1;
    if (name && *name) f = fopen(name, "a");
  }
  if (!f || reg < 0 || reg > 3) return;
  own = contents + reg;
  if (!holds(own)) return;
  for (i = 0; i < 4; i++) {
    if (i != reg && holds(contents + i)) { other = i; n++; }
  }
  if (n != 1) return;
  oth = contents + other;
  fprintf(f, "EO %s %c ser=%u %s%d:%x/%02x/%02x/%u other r%d:%x/%02x/%02x/%u", gen_function_name ? gen_function_name : "?",
          kind == 1 ? 'V' : 'C', g_stmt_serial, contents == g_fpr_contents ? "fr" : "r", reg, own->value, own->flags,
          own->type, own->stamp, other, oth->value, oth->flags, oth->type, oth->stamp);
  fprintf(f, " ownlab=%d othlab=%d new=%x/%02x/%d",
          (own->flags & 0x40) != 0 && own->u.labels ? own->u.labels->labno1 : -1,
          (oth->flags & 0x40) != 0 ? (oth->u.labels ? oth->u.labels->labno1 : -1) : oth->u.lreg,
          kind == 1 ? (int)node->symx : 0, kind == 1 ? node->type : 0, kind == 1 ? node->lreg : 0);
  fputc(10, f);
  if (kind == 1) {
    fprintf(f, "   shape size=%d", node->val);
    for (d = 0, p = node->parent; d < 4 && p; d++, p = p->parent) {
      fprintf(f, " ^%02x/%02x(", p->op, p->type);
      log_operands(f, p->child, 1);
      fputc(')', f);
    }
    fputc(10, f);
  }
  fflush(f);
}
#endif
