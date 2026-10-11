typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;

struct byte_values { u8 pad[32]; s8 a; u8 b; };
struct short_values { u8 pad[32]; s16 a; u16 b; };
struct int_values { u8 pad[32]; s32 a; u32 b; };
struct unsigned_byte_values { u8 pad[32]; u8 a; };
struct unsigned_short_values { u8 pad[32]; u16 a; };

s32 narrow_s8_add(struct byte_values *p, s32 x) {
    p->a = p->a + x + 32;
    return p->a;
}
s32 narrow_u8_add(struct unsigned_byte_values *p, s32 x) {
    p->a = p->a + x + 32;
    return p->a;
}
s32 narrow_s16_add(struct short_values *p, s32 x) {
    p->a = p->a + x + 32;
    return p->a;
}
s32 narrow_u16_add(struct unsigned_short_values *p, s32 x) {
    p->a = p->a + x + 32;
    return p->a;
}
s32 narrow_s8_sub(struct byte_values *p, s32 x) {
    p->a = p->a + x - 32;
    return p->a;
}
s32 narrow_s16_sub(struct short_values *p, s32 x) {
    p->a = p->a + x - 32;
    return p->a;
}
s32 narrow_u8_sub(struct unsigned_byte_values *p, s32 x) {
    p->a = p->a + x - 32;
    return p->a;
}
s32 narrow_u16_sub(struct unsigned_short_values *p, s32 x) {
    p->a = p->a + x - 32;
    return p->a;
}
s32 wide_sum(struct int_values *p, s32 x) {
    p->a = p->a + x + 32;
    return p->a;
}
s32 folded_address(struct short_values *p, s32 x) {
    return p[x].a + p[x].b;
}
s32 unequal_constant(struct short_values *p, s32 x) {
    p->a = p->a + x + 31;
    return p->a;
}
s32 changed_base(struct short_values *p, s32 x) {
    p->a = p->a + p->b + x + 32;
    return p->a + p->b;
}
s32 signed_constant(struct short_values *p, s32 x) {
    p->a = p->a + x - 1;
    p->b = p->b + 65535;
    return p->a + p->b;
}
