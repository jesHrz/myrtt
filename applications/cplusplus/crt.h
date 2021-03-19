#ifndef CRT_H_
#define CRT_H_

#include <inttypes.h>
#include <stdlib.h>

void *operator new(size_t size);
void *operator new[](size_t size);

void operator delete(void * ptr);
void operator delete[](void *ptr);

#endif