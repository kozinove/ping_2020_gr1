#pragma once
#include "ICollection.h"
template <class T>
class Stack : public ICollection<T>
{
    T* mem;
    int N;
    int i;
public:
    Stack(int _N = 100) : N(_N)
    {
        i = -1;
        mem = new T[N];
    }
    void push(T v)
    {
        if (isFull()) throw "isFull";
        i++;
        mem[i] = v;
    }
    T pop()
    {
        if (isEmpty()) throw "isEmpty";
        T v = mem[i];
        i--;
        return v;
    }
    bool isEmpty() { return i < 0; }
    bool isFull() { return i >= N - 1; }
};

