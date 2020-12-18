#ifndef __LEXEMS_H__
#define __LEXEMS_H__

#include<string>
#include<iostream>
#include"Queue.h"
#include"Stack.h"
#include"Structures.h"


using namespace std;

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
    if ((c != '+') && (c != '-') && (c != '(') && (c != ')') && (c != ' ') && (c != '*') && (c != '/'))
        throw Exception(ExceptionType::unidentified_symbol);
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
        return atoi(ol.getS().c_str()) + atoi(or .getS().c_str());
    else if (mark == "-")
        return atoi(ol.getS().c_str()) - atoi(or .getS().c_str());
    else if (mark == "*")
        return atoi(ol.getS().c_str()) * atoi(or .getS().c_str());
    else if (mark == "/")
        return atoi(ol.getS().c_str()) / atoi(or .getS().c_str());
    else throw Exception(ExceptionType::unidentified_symbol);




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
            if (ifNumb(c))
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
    int count = 0, count1 = 0;
    while (!l->isEmpty())
    {
        if (st == q0) {
            tmp = l->pop();

            if (tmp->getS() == "(")
                stack->push(tmp);

            else if (tmp->getS() == ")")
                st = q1;

            else if (tmp->getType() == value)
            {
                int val_ = atoi(tmp->getS().c_str());
                q->push(new Lexems(tmp->getS(), value, val_));
            }

            else if (prior(*tmp) >= 1)
            {
                if (stack->isEmpty())
                    stack->push(tmp);
                else {

                    Lexems* ltmp = stack->pop();
                    while (!stack->isEmpty() && prior(*ltmp) <= prior(*tmp) && prior(*ltmp) != 0)
                    {
                        q->push(new Lexems(ltmp->getS(), op, -1));
                        ltmp = stack->pop();
                        count++;
                    }
                    if (stack->isEmpty()) {
                        if (prior(*ltmp) <= prior(*tmp))
                            q->push(new Lexems(ltmp->getS(), op, -1));
                        else
                            stack->push(ltmp);
                    }
                    else if (count == 0)
                        stack->push(ltmp);
                    stack->push(tmp);
                    count = 0;
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
            result = res(opR, opL, tmp->getS());
            stack->push(new Lexems(to_string(result), value, result));
        }


    }


    return stack->pop()->getVal();
}
#endif


