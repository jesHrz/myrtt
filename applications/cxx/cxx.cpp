// #include <stdio.h>
#include <vector>
#include <iostream>
#include "cxx.h"

A::A()
    : a(0)
{
    std::cout << "A::A()" << std::endl;
}

A::~A()
{
    std::cout << "A::~A()" << std::endl;
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
}

A a;

int main(void)
{
    A *b = new A;
    std::cout << "b=" << b << std::endl;
    a.setA(100);
    a.toString();
    b->setA(150);
    b->toString();

    std::vector<int> v;
    for (int i = 0; i < 10; ++i)    v.push_back(i);
    for (int i = 9; i >= 0; --i)    
        std::cout << v[i] << std::endl; 

    delete b;

    return 0;
}
