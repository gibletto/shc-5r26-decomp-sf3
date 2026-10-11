/* Compare-chain selector lifetime, including real long-branch expansion.
   Volatile increments keep the two case bodies at distinct branch distances. */
volatile int sink;
#define STEP sink = sink + 1;
#define TEN STEP STEP STEP STEP STEP STEP STEP STEP STEP STEP
#define HUNDRED TEN TEN TEN TEN TEN TEN TEN TEN TEN TEN
#define THOUSAND HUNDRED HUNDRED HUNDRED HUNDRED HUNDRED HUNDRED HUNDRED HUNDRED HUNDRED HUNDRED

int selector(x) int x; { return x ^ 85; }

int live_selector(x,y) int x,y;
{
    int r;
    switch (x) {
    case 0: r=17; break;
    case 1: r=23; break;
    case 1000: r=31; break;
    case -300: r=41; break;
    default: r=53;
    }
    sink=r;
    return r+x+y;
}

int call_selector(x,y) int x,y;
{
    int k,r;
    switch (k=selector(x)) {
    case 0: r=61; break;
    case 1: r=67; break;
    case 1000: r=71; break;
    default: r=73;
    }
    sink=k;
    return r+k+x+y;
}

int default_only(x,y) int x,y;
{
    int k;
    switch (k=selector(x)) { default: sink=k+y; }
    return k+x+y;
}

int no_default(x,y) int x,y;
{
    switch (x) { case 0: sink=83; break; case 1: sink=89; break; }
    return x+y;
}

int far_selector(x,y) int x,y;
{
    int r;
    switch (x) {
    case 0:
        sink=0;
        THOUSAND HUNDRED HUNDRED HUNDRED HUNDRED TEN TEN TEN TEN TEN
        r=97; break;
    case 1: r=101; break;
    case 1000: r=103; break;
    default: r=107;
    }
    return r+x+y;
}

int mid_selector(x,y) int x,y;
{
    int r;
    switch (x) {
    case 0:
        sink=0;
        TEN TEN TEN TEN TEN TEN TEN TEN
        r=97; break;
    case 1: r=101; break;
    case 1000: r=103; break;
    default: r=107;
    }
    return r+x+y;
}
