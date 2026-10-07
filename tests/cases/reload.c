/* GEN_RELOAD: bottom is kept in the frame, and its read in the call is its last reference. Release 26 takes it
   from the register the assignment left it in (EXTS.W R0,R7 next to the store); with the rule the slot is read
   again (MOV.W @(12,R15),R0 and MOV R0,R7), as the other three already are. total is read again after the first
   call, so that read is not its last reference and takes the register either way. */
extern short area[8][2][4];
extern char mode;
extern short page_y;
extern short total;
extern void clear_rect();
extern void show();

void clear_area(short *work)
{
    short left;
    short top;
    short right;
    short bottom;

    left = area[work[37]][mode][0];
    top = page_y + area[work[37]][mode][1];
    right = area[work[37]][mode][2];
    bottom = page_y + area[work[37]][mode][3];
    clear_rect(left, top, right, bottom);
}

void count(short *work)
{
    total = work[0] + work[1];
    show(total);
    show(total);
}
