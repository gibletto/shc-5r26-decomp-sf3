/* products read through MACL. Release 26 schedules the sts macl of scale60 above the mul.l it reads */
struct w { int a0; };

void scale60(struct w *wk)
{
    wk->a0 = (wk->a0 * 60) / 100;
}

struct body { char pad[0x84]; int k; int w; };
extern void use(int *);
int energy(struct body *b, short v)
{
    int e[3];
    if (v == 0)
        return 0;
    e[0] = v * v / 2 * b->k;
    e[1] = v * b->w;
    use(e);
    return e[0] + e[1];
}
