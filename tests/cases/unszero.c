/* the zero of an unsigned compare against a converted value is kept in a register like any other constant use:
   the entry test of the inverted loop, `0 < (unsigned)n`, compares the zero's register itself (cmp/hs r10,r4),
   not a copy of it */
extern int match(const char *a, const char *b, unsigned n);
extern unsigned length(const char *s);

char *find(char *s, const char *sub)
{
    unsigned sublen = length(sub);
    int n = length(s) - sublen + 1;
    unsigned i;
    if (n > 0 && sublen > 0) {
        for (i = 0; i < n; i++) {
            if (match(s + i, sub, sublen) == 0) {
                return s + i;
            }
        }
    }
    return 0;
}

/* unsigned on both sides: the zero stays an immediate, as in Release 26 */
void fill(unsigned char *p, unsigned char c, unsigned n)
{
    unsigned i;
    for (i = 0; i < n; i++) {
        p[i] = c;
    }
}
