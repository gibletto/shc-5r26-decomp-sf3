/* multiplies of narrow values by constants, and array indexing through MACL */
struct rec { short a, b, c; char d, e; int f; short g; };
extern struct rec recs[40];
extern short wide[100];
extern char narrow[100];

int scale(short s, char c, unsigned char u)
{
    return s * 100 + c * 300 + u * 1000;
}

int field_sum(int i, int j)
{
    return recs[i].a + recs[j].f + recs[i + j].g;
}

void fill(short *dst, int n)
{
    int i;
    for (i = 0; i < n; i++)
        dst[i] = wide[i] * 37 + narrow[i] * 21;
}

int mac_pair(int a, int b, int c, int d)
{
    int x = a * b;
    int y = c * d;
    return x - y + recs[a].b;
}
