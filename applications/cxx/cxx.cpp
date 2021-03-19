// #include <stdio.h>
#include <vector>
#include <iostream>
#include "cxx.h"

A::A()
    : a(0)
{
    std::cout << "A::A()" << std::endl;
    // printf("A::A()\n");
}

A::~A()
{
    std::cout << "A::~A()" << std::endl;
    // printf("A::~A()\n");
}

void A::setA(int value)
{
    a = value;
}

int A::getA(void)
{
    return a;
}

void A::toString()
{
    std::cout << "A::a = " << a << std::endl;
    // printf("A::a = %d\n", a);
}

A a;

int main(void)
{
    A *b = new A;
    // printf("b=%p\n", b);
    std::cout << "b=" << b << std::endl;
    a.setA(100);
    a.toString();
    b->setA(150);
    b->toString();

    std::vector<int> v;
    for (int i = 0; i < 10; ++i)    v.push_back(i);
    for (int i = 9; i >= 0; --i)    
        std::cout << v[i] << std::endl; 
        // printf("%d\n", v[i]);

    delete b;

    return 0;
}
