#include "sha256.h"

#include "util.h"

#include "stdlib.h"
#include "string.h"
#include "stdio.h"

extern sha_config * sha;
extern const size_t byte_size;
extern word K256[64];
extern word K512[80];
extern word init_hash[8];

/**
 * Computes sha256 hash
 *
 * @param msg - message
 * @param blocks - number of message blocks
 * @param out - diggest location
 */
void hash(word * msg, size_t blocks, word * out) {
    word hashes[8] = {0};
    word msg_shed[64];
    word t1, t2;
    word w[8];

    memcpy(hashes, init_hash, 8);

    for (int i = 0; i < blocks; i++) {
        memcpy(msg_shed, msg + i * sha->block_wsize, sha->block_bsize);

        for (int t = 16; t < 64; t++) {
            msg_shed[t] = sigma1(msg_shed[t - 2]) + msg_shed[t - 7] 
                + sigma0(msg_shed[t - 15]) + msg_shed[t - 16];
        }

        memcpy(w, hashes, 8 * sizeof(word));

        for (int t = 0; t < 64; t++) {
            t1 = w[7] + sum1(w[4]) + ch(w[4], w[5], w[6]) + K256[t] + msg_shed[t];
            t2 = sum0(w[0]) + maj(w[0], w[1], w[2]);
            w[7] = w[6];
            w[6] = w[5];
            w[5] = w[4];
            w[4] = w[3] + t1;
            w[3] = w[2];
            w[2] = w[1];
            w[1] = w[0];
            w[0] = t1 + t2;
        }

        for (int j = 0; j < 8; j++) {
            hashes[j] = w[j] + hashes[j];
        }
    }

    memcpy(out, hashes, 8 * sizeof(word));
}

/**
 * Padding ensures that the padded message is a miltiple of block bits.
 *
 * Padd message with 00..0 and number that represent size of message in block.
 *
 * @param msg_block - the last message block, that going to be padded;
 * @param size - the whole message size.
 */
void pad_block(word * msg_block, size_t size) {
    size_t block_size = size % sha->block_size;
    size_t pad_zeros = sha->block_size - block_size - 64;
    byte * msg = (byte *) msg_block;

    msg[block_size/byte_size] = 0x80;
    memset(msg + block_size/byte_size + 1, 0, pad_zeros/byte_size);
    *((dword *)(msg + sha->block_wsize - 2)) = size;
}

/**
* Functions ch, maj, sum0, sum1, sigma0, sigma1
* Each function operates on 32-bit word
* Each function performs transformation needed by sha standard
*
* @param x, y, z - 32-bit word
* @result 32-bit word
*/
word ch(word x, word y, word z) {
    return (x & y) ^ (~x & z);
}

word maj(word x, word y, word z) {
    return (x & y) ^ (x & z) ^ (y & z);
}

word sum0(word x) {
    return rotr(x, 2) ^ rotr(x, 13) ^ rotr(x, 22);
}

word sum1(word x) {
    return rotr(x, 6) ^ rotr(x, 11) ^ rotr(x, 25);
}

word sigma0(word x) {
    return rotr(x, 7) ^ rotr(x, 18) ^ shr(x, 3);
}

word sigma1(word x) {
    return rotr(x, 17) ^ rotr(x, 19) ^ shr(x, 10);
}

/**
* Functions ch, maj, sum0, sum1, sigma0, sigma1
* Each function operates on 64-bit word
* Each function performs transformation needed by sha standard
*
* @param x, y, z - 64-bit word
* @result 64-bit word
*/
dword ch64(dword x, dword y, dword z) {
    return (x & y) ^ (~x & z);
}

dword maj64(dword x, dword y, dword z) {
    return (x & y) ^ (x & z) ^ (y & z);
}

dword sum0_64(dword x) {
    return rotr(x, 2) ^ rotr(x, 13) ^ rotr(x, 22);
}

dword sum1_64(dword x) {
    return rotr(x, 6) ^ rotr(x, 11) ^ rotr(x, 25);
}

dword sigma0_64(dword x) {
    return rotr(x, 7) ^ rotr(x, 18) ^ shr(x, 3);
}

dword sigma1_64(dword x) {
    return rotr(x, 17) ^ rotr(x, 19) ^ shr(x, 10);
}

void setup(sha_config * config) {
    sha = config;
}
