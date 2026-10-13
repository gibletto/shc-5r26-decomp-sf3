/* a function that saves one register and MACL, with many value returns: each return is a jump to the exit, and the
   literal pool estimate decides where the pools between them fall */
struct pl {
    char pad[300];
    short f0;
    short f1;
    short f2;
    short f3;
    short f4;
    short f5;
    short f6;
    short f7;
    short f8;
    short f9;
    short f10;
    short f11;
    short f12;
    short f13;
    short f14;
    short f15;
    short f16;
    short f17;
    short f18;
    short f19;
    short f20;
    short f21;
    short f22;
    short f23;
    short f24;
    short f25;
    short f26;
    short f27;
    char tail[600];
};
extern struct pl pl[];

int chk(int ix, int a, int b, int c)
{
    struct pl *p = &pl[ix * a];
    if (p->f0) {
        return 10;
    }
    if (p->f1) {
        return 11;
    }
    if (p->f2) {
        return 12;
    }
    if (p->f3) {
        return 13;
    }
    if (p->f4) {
        return 14;
    }
    if (p->f5) {
        return 15;
    }
    if (p->f6) {
        return 16;
    }
    if (p->f7) {
        return 17;
    }
    if (p->f8) {
        return 18;
    }
    if (p->f9) {
        return 19;
    }
    if (p->f10) {
        return 20;
    }
    if (p->f11) {
        return 21;
    }
    if (p->f12) {
        return 22;
    }
    if (p->f13) {
        return 23;
    }
    if (p->f14) {
        return 24;
    }
    if (p->f15) {
        return 25;
    }
    if (p->f16) {
        return 26;
    }
    if (p->f17) {
        return 27;
    }
    if (p->f18) {
        return 28;
    }
    if (p->f19) {
        return 29;
    }
    if (p->f20) {
        return 30;
    }
    if (p->f21) {
        return 31;
    }
    if (p->f22) {
        return 32;
    }
    if (p->f23) {
        return 33;
    }
    if (p->f24) {
        return 34;
    }
    if (p->f25) {
        return 35;
    }
    if (p->f26) {
        return 36;
    }
    if (p->f27) {
        return 37;
    }
    return ix + a + b + c;
}
