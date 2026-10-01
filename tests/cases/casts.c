/* an array name cast to an integer, and a record's first member passed by address */
extern char table[64];
extern void put(unsigned int, int);

void fill_rows(int n)
{
    int i;
    for (i = 0; i < n; i++)
        put((unsigned int)table + i * 4, i);
    put((unsigned int)table, n);
}

struct head { short x, y; };
struct work { struct head head; int life; char state; };
extern void push(struct head *);
extern int alive(struct head *);

void step(struct work *p)
{
    p->life--;
    if (p->state)
        push(&p->head);
}

void step2(struct work *p, int k)
{
    p->state = k;
    p->life = alive(&p->head) + k;
}
