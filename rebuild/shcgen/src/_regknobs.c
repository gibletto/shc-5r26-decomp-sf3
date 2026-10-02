/* shcgen's settings (environment variables, read once): the rules GEN_TST_R0 and GEN_MUL_L (unset = the arcade
   rule, 0 = Release 26) and the register-choice diagnostics (unset = off). */
#include <stdlib.h>
#include <stdio.h>
#include "decls.h"

static int regknob_get_d(const char *name, int *cache, int dflt)
{
  if (*cache < 0) {
    const char *p = getenv(name);
    *cache = (p && *p) ? atoi(p) : dflt;
  }
  return *cache;
}

static int regknob_get(const char *name, int *cache) { return regknob_get_d(name, cache, 0); }

/* GEN_TST_R0=1 (unset): a condition value (a value only tested, `if (x)`, `x && y`) takes its register in
   assign_condition_value_registers scanning r0, r1, r2, r3 upward, as the arcade's compiler does. Release 26 scans
   r3 downward there, so the tested value lands in r3/r2 and later choices in the block shift through the
   last-chosen tie-break. */
int shcgen_knob_tst_r0(void)
{
  static int v = -1;
  return regknob_get_d("GEN_TST_R0", &v, 1);
}

/* GEN_REG_TB_IDX / GEN_REG_ASC_IDX: comma lists of choose_general_register calls (counted from 1 per compile, as
   SHCGEN_REGTRACE numbers them) that keep the last-chosen register as it was / scan in the other direction. */
static int regknob_listed(const char *name, int *loaded, int *n, int *list, int ix)
{
  int i;
  if (!*loaded) {
    const char *p = getenv(name);
    *loaded = 1;
    while (p && *p && *n < 64) {
      list[(*n)++] = atoi(p);
      while (*p && *p != ',') p++;
      if (*p == ',') p++;
    }
  }
  for (i = 0; i < *n; i++) {
    if (list[i] == ix) return 1;
  }
  return 0;
}

int shcgen_knob_call_listed(int ix)
{
  static int loaded = 0, n = 0;
  static int list[64];
  return regknob_listed("GEN_REG_TB_IDX", &loaded, &n, list, ix);
}

int shcgen_knob_call_asc(int ix)
{
  static int loaded = 0, n = 0;
  static int list[64];
  return regknob_listed("GEN_REG_ASC_IDX", &loaded, &n, list, ix);
}

/* GEN_MUL_L=<bits>: mul_fits_16bit_multiply turns an int multiply of a narrow value by a 16-bit constant (not
   2^n, 2^n +- 1 or two set bits: is_16bit_multiplier_constant) into MULS.W/MULU.W; a set bit answers "no" for that
   operand's test (1 the first, 2 the second), so the multiply stays MUL.L. Unset = 3 */
int shcgen_knob_mul_l(void)
{
  static int v = -1;
  return regknob_get_d("GEN_MUL_L", &v, 3);
}

/* SHCGEN_REGTRACE=<file>: a line per choose_general_register call (call number, return address, the node where
   the caller gives it, preferred/excluded masks, scan direction, last-chosen state, the r0-r3 records, the
   candidate classes, the pick) and "FN <name>" per function. SHCGEN_REGTRACE_DUMP=1 adds the node and descriptor
   bytes. The hooks (tools/shcgen-fixes.py) are in the chooser, the condition-value path and the per-function loop.
   Stock data is read by address (SD()), so the trace does not depend on names. */
static int rt_site;
static char *rt_node;
static int rt_callix, rt_f93c, rt_f93e;
static unsigned rt_ret;

static FILE *regtrace_file(void)
{
  static int loaded = 0;
  static FILE *f = 0;
  if (!loaded) {
    char *p = getenv("SHCGEN_REGTRACE");
    loaded = 1;
    if (p && *p) f = fopen(p, "a");
  }
  return f;
}

/* the function about to be compiled: its .reg record (the stage's function table entry name) */
char *gen_function_name;   /* the function being generated (GEN_REMAP_LOG) */

void regtrace_function(char *rec)
{
  FILE *f = regtrace_file();
  int ix = (int)*(short *)(rec + 2) + 0xb6;
  char *name;
  if (ix < 0) ix = -ix;
  name = *(char **)(*(char **)SD(0x0045f9b0) + ix * 0x30 + 8);
  gen_function_name = name;
  if (!f) return;
  fprintf(f, "FN %s\n", name ? name : "?");
  fflush(f);
}

/* the next chooser call is for this node (site 372: the condition value) */
void regtrace_site(int site, char *node)
{
  rt_site = site;
  rt_node = node;
}

/* at the chooser's entry: count the call, keep the caller and the last-chosen state; GEN_REG_ASC_IDX flips the
   scan direction of the listed calls */
char regtrace_chooser_enter(char ascending, unsigned ret)
{
  rt_ret = ret;
  rt_callix++;
  rt_f93c = *(unsigned char *)SD(0x0045f93c);
  rt_f93e = *(unsigned short *)SD(0x0045f93e);
  if (shcgen_knob_call_asc(rt_callix)) ascending = (ascending == 1) ? 0 : 1;
  return ascending;
}

/* at the chooser's exit: GEN_REG_TB_IDX keeps the last-chosen register of the listed calls as it was; the trace
   line */
void regtrace_chooser_exit(unsigned short p1, unsigned short p2, char p3, short *slots, int chosen)
{
  FILE *f;
  int r;
  if (shcgen_knob_call_listed(rt_callix)) *(unsigned char *)SD(0x0045f93c) = (unsigned char)rt_f93c;
  f = regtrace_file();
  if (f) {
    unsigned short excl = (unsigned short)((*(unsigned short *)SD(0x0045f9fa) & 0xfff0)
                                           | (unsigned short)*(char *)SD(0x0045f9a0));
    fprintf(f, "CH ix=%d site=%d node=%c/%02x ra=%08x p1=%04x p2=%04x p3=%d excl=%04x f93c=%d f93e=%04x f9a8=%d |",
            rt_callix, rt_site, rt_node ? rt_node[0] : '-', rt_node ? (unsigned char)rt_node[5] : 0, rt_ret, p1, p2, p3,
            excl, rt_f93c, rt_f93e, *(int *)SD(0x0045f9a8) != 0);
    for (r = 0; r < 4; r++) {
      int *rec = (int *)(SD(0x0045ff00) + r * 0x18);
      fprintf(f, " r%d:%x/%x/%x", r, rec[0], ((unsigned char *)rec)[9], rec[3]);
    }
    fprintf(f, " | cls");
    for (r = 0; r < 7; r++) fprintf(f, " %d", slots[r]);
    fprintf(f, " -> %d", chosen);
    if (rt_node && getenv("SHCGEN_REGTRACE_DUMP")) {
      unsigned char *d = *(unsigned char **)(rt_node + 0x28);
      fprintf(f, " N=");
      for (r = 0; r < 0x2c; r++) fprintf(f, "%02x", (unsigned char)rt_node[r]);
      if (d) {
        fprintf(f, " D=");
        for (r = 0; r < 0x80; r++) fprintf(f, "%02x", d[r]);
      }
    }
    fprintf(f, "\n");
    fflush(f);
  }
  rt_site = 0;
  rt_node = 0;
}
