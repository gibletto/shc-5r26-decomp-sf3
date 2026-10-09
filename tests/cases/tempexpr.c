/* MDL_TEMP_EXPR: an element address whose index already has a temporary is shared as well. */
extern short table[4];
extern short other[4];
extern short limit[4];
extern void note(int n);

void both_arms(char pl, short v)
{
    other[pl] = v;
    if (limit[pl] < v) {
        table[pl] = v;
        note(pl);
    } else {
        table[pl] = 0;
        note(pl + 1);
    }
    limit[pl]++;
}

short switch_arms(char pl, short k)
{
    switch (k) {
    case 0:
        table[pl] += 1;
        note(pl);
        break;
    case 1:
        table[pl] -= 1;
        note(pl);
        break;
    case 2:
        table[pl] = other[pl];
        break;
    default:
        note(pl);
        break;
    }
    return limit[pl];
}
