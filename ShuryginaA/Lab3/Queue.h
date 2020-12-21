#ifndef __QUEUE_H__
#define __QUEUE_H__

#include<string>
#include"Structures.h"


using namespace std;

template <class T>
class TQueue : public TStruct<T>
{
    T* mem;
    int N;
    int first;
    int last;
    int next(int ind) { return (ind + 1) % N; };
public:
    TQueue(int _N = 100);
    TQueue(const TQueue& v);
    ~TQueue();
    void push(T v);
    T pop();
    bool isFull();
    bool isEmpty();


};

template<class T>
inline TQueue<T>::TQueue(int _N)
{
    N = _N;
    mem = new T[N];
    first = 0;
    last = N - 1;
}

template<class T>
inline TQueue<T>::TQueue(const TQueue& v)
{
    N = v.N;
    first = v.first;
    last = v.last;
    mem = new T[N];
    for (int i = last;i != first;i = next(i))
        mem[i] = v.mem[i];
    if (!isEmpty())
        mem[first] = v.mem[first];

}

template<class T>
inline TQueue<T>::~TQueue()
{
    delete[] mem;
}

template<class T>
inline void TQueue<T>::push(T v)
{
    if (isFull())
        throw Exception(ExceptionType::queueisFull);
    last = next(last);
    mem[last] = v;
}

template<class T>
inline T TQueue<T>::pop()
{
    if (isEmpty())
        throw Exception(ExceptionType::queueisEmpty);
    T tmp = mem[first];
    first = next(first);
    return tmp;
}

template<class T>
inline bool TQueue<T>::isFull()
{
    return next(next(last)) == first;
}

template<class T>
inline bool TQueue<T>::isEmpty()
{
    return next(last) == first;
}

#endif


