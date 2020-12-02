 #ifndef __STRUCTURES_H__
#define __STRUCTURES_H__

#include<string>

using namespace std;


template <class T>
class TStruct
{
public:
    virtual void push(T v)=0;
    virtual T pop() = 0;
    virtual bool isEmpty() = 0;
    virtual bool isFull() = 0;

};
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
    bool isFull() { return i>=N-1; }
};

template<class T>
inline TStack<T>::TStack(int _N):N(_N)
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
    for (int i = 0;i <N-i;i++)
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
        throw "is Full";
    i++;
    mem[i] = v;
}

template<class T>
inline T TStack<T>::pop()
{
    if (isEmpty())
        throw "is Empty";
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
    for (int i = 0; i < N-i; i++)
        mem[i] = v.mem[i];

    return *this;
}

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
    last= v.last;
    mem = new T[N];
    for (int i = last;i!=first;i=next(i))
        mem[i] = v.mem[i];
    if(!isEmpty())
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
        throw "isFull";
    last = next(last);
    mem[last] = v;
}

template<class T>
inline T TQueue<T>::pop()
{
    if (isEmpty())
        throw "isEmpty";
    T tmp = mem[first];
    first = next(first);
    return tmp;
}

template<class T>
inline bool TQueue<T>::isFull()
{
    return next(next(last))==first;
}

template<class T>
inline bool TQueue<T>::isEmpty()
{
    return next(last)==first;
}

enum Type {
    op, value
};
enum State {
    q0, q1
};
class Lexems
{
    string s;
    Type t;
    int val;
public:
    Lexems() {};
    Lexems(string _s, Type _t, int _val);
    Type getType() { return t; }
    int getVal() { return val; }
    string getS() { return s; }
    bool ifNumb(char c);
    int prior(Lexems tmp);
    int res(Lexems or , Lexems ol, string mark);
    TQueue<Lexems*>* separat(string _s);
    TQueue<Lexems*>* revPolNot(TQueue<Lexems*>* q);
    int separatFull(TQueue<Lexems*>* q);
    friend ostream& operator <<(ostream& o, Lexems& l)
    {
        o << "|" << l.s << "," << l.t << "|";
        return o;

    }
};

Lexems::Lexems(string _s, Type _t, int _val)
{
    s = _s;
    t = _t;
    val = _val;

}
inline bool Lexems::ifNumb(char c)
{
    if ((c >= '0') && (c <= '9'))
        return true;
    if ((c != '+') && (c != '-') && (c != '(') && (c != ')') &&(c!=' ')&& (c != '*') && (c != '/'))
        throw -1;
    return false;
}
inline int Lexems::prior(Lexems tmp)
{
    if (tmp.getS() == " ")
        return -1;
    if (tmp.getS() == "(" || tmp.getS() == ")")
        return 0;
    if (tmp.getS() == "*" || tmp.getS() == "/")
        return 1;
    else 
        return 2;

    
}
inline int Lexems::res(Lexems or , Lexems ol, string mark)
{
    if (mark == "+")
        return atoi(ol.getS().c_str())+ atoi(or.getS().c_str());
    if (mark == "-")
        return atoi(ol.getS().c_str()) - atoi(or.getS().c_str());
    if (mark == "*")
        return atoi(ol.getS().c_str()) * atoi(or.getS().c_str());
    if (mark == "/")
        return atoi(ol.getS().c_str()) / atoi(or.getS().c_str());


    
}
TQueue<Lexems*>* Lexems::separat(string _s)
{
    string str;
    char c;
    TQueue<Lexems*>* q = new TQueue<Lexems*>;
    State st = q0;
    for (int i = 0;i < _s.length();i++)
    {
        c = _s[i];
        if (st == q0)
        {   
            str = c;
            if(ifNumb(c))           
                st = q1;

            if (!ifNumb(c))
                q->push(new Lexems(str, op, -1));           
        }
        else
        {
            if (st == q1) {
                if (ifNumb(c))
                    str += c;
                if (!ifNumb(c))
                {
                    int val_ = atoi(str.c_str()); 
                    q->push(new Lexems(str, value, val_));
                    st = q0;
                        str = c;
                        q->push(new Lexems(str, op, -1));
                }
            }
        }
    }
    if (ifNumb(c)) {
        str = c;
        int val_ = atoi(str.c_str());
        q->push(new Lexems(str, value, val_));
    }

    return q;
}

inline TQueue<Lexems*>* Lexems::revPolNot(TQueue<Lexems*>* l)
{
    TQueue<Lexems*>* q = new TQueue<Lexems*>;
    TStruct<Lexems*>* stack = new TStack<Lexems*>;
    Lexems* tmp;
    State st = q0;
    int count = 0;
    while (!l->isEmpty())
    {
        if (st == q0) {
            tmp = l->pop();     
            if (prior(*tmp) == 1 || tmp->getS() == "(") 
                stack->push(tmp);
            else if (tmp->getType() == value)
            {
                int val_ = atoi(tmp->getS().c_str());
                q->push(new Lexems(tmp->getS(), value, val_));
            }
            else if (tmp->getS() == ")")
                st = q1;
            else if (prior(*tmp) == 2)
            {
                if (stack->isEmpty())
                    stack->push(tmp);
                else {
                   
                    Lexems* ltmp = stack->pop();
                    while (!stack->isEmpty() && prior(*ltmp)>= 1)
                    {
                        q->push(new Lexems(ltmp->getS(), op, -1));
                        ltmp = stack->pop();
                        count++;                         
                    }
                    if (prior(*ltmp) >= 1) {
                        q->push(new Lexems(ltmp->getS(), op, -1)); //"3+4*2-4"
                        count++;
                    }
                    if(count==0)
                        stack->push(ltmp);
                    stack->push(tmp);                    
                }
            }
        }
            if (st == q1)
            {
                Lexems* sttmp = stack->pop();

                while (!stack->isEmpty() && sttmp->getS() != "(")
                {
                    q->push(new Lexems(sttmp->getS(), op, -1));
                    sttmp = stack->pop();
                }
                st = q0;
           }    
    }
    
    while (!stack->isEmpty())
        q->push(new Lexems(stack->pop()->getS(), op, -1));   
    return q;
}

inline int Lexems::separatFull(TQueue<Lexems*>* q)
{
    // add exp if queue is empty 
    TStruct<Lexems*>* stack = new TStack<Lexems*>;
    int result;
    Lexems* tmp, opR, opL;

    while (!q->isEmpty())
    {     
        tmp = q->pop();
        if (tmp->getType() == value)
        {
            int val_ = atoi(tmp->getS().c_str());
            stack->push(new Lexems(tmp->getS(), value, val_));
        }
        else {
            opR = *(stack->pop());
            opL = *(stack->pop());
            result=res(opR, opL, tmp->getS());
            stack->push(new Lexems(to_string(result), value, result));
        }


    }


    return stack->pop()->getVal();
}




#endif
