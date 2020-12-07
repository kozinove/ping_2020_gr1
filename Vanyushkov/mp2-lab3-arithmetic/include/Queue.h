#pragma once
#include "ICollection.h"
template <class T>
class Queue : public ICollection<T>
{
    T* mem;
    int N;
    int first, last;

    int next(int ind) { return (ind + 1) % N; }
public:
    Queue(int _N = 100) : N(_N)
    {
        mem = new T[N];
        first = 0;
        last = N - 1;
    }
    Queue<T>& operator= (const Queue& p)
    {
        N = p.N;
        mem = new T[N];
        first = p.first;
        last = p.last;
        for (int i = last; i != first; i = next(i))
            mem[i] = p.mem[i];
        if (!isEmpty())
            mem[first] = p.mem[first];
        return *this;
    }
    Queue(const Queue<T>& p)
    {
        *this = p;
    }
    void push(T v)
    {
        if (isFull()) throw "isFull";
        last = next(last);
        mem[last] = v;
    }
    T pop()
    {
        if (isEmpty()) throw "isEmpty";
        T v = mem[first];
        first = next(first);
        return v;
    }
    bool isEmpty() { return next(last) == first; }
    bool isFull() { return next(next(last)) == first; }
};

