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
    TQueue(int _N = 10);
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
    int prior(string c);
    TQueue<Lexems*>* separat(string _s);
    TQueue<Lexems*>* revPolNot(TQueue<Lexems*>* q);
    TQueue<Lexems*>* separatFull(string _s);
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
    if ((c != '+') && (c != '-') && (c != '(') && (c != ')') &&(c!=' ')&& (c != '*'))
        throw -1;
    return false;
}
inline int Lexems::prior(string c)
{
    if (c == " ")
        return -1;
    if (c == "(" || c == ")")
        return 0;
    if( c == "*" || c == "/")
    return 1;
    else /*(c=='-'||c=='+')*/
        return 2;

    
}
TQueue<Lexems*>* Lexems::separat(string _s)
{
    string str;
    TQueue<Lexems*>* q = new TQueue<Lexems*>;
    State st = q0;
    for (int i = 0;i < _s.length();i++)
    {
        char c = _s[i];
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
                {
                    str += c;
                }
                if (!ifNumb(c))
                {
                    int val_ = atoi(str.c_str()); 
                    q->push(new Lexems(str, value, val_));
                    st = q0;
                    if (!ifNumb(c)) {
                        str = c;
                        q->push(new Lexems(str, op, -1));

                    }
                }
            }
        }
    }
    return q;
}

inline TQueue<Lexems*>* Lexems::revPolNot(TQueue<Lexems*>* l)
{
    string str;
    TQueue<Lexems*>* q = new TQueue<Lexems*>;
    TStruct<Lexems*>* stack = new TStack<Lexems*>;
    Lexems tmp;
    bool f = true;
    while (!l->isEmpty())
    {
        tmp = *(l->pop());
        if (tmp.getType() == value) {
            int val_ = atoi(tmp.getS().c_str());
            q->push(new Lexems(tmp.getS(), value, val_));
        }
        else {
            /*if (tmp.prior(tmp.getS()) == 2) {
                while (!stack->isEmpty() && f == true)
                {
                    Lexems* ltmp = stack->pop();
                    if (prior(ltmp->getS()) <= 2)
                        q->push(ltmp);
                    else {
                        stack->push(ltmp);
                        f = false;
                    }
                }*/

                stack->push(new Lexems(tmp.getS(), op, -1));
            }

        }
    
    
    while (!stack->isEmpty()) {   
        tmp = *(stack->pop());
        if (tmp.getS() == ")") {
            tmp = *(stack->pop());
            while (tmp.getS() != "(") {
                q->push(new Lexems(tmp.getS(), op, -1));
                tmp = *(stack->pop());
            }
        }
        if (!stack->isEmpty()) 
            if(tmp.getS() == "(")
                tmp = *(stack->pop());
                    
        q->push(new Lexems(tmp.getS(), op, -1));

    }
   
    
    
    while (!stack->isEmpty())
        cout << *(stack->pop()) << " ";
    cout << endl;
    while (!q->isEmpty())
        cout << *(q->pop()) << " ";
    



    
    
    
    return q;
}

inline TQueue<Lexems*>* Lexems::separatFull(string _s)
{



    return NULL;
}



//TQueue<Lexems*>* Lexems::separat(string _s)
//{
//    _s += " ";
//    string str;
//    TQueue<Lexems*>* q = new TQueue<Lexems*>;
//    State st = q0;
//    for (int i = 0;i < _s.length();i++)
//    {
//        char c = _s[i];
//        if (st == q0)
//        {
//            if ((c >= '0') && (c <= '9'))
//            {
//
//                st = q1;
//                str = c;
//            }
//
//            if ((c == '+') || (c == '-') || (c == '(') || (c == ')'))
//            {
//                str = c;
//                q->push(new Lexems(str, op, -1));
//            }
//        }
//        else
//        {
//            if (st == q1) {
//                if ((c >= '0') && (c <= '9'))
//                {
//                    str += c;
//                    st = q1;
//                }
//                if ((c == '+') || (c == '-') || (c == ' ') || (c == '(') || (c == ')'))
//                {
//                    int val_ = atoi(str.c_str());
//                    q->push(new Lexems(str, value, val_));
//                    st = q0;
//                    if ((c == '+') || (c == '-') || (c == '(') || (c == ')')) {
//                        str = c;
//                        q->push(new Lexems(str, op, -1));
//                    }
//                }
//            }
//        }
//    }
//    return q;
//}
#endif
