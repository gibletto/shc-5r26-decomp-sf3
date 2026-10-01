/* values that are only tested */
struct pl { char flag, mode; short hp; int bits; };
extern struct pl pls[2];
extern void on_hit(int), on_ko(int);

void scan(int i)
{
    struct pl *p = &pls[i];
    if (p->flag)
        on_hit(i);
    if (p->bits & 0x40)
        on_ko(i);
    if (p->hp)
        on_hit(p->mode);
}

int any_set(int *v, int n)
{
    while (n--) {
        if (*v++ & 3)
            return 1;
    }
    return 0;
}
