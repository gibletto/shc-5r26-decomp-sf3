/* MDL_LOOP_INV: with -speed Release 26 turns every loop whose trip count it does not know into a guarded do-loop
   (the test is copied in front of the loop). The rule keeps the jump to the test at the bottom unless the test
   compares two locals or constants and the loop holds no other loop:
     sum    counter against a global: the test stays at the bottom, entered by a jump
     length the test is not a comparison: the same
     copy   counter against a parameter: inverted, with or without the rule
     grid   an outer loop is never inverted, whatever its test */
extern int limit;
extern int table[];
int sum(void)
{
    int i, s = 0;
    for (i = 0; i < limit; i++)
        s += table[i];
    return s;
}
int length(const char *p)
{
    int n = 0;
    while (*p++)
        n++;
    return n;
}
void copy(int *d, int n)
{
    int i;
    for (i = 0; i < n; i++)
        d[i] = table[i];
}
int grid(int w, int h)
{
    int x, y, s = 0;
    for (y = 0; y < h; y++)
        for (x = 0; x < w; x++)
            s += table[y * 16 + x];
    return s;
}
