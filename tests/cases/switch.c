/* switch statements: the case tests and the jumps between case blocks */
extern int work[16];
extern void sub(int);

int dispatch(int n, int v)
{
    switch (n) {
    case 0:
        return v + 1;
    case 1:
        work[1] = v;
        break;
    case 2:
        work[2] = v;
    case 3:
        work[3] = v;
        break;
    case 7:
        sub(v);
        return 3;
    }
    return 0;
}

void state_step(char *st)
{
    switch (st[1]) {
    case 0:
        st[2] = 4;
        st[1] = 1;
        break;
    case 1:
        if (--st[2] == 0)
            st[1] = 2;
        break;
    case 2:
        sub(st[3]);
        break;
    default:
        st[1] = 0;
        break;
    }
}

int table_switch(int n)
{
    switch (n) {
    case 0: return work[0];
    case 1: return work[4];
    case 2: return work[2];
    case 3: return work[7];
    case 4: return work[3];
    case 5: return work[9];
    case 6: return work[1];
    case 7: return work[5];
    }
    return -1;
}

/* the example in SF3.md */
int pick(int n, int a, int b)
{
    switch (n) {
    case 0:  return a;
    default: return b;
    }
}

extern void finish(char *);

void only_default(char *p, int i)
{
    switch (p[i]) {
    default:
        finish(p);
        break;
    }
}
