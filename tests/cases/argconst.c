/* the same constants passed to several calls */
extern void put(int, int, int);
extern void sound(int);
extern int color;

void draw_frame(int x, int y)
{
    put(x, y, 0x7fff);
    put(x + 8, y, 0x7fff);
    put(x, y + 8, 0x7fff);
    put(x + 8, y + 8, 0x7fff);
    sound(0x123);
}

void effects(int n)
{
    int i;
    for (i = 0; i < n; i++) {
        put(i, 0x40, 0x1234);
        if (i & 1)
            sound(0x1234);
    }
    color = 0x1234;
}

struct actor { char state, shown, visible, sub; short timer; };
extern void anim_init(struct actor *, int, int, int, int);

void actor_start(struct actor *a, int id)
{
    switch (a->state) {
    case 0:
        a->state++;
        a->shown = 1;
        a->visible = 0;
        anim_init(a, 0, id, a->sub + 1, 0);
        break;
    case 1:
        if (--a->timer == 0)
            a->state = 0;
        break;
    }
}
