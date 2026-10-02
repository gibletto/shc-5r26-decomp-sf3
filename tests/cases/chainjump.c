/* GEN_CHAIN_JUMP: the constant 1, stored by three cases of a switch, is kept in a register from the switch head.
   r4-r7 are taken, so it goes to r13. With the rule the compare chain's jumps no longer count r1 as used at the
   switch, so at the end of the function the constant moves to r1 and r13 is not saved. */
typedef struct { int pad[3]; struct work *target; } work;
struct work { short pad[0x2c]; short vital; };
typedef struct { short koc, ix; short pad, pat; } cmd;
extern short limit;
extern int next(work *w, cmd *c, int pat);
int check(work *w, cmd *c)
{
    short v = w->target->vital;
    short hit = 0;
    int cut = (limit * c->ix) / 100;
    switch (c->koc) {
    case 1:
        if (v > cut) hit = 1;
        break;
    case 2:
        if (v < cut) hit = 1;
        break;
    default:
        if (v == cut) hit = 1;
        break;
    }
    if (hit)
        return next(w, c, c->pat);
    return 1;
}
