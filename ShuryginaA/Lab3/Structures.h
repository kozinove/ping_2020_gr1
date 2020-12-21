#ifndef __STRUCTURES_H__
#define __STRUCTURES_H__

#include<string>


using namespace std;


enum class ExceptionType { stackisFull , 
                           queueisFull, 
                           stackisEmpty, 
                           queueisEmpty,
                           unidentified_symbol,
};
struct Exception
{
    ExceptionType error;
    Exception(ExceptionType _error) { error = _error; }
};

template <class T>
class TStruct
{
public:
    virtual void push(T v)=0;
    virtual T pop() = 0;
    virtual bool isEmpty() = 0;
    virtual bool isFull() = 0;

};

#endif
