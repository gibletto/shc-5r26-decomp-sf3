/* PEP_AUTOINC, bit 2: stores through a pointer that is decremented first. In restore the first *--dst is a
   pre-decrement store from shcgen (MOV.L R2,@-R4) either way: dst is used again. After the second one dst is dead,
   so the optimizer leaves *(dst - 4) = x and shcgen emits ADD #-4,R4 and a plain store; Release 26's peephole stage
   folds that pair into a second MOV.L R1,@-R4, with the rule it stays (comm_gets in Street Fighter III). before is
   the same pair written with an index. clear's pointer lives round the loop, so its store is @-R4 either way. */
typedef struct {
    char pad[0x84];
    unsigned long *saved;
    char pad2[0x40];
    unsigned long count;
} work;

int restore(work *w)
{
    unsigned long *src = w->saved;
    unsigned long *dst = &w->count;
    *--dst = *--src;
    *--dst = *--src;
    return 1;
}

void before(unsigned long *p, unsigned long v)
{
    p[-1] = v;
}

void clear(unsigned long *p, int n)
{
    while (n--)
        *--p = 0;
}
