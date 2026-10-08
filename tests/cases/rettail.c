/* returns behind the same store, behind the same call, and behind the same value; two tail calls that share
   their ending; a return inside a switch that is a whole block */
struct obj { char be, disp; short pad[17]; short rno; short kind; short x, y; struct obj *master; };
extern int out_of_range(struct obj *, int);
extern int step(struct obj *, short *, int);
extern void put(struct obj *);
extern struct obj field[];

void move(struct obj *o)
{
    struct obj *m = o->master;
    if (m->be == 0) {
        o->disp = 0;
        o->rno = 3;
        return;
    }
    switch (o->rno) {
    case 0:
        o->rno++;
        put(o);
        return;
    case 1:
        if (out_of_range(o, 96)) {
            o->disp = 0;
            o->rno++;
            return;
        }
        break;
    case 2:
        o->x = field[o->kind].x;
        o->y = field[o->kind].y - 128;
        put(o);
        return;
    default:
        o->rno = 99;
        return;
    }
    o->x = m->x;
    o->y = m->y;
    put(o);
}

int follow(struct obj *o, short *cmd)
{
    if (o->kind == 1) {
        if (o->be != 19 && o->master->x == cmd[1])
            return step(o, cmd, cmd[2]);
    } else {
        o = o->master;
        if (o->kind == 1 && o->master->x == cmd[1])
            return step(o, cmd, cmd[2]);
    }
    return 1;
}

int grade(struct obj *o)
{
    if (o->be == 0)
        return 0;
    if (o->x > 100)
        return 2;
    if (o->y > 100)
        return 2;
    return 0;
}

int pick(struct obj *o, short *cmd)
{
    if (o->be)
        return step(o, cmd, cmd[3]);
    return step(o, cmd, cmd[2]);
}

void turn(struct obj *o)
{
    switch (o->rno) {
    case 0:
        if (o->kind) {
            o->rno++;
            put(o);
            return;
        } else {
            put(o);
            return;
        }
    case 1:
        o->x++;
        break;
    }
    o->y = o->x;
}
