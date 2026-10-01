/* a product read after one other instruction: an index scaled by a record size, the record array's address
   loaded between the multiply and the read */
typedef struct { char pad[8]; short id; char pad2[0x5a]; short pos; char pad3[0x3b0]; } WK;
extern WK wk_tbl[2];

int near_side(WK *wk)
{
    short id = wk->id ^ 1;
    short d = wk->pos - wk_tbl[id].pos;
    if (d < 0)
        d = -d;
    return d < 88;
}
