/* rows filled from index 1: the pointers that step through t and k start at base + 16. In fill_rows an unused
   initialized local is a dead store, removed after the loop is reduced, which runs the expression passes again over
   the starts once the counter's 1 has been folded in: Release 26 then reorders 16 + base to base + 16 (mov r5,r1 /
   add #16,r1); the arcade keeps the literal first (mov #16,r1 / add r5,r1), as Release 26 already does in
   fill_rows2, which has no dead store */
typedef struct { unsigned short a, b, c, d; long e, f; } ROW;

void fill_rows(ROW *t, unsigned long *k, short n)
{
    long unused = 0;
    short i;
    for (i = 1; i <= n; i++) {
        t[i].a = (unsigned short)k[i * 4];
        t[i].e = 0;
        t[i].f = 0;
    }
}

void fill_rows2(ROW *t, unsigned long *k, short n)
{
    short i;
    for (i = 1; i <= n; i++) {
        t[i].a = (unsigned short)k[i * 4];
        t[i].e = 0;
        t[i].f = 0;
    }
}
