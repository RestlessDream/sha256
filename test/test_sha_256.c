#include "unity.h"
#include "../src/sha256.h"
#include "../src/util.h"
#include "stdio.h"
#include <string.h>

extern sha_config sha_256;
extern sha_config * sha;
extern size_t state_rows;

void setUp(void) {
    setup(&sha_256);
}

void tearDown(void) {
}

void test_pad_block() {
    byte msg[64] = { 'a', 'b', 'c' };
    byte expected[64] = { 0b01100001, 0b01100010, 0b01100011 };
    memset(expected + 3,  0, 61);
    expected[3] = 0b10000000;
    expected[63] = 24; 

    pad_block(msg, 24);
    printf("%d", sha->block_bsize);

    TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, msg, 64);
}

void test_hash() {
    byte msg[16] = "abc";
    word out[16];
    word expected[16] = { 0xba7816bf, 0x8f01cfea, 0x414140de, 0x5dae2223,
0xb00361a3, 0x96177a9c, 0xb410ff61, 0xf20015ad };
    pad_block(msg, 24);
    hash(msg, 1, out);

    TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, out, 16);
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_hash);
    RUN_TEST(test_pad_block);

    return UNITY_END();
}
