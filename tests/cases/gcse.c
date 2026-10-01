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
