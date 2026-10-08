/* MDL_MASK_AND.
   Release 26's simplifier turns a mask by 0xff into casts, (T)(unsigned char)x, and shcgen extends (extu.b).
   With the rule the mask stays an and.
   command: `number & 0xFF` indexes a table. Release 26: extu.b r5,r5; the rule: extu.w r5,r0 and and #255,r0.
   pick: `n &= 0xFF` on a variable in a register. Release 26: extu.b r5,r5; the rule: mov.w H'00FF and and r1,r5.
   turn: `t = -t; t &= 0xFF`. Release 26 stores the negated value to the frame and loads its low byte; the rule:
   neg r4,r4, and r3,r4.
   fade: the mask written as a cast is extu.b under both settings.
   pitch: 0xffff is not the rule's: extu.w under both settings.
   store: an and-assignment to memory is and #255,r0 under both settings. */
typedef struct {
    short kind;
    short step;
    signed char mask;
} WORK;
extern signed char timer;
extern long *commands[4];
extern long *current;
extern const short colors[256][3];
extern void set_color(int r, int g, int b);

void command(short side, unsigned short number)
{
    current = (long *)commands[side][number & 0xFF];
}

void pick(WORK *w)
{
    short n = timer & w->mask;

    n &= 0xFF;
    if (w->kind == 240) {
        n >>= 4;
    }
    w->step = n;
}

short turn(short t, short back)
{
    if (back) {
        t = -t;
        t &= 0xFF;
    }
    return t;
}

void fade(unsigned short number)
{
    const short *c = colors[(unsigned char)number];

    set_color(c[0], c[1], c[2]);
}

int pitch(int note, int bend)
{
    note += bend;
    note &= 0xFFFF;
    return note >> 4;
}

void store(WORK *w)
{
    w->step &= 0xFF;
}
