/* a structure copied in a loop that counts down: the pointers step after the copy (add #-4 behind the moves),
   not one element ahead before the loop and down before each copy as an auto-decrement of the destination */
typedef struct { short pos_x; short pos_y; } POS;
typedef struct { char pad[84]; short x; short y; } OBJ;

void push_pos(OBJ *wk, POS *buf)
{
    short i;
    for (i = 16; i > 0; i--) {
        buf[i] = buf[i - 1];
    }
    buf->pos_x = wk->x;
    buf->pos_y = wk->y;
}
