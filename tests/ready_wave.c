typedef unsigned long u32;

u32 graph(volatile u32 *p, u32 x, u32 y)
{
    u32 a = x + 1, b = y + 3, c = a ^ b;
    p[0] = a;
    p[1] = b;
    a = (c << 2) + p[1];
    b = (p[0] >> 3) ^ a;
    p[2] = c;
    p[3] = a;
    return b + p[2];
}

u32 overlap(u32 *p, u32 *out, u32 x)
{
    out[0] = p[0] + x;
    out[1] = p[1] ^ out[0];
    out[2] = p[2] + out[1];
    return out[2] + p[0];
}

u32 multiply(u32 x, u32 y)
{
    u32 first = x * y;
    u32 second = (x + 3) * (y ^ 7);
    return first + (second << 1) + (x & 255);
}

u32 diamond(u32 condition, u32 a, u32 b)
{
    if (condition) return (a + 3) ^ b;
    return (b + 7) ^ a;
}

u32 callsite(volatile u32 *p, u32 (*callback)(u32), u32 x, u32 y)
{
    u32 a = x + 1;
    u32 b;
    p[0] = y;
    b = callback(a);
    p[1] = b;
    return a ^ b ^ p[0];
}

u32 window32(volatile u32 *p)
{
    u32 sum = p[0];
    sum += p[1]; sum ^= p[2]; sum += p[3]; sum ^= p[4];
    sum += p[5]; sum ^= p[6]; sum += p[7]; sum ^= p[8];
    sum += p[9]; sum ^= p[10]; sum += p[11]; sum ^= p[12];
    sum += p[13]; sum ^= p[14]; sum += p[15]; sum ^= p[16];
    sum += p[17]; sum ^= p[18]; sum += p[19]; sum ^= p[20];
    sum += p[21]; sum ^= p[22]; sum += p[23]; sum ^= p[24];
    sum += p[25]; sum ^= p[26]; sum += p[27]; sum ^= p[28];
    sum += p[29]; sum ^= p[30]; sum += p[31]; sum ^= p[32];
    return sum;
}
