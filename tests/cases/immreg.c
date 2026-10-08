/* MDL_IMM_REG.
   round_start: zero is kept in r14 for the stores and the call. The unsigned long zero stored to score[0][2] heads
   the class of the block's unsigned long zeros, and the indexes of mark[0], dead[0] and step[0] are members of it.
   Release 26 takes those as immediates of their adds and stores through the address alone (mov.w r14,@r2); with
   the rule they read the register (mov.w r14,@(r0,r14), mov.b r3,@(r0,r14), mov.w r0,@(r0,r4)).
   round_title: there the block's first unsigned long zero is the index of wins[0], an add's immediate, so the
   class is no candidate and both settings store plainly.
   put_rect: the columns start at `x + 0` and the cell codes at `code + row * 16 + 0`. With the rule the zero the
   counters start from is added from its register (add r14,r12).
   item_init: 3 is in a register for the store to item; with the rule the two `& 3` after it read that register
   (and r4,r3 for and #3,r0). */
extern short state, pause, kind;
extern unsigned long score[2][3];
extern short wins[2], mark[2], step[4];
extern signed char dead[8];
extern void gauge_init(void), score_show(void), mark_show(short side), work_clear(void);
extern int put_cell(unsigned short x, unsigned short y, unsigned short attr, unsigned short code);

void round_start(void)
{
    switch (state) {
    case 0:
        state++;
        gauge_init();
        score[0][2] = 0;
        score[1][2] = 0;
        score_show();
        mark[0] = 0;
        mark_show(0);
        mark[1] = 0;
        mark_show(1);
        dead[0] = 1;
        pause = 0;
        step[0] = 0;
        step[1] = 0;
        step[2] = 0;
        step[3] = 0;
        kind = 2;
        work_clear();
        break;
    default:
        score_show();
        break;
    }
}

void round_title(void)
{
    gauge_init();
    wins[0] = 0;
    wins[1] = 0;
    score[0][1] = 0;
    score[0][2] = 0;
    score[1][1] = 0;
    score[1][2] = 0;
    score_show();
    mark[0] = 0;
    mark_show(0);
    mark[1] = 0;
    mark_show(1);
    work_clear();
}

void put_rect(short x, short y, unsigned short w, unsigned short h, short attr, short code)
{
    unsigned short row;
    unsigned short col;

    for (row = 0; row < h; row++) {
        for (col = 0; col < w; col++) {
            put_cell(x + col, y + row, attr, code + row * 16 + col);
        }
    }
}

extern signed char item, now, org, set_a[8], set_b[8];
extern short attr;
extern void item_show(int attr, int value);

void item_init(void)
{
    item = 6;
    now = set_a[7] & 1;
    org = set_b[7] & 1;
    attr = (now != org) ? 8 : 2;
    item_show(attr, now);
    item = 5;
    now = set_a[5];
    org = set_b[5];
    attr = (now != org) ? 8 : 2;
    item_show(attr, now);
    item = 4;
    now = set_a[4] / 16;
    now &= 3;
    org = set_b[4] / 16;
    org &= 3;
    attr = (now != org) ? 8 : 2;
    item_show(attr, now);
    item = 3;
    now = set_a[4] & 3;
    org = set_b[4] & 3;
    attr = (now != org) ? 8 : 2;
    item_show(attr, now);
    item = 2;
    now = set_a[3];
    org = set_b[3];
    attr = (now != org) ? 8 : 2;
    item_show(attr, now);
}
