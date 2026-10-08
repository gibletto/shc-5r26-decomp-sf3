/* MDL_IMM_REG, bits 4 and 8.
   side_init: 1 is in r12 for the stores. `(ix + 1) & 1` adds to a parameter: with the rule the add reads the
   register (add r12,r2) as the and does; Release 26 has add #1,r2.
   next_move: 1 is in a register for the calls' last argument and the store. `p->code[p->step] + 1` adds to a value
   that is first loaded from memory, so both settings keep add #1,r7.
   place_rows: `pos_y -= 1` and `pos_y += 1` on a global. With the rule they read the 1 kept in a register for the
   stores and the stack arguments (sub r8,r1, add r8,r3), and count toward keeping it there. */
typedef struct side {
    signed char on, shown, blink, kind, set, pad;
    short work, id;
    struct side *other;
    short flags, col;
} SIDE;
extern SIDE sides[2];
extern signed char kinds[2], sets[8], chars[2];
extern void base_init(SIDE *p), cmd_init(SIDE *p);

void side_init(SIDE *p, short ix)
{
    p->on = 1;
    p->shown = 0;
    p->blink = ix;
    p->id = ix;
    p->work = 1;
    p->kind = kinds[ix];
    p->set = sets[chars[ix]];
    base_init(p);
    p->other = &sides[(ix + 1) & 1];
    cmd_init(p);
    if (ix) {
        p->flags |= 0x10;
    }
}

typedef struct mover {
    short step, kind, cnt, dir;
    short *code;
    signed char rno[4];
} MOVER;
extern void move_init(MOVER *p, short a, short b, short c, short d);
extern short ready(MOVER *p);

void next_move(MOVER *p)
{
    switch (p->rno[0]) {
    case 0:
        p->rno[0] = 1;
        p->cnt = 1;
        move_init(p, 0, 6, p->code[p->step] + 1, 1);
        break;
    case 1:
        if (ready(p)) {
            p->rno[1] = 1;
            move_init(p, 0, 6, p->code[p->kind] + 1, 1);
        }
        break;
    default:
        p->dir = 1;
        move_init(p, 1, 6, p->code[p->dir] + 1, 1);
        break;
    }
}

extern short pos_x, pos_y, rank, base_x, base_y, rank_type;
extern signed char order[4], flash;
extern void put_name(int n), put_face(int n), put_score(int n);
extern void mark_init(int a, int b, int c, int d, int e, int f, int g, int h);

void place_rows(void)
{
    order[0] = 1;
    flash = 1;
    mark_init(24, base_x + 240, base_y + 68, 180, 7, 30, 0, 1);
    mark_init(0, base_x + 248, base_y + 60, 180, 3, 10, 2, 1);
    pos_x = base_x + 312;
    pos_y = base_y + 120;
    rank = rank_type + 10;
    pos_y -= 1;
    put_name(0);
    pos_y += 1;
    pos_x += 16;
    pos_y += 1;
    put_face(0);
    pos_y -= 1;
    pos_x -= 32;
    put_score(0);
}
