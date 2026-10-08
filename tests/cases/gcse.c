/* a pointer loaded in two switch cases, and in both arms of an if after a use in the condition */
typedef struct { char pad[0x60]; short free; short deff; } BGW;
extern BGW *bgw_ptr;
extern char *step_ptr;
extern void on(int);
extern void down(int, int);

void bg_step(void)
{
    switch (*step_ptr) {
    case 0:
        *step_ptr += 1;
        on(1);
        bgw_ptr->deff = 19;
        break;
    case 1:
        bgw_ptr->free -= 1;
        if (bgw_ptr->free <= 0)
            *step_ptr += 1;
        break;
    case 2:
        bgw_ptr->deff -= 1;
        if (bgw_ptr->deff >= 0)
            down(1, 1);
        else
            *step_ptr += 1;
        break;
    }
    on(0);
}

void bg_blink(void)
{
    bgw_ptr->free++;
    if (bgw_ptr->free & 1)
        bgw_ptr->deff = 32;
    else
        bgw_ptr->deff = 0;
    on(2);
}

/* a row's address shared by a test and an argument, then used again after each call */
extern char rank_in[2][4];
extern void name_in(int, int);

void name_in_all(id)
short id;
{
    if (rank_in[id][0] >= 0)
        name_in(id, rank_in[id][0]);
    if (rank_in[id][1] >= 0)
        name_in(id, rank_in[id][1] + 5);
    if (rank_in[id][2] >= 0)
        name_in(id, rank_in[id][2] + 10);
}
