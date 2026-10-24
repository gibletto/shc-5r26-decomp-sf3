/* Terminal return scheduling controls. */
typedef struct {
    unsigned char prefix[36];
    short routine[8];
    unsigned char body[760];
} SlotBase;
typedef struct {
    SlotBase w;
    unsigned char gap[6];
    short player;
    short selected;
    short priority;
    unsigned char tail[44];
} SlotWork;
extern short ready[2];
extern signed char choices[2];
extern void observer(SlotWork* work);

int disjoint(SlotWork* work) {
    if (ready[work->player] == 0) {
        return 0;
    }
    if (choices[work->player] == work->selected) {
        work->w.routine[0] = 4;
    } else {
        work->w.routine[0]++;
    }
    return 1;
}

int literal_negative(SlotWork* work) {
    if (ready[work->player] == 0) {
        return 0;
    }
    if (choices[work->player] == work->selected) {
        work->w.routine[0] = 4;
    } else {
        work->w.routine[0]++;
    }
    return -7;
}

int literal_positive(SlotWork* work) {
    if (ready[work->player] == 0) {
        return 0;
    }
    if (choices[work->player] == work->selected) {
        work->w.routine[0] = 4;
    } else {
        work->w.routine[0]++;
    }
    return 42;
}

int framed_small(SlotWork* work) {
    volatile int frame[8];
    frame[0] = work->selected;
    if (ready[work->player] == 0) {
        return 0;
    }
    if (choices[work->player] == work->selected) {
        work->w.routine[0] = 4;
    } else {
        work->w.routine[0]++;
    }
    return 1;
}

int framed_large(SlotWork* work) {
    volatile int frame[40];
    frame[0] = work->selected;
    if (ready[work->player] == 0) {
        return 0;
    }
    if (choices[work->player] == work->selected) {
        work->w.routine[0] = 4;
    } else {
        work->w.routine[0]++;
    }
    return 1;
}

int arm_dependency(SlotWork* work) {
    if (ready[work->player] == 0) {
        return 0;
    }
    if (choices[work->player] == work->selected) {
        work->w.routine[0] = *(volatile short*)&work->priority;
    } else {
        work->w.routine[0]++;
    }
    return 1;
}

int arm_call(SlotWork* work) {
    if (ready[work->player] == 0) {
        return 0;
    }
    if (choices[work->player] == work->selected) {
        observer(work);
        work->w.routine[0] = 4;
    } else {
        work->w.routine[0]++;
    }
    return 1;
}

int extra_predecessor(SlotWork* work) {
    if (ready[work->player] == 0) {
        return 0;
    }
    if (ready[work->player] == 2) goto finished;
    if (choices[work->player] == work->selected) {
        work->w.routine[0] = 4;
    } else {
        work->w.routine[0]++;
    }
finished:;
    return 1;
}

