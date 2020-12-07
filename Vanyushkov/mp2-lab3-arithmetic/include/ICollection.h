#pragma once
template <class T>
class ICollection
{
public:
    virtual void push(T v) = 0;
    virtual T pop() = 0;
    virtual bool isEmpty() = 0;
    virtual bool isFull() = 0;
};

