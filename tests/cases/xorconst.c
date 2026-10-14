/* the constant of a bit-xor counts toward keeping the constant in a register: 1 is stored twice and xored once
   after a call, so it is kept in a callee-saved register and the xor reads it (xor rN,r0, not xor #1,r0) */
typedef struct { char disp_flag; char kage_flag; char rl_flag; char pad; short char_index; } OBJ;
extern void set_motion(OBJ *wk, short a, short b);

void start_shadow(OBJ *ewk, OBJ *oya)
{
    ewk->disp_flag = 1;
    ewk->kage_flag = 1;
    set_motion(ewk, 0, ewk->char_index);
    ewk->rl_flag = oya->rl_flag ^ 1;
}
