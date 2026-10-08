/* loops over an array: a member of a struct reached through a pointer (the rule adds p + offset to i * 2 on
   each pass; Release 26 steps a pointer) and a static array (a stepping pointer with and without the rule) */
typedef struct { char pad[0x100]; short ix[8]; } work;
extern short table[8];
void clear_member(work *wk)
{
    long i;
    for (i = 0; i < 8; i++) {
        wk->ix[i] = -1;
    }
}
int find_member(work *wk, short v)
{
    short i;
    short r = 0;
    for (i = 2; i < 8; i++) {
        if (wk->ix[i] == v) {
            r = 1;
        }
    }
    return r;
}
void clear_static(void)
{
    short i;
    for (i = 0; i < 8; i++) {
        table[i] = 0;
    }
}
