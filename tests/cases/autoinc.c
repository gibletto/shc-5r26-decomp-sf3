/* PEP_AUTOINC: a load through a pointer followed by a separate increment of the pointer. Release 26's peephole
   stage folds the two into mov.l @r5+,r6; with the rule the add stays (fifo_get in Street Fighter III). The
   second function's *p++ is a post-increment from shcgen itself and is the same either way. */
typedef struct { unsigned long *base, *wr, *rd; long count; unsigned long size; } fifo;
unsigned long get(fifo *q)
{
    unsigned long *rd, dat;
    if (q->wr != q->rd) {
        rd = q->rd;
        dat = *rd;
        q->rd = ++rd;
        q->count--;
        if ((unsigned long)rd >= (unsigned long)q->base + q->size)
            q->rd = q->base;
        return dat;
    }
    return 0;
}
extern void put(short v);
void walk(short *p, int n)
{
    while (n--)
        put(*p++);
}
