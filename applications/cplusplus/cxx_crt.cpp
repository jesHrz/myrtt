#include <stdio.h>
// #include <iostream>
#include <stdlib.h>
#include "crt.h"

void *operator new(size_t size)
{
    return malloc(size);
}

void *operator new[](size_t size)
{
    return malloc(size);
}

void operator delete(void *ptr)
{
    free(ptr);
}

void operator delete[](void *ptr)
{
    return free(ptr);
}

void __cxa_pure_virtual(void)
{
    // std::cout << "Illegal to call a pure virtual function.\n";
    printf("Illegal to call a pure virtual function.\n");
}
