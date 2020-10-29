#ifndef _SHA_256_H_
#define _SHA_256_H_

#include "static.h"

void hash(word * msg, size_t blocks, word * out);

void pad_block(word * msg_block, size_t size);
word ch(word x, word y, word z);
word maj(word x, word y, word z);
word sum0(word x);
word sum1(word x);
word sigma0(word x);
word sigma1(word x);

void setup(sha_config * config);
dword ch64(dword x, dword y, dword z);
dword maj64(dword x, dword y, dword z);
dword sum0_64(dword x);
dword sum1_64(dword x);
dword sigma0_64(dword x); 
dword sigma1_64(dword x); 
int proof_of_work(word * in, size_t blocks, size_t zeros_count, word * out);
int cmpbits(word v1, word v2, size_t count);

#endif //_SHA_256_H_
