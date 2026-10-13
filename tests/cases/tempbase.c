/* two elements of one array in a structure passed to a call: the array's address is a temporary kept in the frame
   (its register is wanted for an argument), and the element read after the reload has its offset added into the
   register that the address was loaded into, in place of a displacement through r0 */
struct work {
    char flag;
    char no[7];
    short index;
    short pad[20];
    short old[8];
    short more[16];
    short x;
};
extern void init();
extern void speed();
extern short limit;
extern char done;

void start(struct work *w)
{
    if (w->old[1] <= limit) {
        w->no[1] = 99;
    }
    switch (w->no[1]) {
    case 0:
        w->no[1] += 1;
        done = 0;
        w->flag = 1;
        init(w, 0, w->old[0], w->index, 0);
        w->old[3] = 10;
        speed(w, w->old[3], w->x, w->old[2], 2, 2);
    case 1:
        w->old[3] -= 1;
        if (w->old[3] < 0) {
            w->no[1] += 1;
            w->x = w->old[2];
            done = 1;
        }
        break;
    default:
        init(w);
        break;
    }
}
