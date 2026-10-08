/* GEN_MUL_L, bit 4: v is a short parameter, so its register's upper half is not known to be the sign. The
   multiplies by 21 and 13 stay MUL.L (bits 1 and 2), and with bit 4 the operand's cast stays too: EXTS.W R4,R0,
   MOV #21,R2, MUL.L R2,R0. Without it the cast is dropped as if MULS.W were to follow (MUL.L R0,R4). */
int scale(short v)
{
    switch (v & 0xFFF8) {
    case 0:
        v /= 2;
        break;
    case 8:
        v = (v * 21) / 64;
        break;
    default:
        v = (v * 13) / 32;
        break;
    }
    return v;
}
