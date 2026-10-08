/* every path ends in a tail call: an if/else of two calls in front of a switch arm's break (the epilogue stays
   behind the last jump), the same with the two calls sharing their ending, and a switch whose arms each end in
   one call (no epilogue is left) */
struct obj { char be, disp; short pad[17]; short rno; short kind; short x, y; struct obj *master; };
extern int pick(struct obj *, int);
extern void start(struct obj *, int, int);
extern void put(struct obj *);
extern void put_back(struct obj *);
extern void drop(struct obj *);
extern void run(struct obj *);

void show(struct obj *o)
{
    switch (o->rno) {
    case 0:
        o->rno++;
        o->disp = 1;
        start(o, 0, o->kind);
        break;
    case 1:
        run(o);
        if (o->x) {
            put_back(o);
        } else {
            put(o);
        }
        break;
    default:
        drop(o);
        put(o);
        break;
    }
}

void win(struct obj *o)
{
    short w;
    switch (o->rno) {
    case 0:
        o->rno++;
        if (o->x >= o->y) {
            w = pick(o, 3);
            start(o, 9, w + 36);
        } else {
            w = pick(o, 3);
            start(o, 9, w + 32);
        }
        break;
    default:
        run(o);
        break;
    }
}

void plain(struct obj *o)
{
    switch (o->rno) {
    case 0:
        o->rno++;
        o->disp = 1;
        start(o, 0, o->kind);
        break;
    case 1:
        run(o);
        put(o);
        break;
    default:
        drop(o);
        put(o);
        break;
    }
}
