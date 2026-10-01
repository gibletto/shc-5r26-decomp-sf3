/* many values live across calls: stack slots near branches and calls */
extern int f1(int), f2(int, int), f3(int, int, int);
extern int g[32];

int busy(int a, int b, int c, int d)
{
    int e = f1(a) + b;
    int h = f2(c, d) - a;
    int i = f3(a, b, c) ^ d;
    int j = f1(e + h);
    int k = f2(i, j) + e;
    if (k > h)
        g[3] = f1(k + i + j + a + b);
    else
        g[4] = f2(e, h + c + d);
    return e + h + i + j + k + a + b + c + d;
}

void spill_loop(int *p, int n, int s)
{
    int a = g[0], b = g[1], c = g[2], d = g[3], e = g[4];
    while (n-- > 0) {
        if (*p > s)
            a += f1(*p);
        else
            b += f2(*p, s);
        c += a; d += b; e += c ^ d;
        p++;
    }
    g[0] = a; g[1] = b; g[2] = c; g[3] = d; g[4] = e;
}
