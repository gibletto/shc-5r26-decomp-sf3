/* several returns of the same value */
struct obj { short x, y; char kind, flag; short life; };
extern int collide(struct obj *, struct obj *);

int check(struct obj *a, struct obj *b)
{
    if (a->kind == 0)
        return 0;
    if (a->flag & 0x80)
        return 0;
    if (b->life <= 0)
        return 1;
    if (collide(a, b))
        return 1;
    if (a->x < b->x)
        return 2;
    return 0;
}

int sign_class(int v)
{
    if (v < -100)
        return -1;
    if (v > 100)
        return 1;
    if (v == 0)
        return 0;
    return v < 0 ? -1 : 1;
}
