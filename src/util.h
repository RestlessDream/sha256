#ifndef _UTIL_H_
#define _UTIL_H_

#include "types.h"

#include "stdlib.h"

word rotr(word x, size_t n);
word shr(word x, size_t n);
word rotr64(dword x, size_t n);
word shr64(dword x, size_t n);

#endif // UTIL_H_
