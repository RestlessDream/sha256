#ifndef _TYPES_H_
#define _TYPES_H_

#include "stdlib.h"
#include "stdint.h"

typedef unsigned char byte;
typedef uint32_t word;
typedef uint64_t dword;

typedef struct {
    const size_t message_bsize;
    const size_t block_size;
    const size_t block_bsize;
    const size_t block_wsize;
    const size_t word_bsize;
    const size_t message_diggest_bsize;
} sha_config;

#endif // TYPES_H_
