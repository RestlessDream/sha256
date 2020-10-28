#include "util.h"
#include "static.h"

extern sha_config * sha;
extern size_t byte_size;

/**
 * Roatate word(32-bit value) right (analog c++ >>> operation)
 *
 * @param x - rotated value
 * @param n - the size by which the value is rotated
 * @return result - rotated value
 */
word rotr(word x, size_t n) {
    return (x >> n) | (x << (sha->word_bsize * byte_size - n));
}

/**
 * Shift word(32-bit value) right
 *
 * @param x - shifted value
 * @param n - the size by which the value is shifted
 * @return result - shifted value
 */
word shr(word x, size_t n) {
    return x >> n;
}

/**
 * Roatate word(64-bit value) right (analog c++ >>> operation)
 *
 * @param x - rotated value
 * @param n - the size by which the value is rotated
 * @return result - rotated value
 */
word rotr64(dword x, size_t n) {
    return (x >> n) | (x << (sha->word_bsize * byte_size - n));
}

/**
 * Shift word(64-bit value) right
 *
 * @param x - shifted value
 * @param n - the size by which the value is shifted
 * @return result - shifted value
 */
word shr64(dword x, size_t n) {
    return x >> n;
}
