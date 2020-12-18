#ifndef __STACK_H__
#define __STACK_H__

#include<string>
using namespace std;

template <class T>
class TStack : public TStruct<T>
{
    T* mem;
    int N;
    int i;
public:
    TStack(int _N = 100);
    TStack(const TStack& v);
    ~TStack();
    void push(T v);
    T pop();
    TStack& operator=(const TStack& v);
    bool isEmpty() { return i < 0; }
    bool isFull() { return i >= N - 1; }
};

template<class T>
inline TStack<T>::TStack(int _N) :N(_N)
{
    i = -1;
    mem = new T[N];
}

template<class T>
inline TStack<T>::TStack(const TStack& v)
{
    N = v.N;
    i = v.i;
    mem = new T[N];
    for (int i = 0;i < N - i;i++)
        mem[i] = v.mem[i];
}

template<class T>
inline TStack<T>::~TStack()
{
    delete[] mem;
}

template<class T>
inline void TStack<T>::push(T v)
{
    if (isFull())
        throw Exception(ExceptionType::stackisFull);
    i++;
    mem[i] = v;
}

template<class T>
inline T TStack<T>::pop()
{
    if (isEmpty())
        throw Exception(ExceptionType::stackisEmpty);
    T tmp = mem[i];
    i--;
    return tmp;
}

template<class T>
TStack<T>& TStack<T>::operator=(const TStack& v)
{
    if (&v == this)
        return *this;
    N = v.N;
    i = v.i;
    delete[] mem;
    mem = new T[N];
    for (int i = 0; i < N - i; i++)
        mem[i] = v.mem[i];

    return *this;
}








#endif
