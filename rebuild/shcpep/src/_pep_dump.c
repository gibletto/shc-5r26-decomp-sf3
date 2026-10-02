/* Diagnostics, off unless set. PEP_DUMP=<file>: the function's blocks and records, one line per record, after
   loading and after each pass of optimize_current_node_list (tools/shcpep-fixes.py puts the calls in).
   XJUMP_LOG=<file> (src/_pep_rules.c): its lines name the function; TAIL and NEXT lines below. */
#if SHC_REBUILD_UPDATED
#include <stdio.h>
#include <stdlib.h>
#include "decls.h"
#include "imports.h"
#include "pep_rules.h"

static const char *opname(int op)
{
  static char buf[8];
  unsigned int p = ((unsigned int *)(g_sd + 0x2c68))[op];
  if (p >= 0x424000u && p < 0x424000u + 0x7f70u) return (const char *)(g_sd + (p - 0x424000u));
  if (p > 0x10000u) return (const char *)p;
  sprintf(buf, "op%02x", op);
  return buf;
}

/* the name of the function being loaded (its FLABEL's symbol), for logs */
const char *pep_current_function(void)
{
  code_node *b = g_current_node_list;
  symbol *y;
  short l;
  if (!b || b->psd[0].op != OP_FLABEL) return "?";
  l = (short)(int)b->psd[0].ea1;
  for (y = l > 0 ? g_symbol_hash[l % 0x3fd] : 0; y; y = y->hash_next)
    if (y->number == l) return y->name ? y->name : "?";
  return "?";
}

void pep_dump(const char *tag, void *list)
{
  static FILE *f; static int opened;
  code_node *b, *n;
  psd *r;
  int i, bn = 0;
  if (!opened) { char *p = getenv("PEP_DUMP"); opened = 1; if (p) f = fopen(p, "a"); }
  if (!f) return;
  fprintf(f, "== %s\n", tag);
  for (b = (code_node *)list; b; b = b->next_block) {
    fprintf(f, "B%d lab=%d tgt=%d fl=%x\n", ++bn, b->labno, b->target_labno, b->flags);
    for (n = b; n; n = n->next) {
      for (i = 0; i < 15; i++) {
        r = &n->psd[i];
        if (r->op == 0) continue;
        fprintf(f, "   %-8s", opname(r->op));
        if (r->op == OP_LABEL || r->op == OP_CLABEL || r->op == OP_DLABEL || r->op == OP_FLABEL) {
          short l = (short)(int)r->ea1;
          symbol *y;
          fprintf(f, " L%d", l);
          for (y = l > 0 ? g_symbol_hash[l % 0x3fd] : 0; y; y = y->hash_next)
            if (y->number == l) { fprintf(f, " refs=%d", y->ref_count); if (r->op == OP_FLABEL && y->name) fprintf(f, " %s", y->name); break; }
        }
        else if (r->op >= OP_ENTER) {
          if (r->ea1 && r->ea1->labels) fprintf(f, " ->%d", r->ea1->labels->labno1);
          if (r->ea1) fprintf(f, " s(%x,%d,%d)", r->ea1->type & 0x1f, r->ea1->base, r->ea1->disp);
          if (r->ea2) fprintf(f, " d(%x,%d,%d)", r->ea2->type & 0x1f, r->ea2->base, r->ea2->disp);
        }
        if (r->misc) fprintf(f, " misc=%x", (unsigned char)r->misc);
        if (r->flg || r->tmp) fprintf(f, " flg=%x tmp=%x", (unsigned char)r->flg, (unsigned char)r->tmp);
        fprintf(f, "\n");
      }
    }
  }
  fflush(f);
}

/* an XJUMP_LOG line: the function, then the text */
static void xjlog(const char *fmt, int a, int b)
{
  char *p = getenv("XJUMP_LOG");
  FILE *f;
  if (!p || !(f = fopen(p, "a"))) return;
  fprintf(f, "%s ", pep_current_function());
  fprintf(f, fmt, a, b);
  fclose(f);
}

/* XJUMP_LOG: the record after a tail call that expand_tail_calls_into_epilogue_jumps expands (TAIL op=..) */
void pep_log_tail(int op) { xjlog("TAIL op=%x\n", op, 0); }

/* XJUMP_LOG: delete_branch_to_next_label deletes the jump of a block cross-jumping made (NEXT op=.. lab=..) */
void pep_log_xj_next(int *blk, int op)
{
  short l = blk ? *(short *)((char *)blk + 4) : 0;
  if (pep_xj_label_was_made(l)) xjlog("NEXT op=%x lab=%d\n", op, l);
}
#endif
