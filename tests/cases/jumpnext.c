/* a jump that ends up in front of its own label: kept where the code in between went away after loading (an else
   arm shared with a later identical one, an else arm that returns, the compare chain of a switch whose cases are
   all goto), deleted behind "else break;" */
struct obj { short rno, count, frame, limit; char play, req; };
extern struct obj *cur;
extern void print(int, int, int, char *);
extern void step(struct obj *);
extern int ask(struct obj *);
extern char none_msg[], erase_msg[];

void shared(struct obj *o)
{
    switch (o->rno) {
    case 6:
        if (o->count) {
            print(30, 1, 14, erase_msg);
        } else {
            print(30, 1, 6, none_msg);
            break;
        }
        o->req = 1;
        o->frame++;
        break;
    case 7:
        if (o->count) {
            print(30, 1, 14, erase_msg);
        } else {
            print(30, 1, 6, none_msg);
            break;
        }
        o->req = 1;
        o->frame = 1;
        break;
    default:
        o->play = 0;
        break;
    }
    step(o);
}

void returns(struct obj *o)
{
    int n;
    if (o->rno == 3) {
        n = 0;
    } else if (o->count == 3) {
        n = 1;
    } else {
        return;
    }
    if (ask(o) == -1) {
        return;
    }
    o->frame = n;
    o->req = 1;
}

void gotos(struct obj *o)
{
    if (o->rno == 1) {
        if (o->count > 0) {
            goto one;
        }
    }
    switch (ask(o)) {
    case 0:
        goto parry;
    case 1:
        goto guard;
    }
one:
    o->play = 2;
    step(o);
    o->rno = 1;
    return;
parry:
    o->req = 1;
    return;
guard:
    o->req = 2;
}

int breaks(struct obj *o, short *next, int id)
{
    short ix = o->rno;
    while (ix != -1) {
        if (next[ix * 4] != id) {
            ix = next[ix * 4 + 1];
        } else {
            break;
        }
    }
    return ix;
}
