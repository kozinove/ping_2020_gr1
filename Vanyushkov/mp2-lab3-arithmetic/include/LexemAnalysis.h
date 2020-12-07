#pragma once
#include <string>
#include "Queue.h"
#include "Lexem.h"

enum class State { oper, num };

class LexemAnalysis
{
    std::string s, st;
    ICollection<Lexem*>* q;
    State state;

    void queuePush(ICollection<Lexem*>* tmp, Lexem* lexem) // Добавление элемента в очередь
    {
        if (tmp->isFull()) throw "Error: Example is long";
        tmp->push(lexem);
    }
    bool number(const char c) { return c >= '0' && c <= '9' || c == '.'; }
    bool letter(const char c) 
    { 
        char ct = std::tolower(c);
        return ct == 'a' || ct == 'c' || ct == 's' || ct == 't' || ct == 'd' || ct == 'm' || ct == 'p'; 
    }
    bool operation(const char c) { return c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '(' || c == ')'; }
    bool operation(const std::string s) { return s == "div" || s == "mod"; }
    bool uOperation(const std::string s) { return s == "sqrt" || s == "sin" || s == "tan" || s == "tg" || s == "cot" || s == "ctg" || s == "abs" || s == "cos"; }
    std::string strOp(const std::string s, unsigned& p)
    {
        std::string st;
        while (!(operation(s[p]) || s[p] == ' ' || number(s[p]))) st += std::tolower(s[p++]);
        return st;
    }
    void pushWord(ICollection<Lexem*>* tmp, const std::string s, unsigned& i)
    {
        unsigned p = i, p0 = i;
        std::string st = strOp(s, p);
        i = p - 1;
        if (operation(st))       queuePush(tmp, new Lexem(st, TypeLexem::op, p0)); // div mod
        else if (uOperation(st)) queuePush(tmp, new Lexem(st, TypeLexem::uop, p0));
        else if (st == "pi")     queuePush(tmp, new Lexem(st, TypeLexem::value, p0));
        else throw "No such operation! Error at position: " + std::to_string(p0 + 1);
    }
public:
    LexemAnalysis(std::string s = "")
    {
        this->s = s + ' ';
        q = new Queue<Lexem*>;
        state = State::oper;
    }
    void setExample(std::string in) { s = in + ' '; }
    ICollection<Lexem*>* getLexem() { return q; }
    std::string analysis(std::string in = "")
    {
        ICollection<Lexem*>* tmp = new Queue<Lexem*>;
        bool e = false;
        if (in != "") s = in + ' ';
        for (size_t i = 0; i < s.length(); i++)
        {
            char c = s[i];
            if (state == State::oper)
            {
                if (number(c))
                {
                    st = c;
                    state = State::num;
                }
                else if (operation(c)) queuePush(tmp, new Lexem(st = c, TypeLexem::op, i));
                else if (letter(c)) pushWord(tmp, s, i);
                else if (c != ' ') throw "Wrong symbol! Error at position: " + std::to_string(i + 1);
            }
            else if (state == State::num)
            {
                if (e) // Проверка на экспоненту
                {
                    if (c == '-' || c == '+' || number(c))
                    {
                        st += c;
                        e = false;
                        continue;
                    }
                    throw "Wrong symbol! Error at position: " + std::to_string(i + 1);
                }
                if (number(c) || c == 'e')
                {
                    st += c;
                    if (c == 'e') e = true;
                }
                if (letter(c)) //throw "Wrong operation! Error at position: " + std::to_string(i + 1);
                {
                    queuePush(tmp, new Lexem(st, TypeLexem::value, i));
                    pushWord(tmp, s, i); // div mod
                    state = State::oper;
                }
                if (operation(c) || c == ' ')
                {
                    queuePush(tmp, new Lexem(st, TypeLexem::value, i));
                    state = State::oper;
                }
                if (operation(c)) queuePush(tmp, new Lexem(st = c, TypeLexem::op, i));
            }
        }
        Lexem* lexem1 = tmp->pop();
        std::string out = lexem1->getStr();
        tmp->push(new Lexem("", TypeLexem::op, 0)); // Добавление пустого элемента для проработки цикла полностью
        while (!tmp->isEmpty())
        {
            Lexem* lexem2 = tmp->pop();
            if (lexem1->getType() == TypeLexem::uop && lexem2->getStr() != "(") throw "No open bracket! Error at position: " + std::to_string(lexem1->getPosition());
            if (lexem1->getType() == lexem2->getType() && lexem2->getStr() != "")
            {
                if (lexem1->getType() == TypeLexem::value) // Встретились 2 числа
                    throw "No operation! Error at position: " + std::to_string(lexem2->getPosition());
                if (lexem1->getType() == TypeLexem::uop) // Перед унарной операцией (кроме минуса) нет открывающей скобки
                    throw "No open bracket! Error at position: " + std::to_string(lexem2->getPosition());
                if (lexem1->getStr() != "(" && lexem2->getStr() != "(" && lexem1->getStr() != ")" && lexem2->getStr() != ")"
                    || lexem1->getStr() == "(" && lexem2->getStr() == ")") // Встретились 2 арифметические операции
                    throw "Not enough numbers! Error at position: " + std::to_string(lexem2->getPosition());
            }
            //if (lexem1->getStr() == ")" && lexem2->getType() == TypeLexem::value || lexem2->getStr() == "(" && lexem1->getType() == TypeLexem::value)
            //    throw "No operation! Error at position: " + std::to_string(lexem2->getPosition());
            queuePush(q, lexem1);
            if (lexem1->getType() == TypeLexem::value && lexem2->getStr() == "(" 
                || lexem1->getStr() == ")" && lexem2->getStr() == "(" || lexem1->getType() == TypeLexem::value && lexem2->getType() == TypeLexem::uop)
            {
                queuePush(q, new Lexem("*", TypeLexem::op, lexem1->getPosition())); // Добавление операции умножения перед унарными операциями и со скобками
                out += " *";
            }
            if (lexem1->getStr() == ")" && lexem2->getType() == TypeLexem::value)
            {
                queuePush(q, new Lexem("^", TypeLexem::op, lexem1->getPosition())); // Добавление операции умножения перед унарными операциями и со скобками
                out += " ^";
            }

            if (lexem1->getType() == TypeLexem::uop || lexem1->getStr() == "(" || lexem2->getStr() == ")") // Оформление выходной строки
                out += lexem2->getStr();
            else out += ' ' + lexem2->getStr();
            lexem1 = lexem2;
        }
        return out;
    }

    friend std::ostream& operator<< (std::ostream& o, const LexemAnalysis& l)
    {
        o << l.s << '\n';
        while (!l.q->isEmpty()) o << *(l.q->pop()) << '\n';
        return o;
    }
};

