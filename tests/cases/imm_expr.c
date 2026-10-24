typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

s8 left_value, right_value;
volatile s32 result, checksum;

void emit_values(s32 value, s32 a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 g) {
    result = result * 3 + value;
    checksum = checksum * 3 + a + b + c + d + e + f + g;
}

s32 read_left(void) { return left_value; }
s32 read_right(void) { return right_value; }

void difference(void) {
    emit_values(left_value - right_value + 1, 1, 1, 1, 1, 1, 1, 1);
    emit_values(65, 1, 1, 1, 1, 1, 1, 1);
}
void sum(void) {
    emit_values(left_value + right_value + 1, 1, 1, 1, 1, 1, 1, 1);
    emit_values(65, 1, 1, 1, 1, 1, 1, 1);
}
void product(void) {
    emit_values(left_value * right_value + 1, 1, 1, 1, 1, 1, 1, 1);
    emit_values(65, 1, 1, 1, 1, 1, 1, 1);
}
void cast_difference(void) {
    emit_values((s16)(left_value - right_value) + 1, 1, 1, 1, 1, 1, 1, 1);
    emit_values(65, 1, 1, 1, 1, 1, 1, 1);
}
void difference_seven(void) {
    emit_values(left_value - right_value + 7, 7, 7, 7, 7, 7, 7, 7);
    emit_values(65, 7, 7, 7, 7, 7, 7, 7);
}
void difference_negative(void) {
    emit_values(left_value - right_value - 3, -3, -3, -3, -3, -3, -3, -3);
    emit_values(65, -3, -3, -3, -3, -3, -3, -3);
}
void product_sixteen(void) {
    emit_values(left_value * right_value + 16, 16, 16, 16, 16, 16, 16, 16);
    emit_values(65, 16, 16, 16, 16, 16, 16, 16);
}
void plain_global(void) {
    emit_values(left_value + 1, 1, 1, 1, 1, 1, 1, 1);
    emit_values(65, 1, 1, 1, 1, 1, 1, 1);
}
void local_sum(s32 a, s32 b) {
    emit_values(a + b + 1, 1, 1, 1, 1, 1, 1, 1);
    emit_values(65, 1, 1, 1, 1, 1, 1, 1);
}
void indirect_difference(s8* a, s8* b) {
    emit_values(*a - *b + 1, 1, 1, 1, 1, 1, 1, 1);
    emit_values(65, 1, 1, 1, 1, 1, 1, 1);
}
void call_difference(void) {
    emit_values(read_left() - read_right() + 1, 1, 1, 1, 1, 1, 1, 1);
    emit_values(65, 1, 1, 1, 1, 1, 1, 1);
}
void outside_imm8(void) {
    emit_values(left_value - right_value + 128, 128, 128, 128, 128, 128, 128, 128);
    emit_values(65, 128, 128, 128, 128, 128, 128, 128);
}
void zero_offset(void) {
    emit_values(left_value - right_value + 0, 0, 0, 0, 0, 0, 0, 0);
    emit_values(65, 0, 0, 0, 0, 0, 0, 0);
}
