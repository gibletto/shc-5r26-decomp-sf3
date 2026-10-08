/* a counted loop whose every use of the counter becomes a stepped address: with an int counter the rule drops
   the counter and compares one address with the end of the table (Release 26 keeps the counter); with a short
   counter, and where only an integer multiple of the counter is stepped (a member array reached through a
   pointer), the counter stays with and without the rule */
typedef struct { char status; char state; char pad[62]; } task;
typedef struct { char pad[36]; short ix[8]; } work;
extern task tasks[8];
extern char flags[8];
void sleep_tick(void)
{
    unsigned long i;
    for (i = 0; i < 8; i++) {
        if (tasks[i].status == 1) {
            tasks[i].state--;
            if (tasks[i].state == 0) {
                tasks[i].status = 2;
            }
        }
    }
}
void clear_flags(void)
{
    short i;
    for (i = 0; i < 8; i++) {
        flags[i] = 0;
    }
}
void clear_ix(work *wk)
{
    long i;
    for (i = 0; i < 8; i++) {
        wk->ix[i] = -1;
    }
}
