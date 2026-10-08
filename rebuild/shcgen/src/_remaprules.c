/* The arcade's rules for the scratch registers of a switch's compare chain, GEN_CHAIN_JUMP, and of a break or a
   continue, GEN_JUMP_TEMP, and the GEN_REMAP_LOG diagnostic (only with SHC_REBUILD_UPDATED=1).

   At the end of a function, remap_register_variables_to_scratch_registers moves a register variable from a
   callee-saved register to the first of r0-r3 whose free ranges (the statements in which code generation left the
   scratch register unused) cover all of the variable's live ranges, so the function need not save that register.

   GEN_CHAIN_JUMP=1 (unset: 1, the arcade rule; 0: Release 26): the jumps of a switch's compare chain
   (emit_switch_compare_chain) do not take r1 out of its free ranges. Release 26 counts r1, the register a
   JUMPT/JUMP would load for a jmp @r1, as used at the switch's statement for every case, although each becomes a bt
   or bra; so a constant or variable that is live from the switch head into its cases never moves to r1 and keeps
   r13 or r14 saved (comm_emhp's 1, which the arcade keeps in r1 with no save of r13).

   GEN_REMAP_LOG=<file> (a diagnostic, off unless set; a %d in the name is replaced by the process id): per function,
   each statement's scratch registers left used ("st") and each serial taken out of their free ranges ("rm"), then
   the free ranges and every lreg's register, flags and live ranges as the pass sees them. */
#include <stdlib.h>
#include <stdio.h>
#include <process.h>
#include "decls.h"

extern char *gen_function_name;

static FILE *remap_log_file(void)
{
    static FILE *f;
    static int opened;
    if (!opened) {
        const char *p = getenv("GEN_REMAP_LOG");
        char path[512];
        opened = 1;
        if (p && *p) {
            _snprintf(path, sizeof path, p, _getpid());
            f = fopen(path, "a");
        }
    }
    return f;
}

void gen_remap_log(void)
{
    static int fn;
    FILE *f = remap_log_file();
    short *lreg;
    int s;
    if (!f)
        return;
    fprintf(f, "F%d %s serial %u\n", ++fn, gen_function_name ? gen_function_name : "?", g_stmt_serial);
    for (s = 0; s < 4; s++) {
        reg_range *r;
        fprintf(f, "  r%d free", s);
        for (r = g_gpr_contents[s].ranges; r; r = r->next)
            fprintf(f, " %u-%u", r->start, r->end);
        fputc('\n', f);
    }
    for (lreg = *(short **)&g_lreg_table; lreg && *lreg != 0; lreg += 0x12) {
        lreg_entry *e = (lreg_entry *)lreg;
        reg_range *r;
        fprintf(f, "  L%d reg%d fl%02x live", e->lreg, e->reg, e->flags);
        for (r = e->ranges; r; r = r->next)
            fprintf(f, " %u-%u", r->start, r->end);
        fputc('\n', f);
    }
    fflush(f);
}

void gen_remap_log_mark(const char *what, unsigned int mask, unsigned int serial)
{
    FILE *f = remap_log_file();
    if (f && (mask & 0xf)) {
        fprintf(f, "    %s mask%x serial%u\n", what, mask & 0xf, serial);
        fflush(f);
    }
}

/* the registers a compare-chain jump adds to the chain's used mask */
unsigned int gen_chain_jump_regs(unsigned int mask)
{
    static int k = -1;
    if (k < 0) {
        const char *v = getenv("GEN_CHAIN_JUMP");
        k = (v && *v) ? atoi(v) : 1;
    }
    return k ? 0 : mask;
}

/* GEN_JUMP_TEMP=<bits> (unset: 3, the arcade rule; 0: Release 26). Every statement that jumps picks a free scratch
   register for the jump (a far jump would be mov.l #label,rN and jmp @rN; the peephole stage makes nearly all of
   them a bra) and takes it out of that register's free ranges at the current statement serial, so
   remap_register_variables_to_scratch_registers cannot move a register variable that is live there to it. A
   break or a continue has no serial of its own: Release 26 charges its register to the statement in front of
   it, which the jump has nothing to do with, and a value that lives through that statement (the copy of a
   stepped pointer in a loop that ends in continue, a counter tested before a break) stays in r8-r14 and is saved.
   The arcade's compiler does not charge it.
     1  continue
     2  break
     4  goto (off: no site in the game decides)
     8  a for loop's jump to its test, 16 a for loop without a test, 64 a while loop's jump to its test (off: these
        are charged to the loop statement itself; no site decides)
    32  the jump over an else (off: charged to the if statement itself; the arcade charges it too) */
unsigned int gen_jump_temp_regs(int bit, unsigned int mask)
{
    static int k = -1;
    if (k < 0) {
        const char *v = getenv("GEN_JUMP_TEMP");
        k = (v && *v) ? atoi(v) : 3;
    }
    return (k & bit) ? 0 : mask;
}
