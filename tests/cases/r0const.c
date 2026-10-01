/* byte stores and compares that go through r0 around conditional branches */
struct ent { char act, sub, timer, dir; short x, y; };
extern struct ent ents[8];
extern void hit(struct ent *);

void ent_reset(struct ent *e, int full)
{
    e->sub = 1;
    if (full)
        e->timer = 1;
    e->dir = 1;
    if (e->act == 1)
        hit(e);
}

int count_mode(char *p, int n)
{
    int c = 0;
    while (n--) {
        if (*p == 3)
            c++;
        else if (p[1] == 3)
            c += 2;
        p += 2;
    }
    return c;
}

void ent_flags(struct ent *e)
{
    if (e->act == 4)
        e->sub = 4;
    if (e->timer == 4)
        e->dir = 4;
}

struct big { char head[0x270]; short level; short limit; };

int level_step(struct big *p, int d)
{
    if (d > 0) {
        p->level += d;
        if (p->level >= 63) {
            p->level = 63;
            return 1;
        }
    } else {
        p->level += d;
        if (p->level <= 0) {
            p->level = 0;
            return 1;
        }
    }
    return 0;
}
