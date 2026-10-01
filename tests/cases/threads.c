/* nested conditions with common tails */
struct st { char r0, r1, r2, r3; short cnt; short lim; };
extern void go(int), stop(void);

void step(struct st *s, int in)
{
    if (s->r0 == 0) {
        if (in & 1) {
            s->r1 = 2;
            go(1);
        } else {
            s->r1 = 2;
            go(1);
        }
    } else if (s->r0 == 1) {
        if (--s->cnt <= 0) {
            s->r0 = 2;
            stop();
        }
    } else {
        if (s->cnt < s->lim) {
            s->cnt++;
            go(0);
        } else {
            s->r0 = 0;
            go(0);
        }
    }
}

int pick(struct st *s, int a, int b)
{
    if (a) {
        if (b)
            goto both;
        s->r2 = 1;
        return 1;
    }
    if (b) {
        s->r3 = 1;
        return 1;
    }
both:
    s->r2 = s->r3 = 1;
    return 2;
}
