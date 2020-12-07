#pragma once
#include "Queue.h"
#include "Stack.h"
#include "Lexem.h"

int priority(std::string op) // Приоритет операций
{
    if (op == "+" || op == "-") return 1;
    if (op == "div") return 2;
    if (op == "mod") return 3;
    if (op == "*" || op == "/") return 4;
    if (op == "^") return 5;
    return 0;
}

template<class T>
class BktPosition
{
    T lexem;      // Скобка
    int position; // Позиция
public:
    BktPosition() { lexem = nullptr; position = -1; }
    int getPosition() { return position; }
    T getLexem() { return lexem; }
    void delPosition() { position = -1; }
    void setLexem(const T s, int p) { lexem = s; position = p; }
};

class Rpn
{
    ICollection<Lexem*>* oper;   // Стек операций
    BktPosition<Lexem*>* uOper;  // Стек унарных операций
    ICollection<Lexem*>* valIn;  // Входной поток
    ICollection<Lexem*>* valOut; // Выходной поток

    void pushOp(Lexem* lexem)
    {
        bool pop = true;
        Lexem* tmp = oper->pop();
        while (priority(tmp->getStr()) >= priority(lexem->getStr())) // Проверка на больший или равный приоритет
        {
            valOut->push(tmp);
            if (oper->isEmpty())
            {
                pop = false;
                break;
            }
            tmp = oper->pop();
        }
        if (pop) oper->push(tmp); // Изъятый элемент имеет меньший приоритет
        oper->push(lexem);
    }

public:
    Rpn(ICollection<Lexem*>* in = nullptr)
    {
        oper = new Stack<Lexem*>;
        uOper = new BktPosition<Lexem*>[100];
        valIn = new Queue<Lexem*>;
        if (in) valIn = in;
        valOut = new Queue<Lexem*>;
    }
    ~Rpn() { delete[] uOper; }
    void setLexem(ICollection<Lexem*>* in) { valIn = in; }
    ICollection<Lexem*>* getRpn() { return valOut; }
    void doRpn(ICollection<Lexem*>* in = nullptr)
    {
        if (in) valIn = in;
        int bkt = 0;          // Проверка скобок
        bool prevVal = false; // Для унароной операции '-' (-4 = 0 - 4)
        while (!valIn->isEmpty())
        {
            Lexem* lexem = valIn->pop();
            if (lexem->getType() == TypeLexem::value) // Добавление операндов в выходной поток
            {
                valOut->push(lexem);
                prevVal = true;
            }
            else if (lexem->getType() == TypeLexem::op) // Обработка операций
            {
                if (lexem->getStr() == "-") // Обработка минуса
                {
                    if (!prevVal) valOut->push(new Lexem("0", TypeLexem::value, lexem->getPosition())); // Унарный минус
                    if (oper->isEmpty()) oper->push(lexem);
                    else pushOp(lexem);
                }
                else if (lexem->getStr() == ")") // Обработка закрывающей скобки
                {
                    bkt--;
                    if (bkt < 0) throw "No open bracket! Error at position: " + std::to_string(lexem->getPosition());
                    Lexem* tmp = oper->pop();
                    while (tmp->getStr() != "(") // Поиск открывающей скобки
                    {
                        valOut->push(tmp);
                        if (oper->isEmpty()) break;
                        tmp = oper->pop();
                    }
                    if (uOper[bkt].getPosition() == bkt)
                    {
                        valOut->push(uOper[bkt].getLexem());
                        uOper[bkt].delPosition(); // Удаление унарной операции
                    }
                }
                else if (lexem->getStr() == "(") // Обработка открывающей скобки
                {
                    oper->push(lexem);
                    bkt++;
                }
                else if (oper->isEmpty()) oper->push(lexem); // Добавление первой операции 
                else pushOp(lexem); // Обработка операций
                if (lexem->getStr() != ")") prevVal = false;
            }
            else // Обработка унарных операций (кроме минуса)
            {
                uOper[bkt].setLexem(lexem, bkt); 
                prevVal = false;
            }
        }
        if (bkt > 0) // Проверка на оставшиеся открывающие скобки
        {
            Lexem* lexem = oper->pop();
            while (lexem->getStr() != "(") lexem = oper->pop(); // Поиск открывающеся скобки
            throw "No close bracket! Error at position: " + std::to_string(lexem->getPosition());
        }
        while (!oper->isEmpty()) valOut->push(oper->pop());
    }

    friend std::ostream& operator<< (std::ostream& o, const Rpn& l)
    {
        while (!l.valOut->isEmpty()) o << *(l.valOut->pop()) << '\n';
        return o;
    }
};

