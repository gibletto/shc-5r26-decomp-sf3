/* GEN_POOL_MOVLOC: without optimization this function's code and literals come to just over the literal pool
   window when each load or store of a local counts 6 bytes, so Release 26 holds the pool back to the end of the
   function, after the closing brace's own return. Counted as 4 they fit, and the pool follows the return statement. */
extern int scale;
int total(int *v, int n)
{
    int sum, lo, hi, i;

    sum = 0;
    lo = v[0];
    hi = v[0];
    for (i = 0; i < n; i++) {
        if (v[i] < lo) lo = v[i]; else sum += lo;
        if (v[i] > hi) hi = v[i]; else sum += hi;
    }
    return sum * scale + lo * 0x12345 + hi;
}
