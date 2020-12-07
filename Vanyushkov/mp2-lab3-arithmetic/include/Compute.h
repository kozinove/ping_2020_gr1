#pragma once
#include "Lexem.h"
#include "Stack.h"
#include "Queue.h"

Lexem* uop(Lexem* v, const std::string o, const unsigned pos) // Выполнения унарных операций
{
    double val = v->getVal();
    TypeLexem type = v->getType();

    if (o == "sqrt")
    {
        if (val < 0) throw "Negative number under the root! Error at position: " + std::to_string(pos);
        return new Lexem(std::to_string(sqrt(val)), type, pos);
    }
    if (o == "sin") return new Lexem(std::to_string(sin(val)), type, pos);
    if (o == "cos") return new Lexem(std::to_string(cos(val)), type, pos);
    if (o == "tg" || o == "tan")
    {
        double s = sin(val);
        double c = cos(val);
        if (c >= -1.0e-6 && c <= 1.0e-6) // cos == 0
            throw "This angle cannot be calculated! Error at position: " + std::to_string(pos);
        return new Lexem(std::to_string(s / c), type, pos);
    }
    if (o == "ctg" || o == "cot")
    {
        double s = sin(val);
        double c = cos(val);
        if (s >= -1.0e-6 && s <= 1.0e-6) // sin == 0
            throw "This angle cannot be calculated! Error at position: " + std::to_string(pos);
        return new Lexem(std::to_string(c / s), type, pos);
    }
    return new Lexem(std::to_string(abs(val)), type, pos); // abs(val)
}

Lexem* op(Lexem* op1, Lexem* op2, const std::string o, const unsigned pos) // Выполнений операций
{
    double v1 = op1->getVal();
    double v2 = op2->getVal();
    TypeLexem type = op1->getType();

    if (o == "+")
    {
        if (isinf(v1 + v2)) throw "Large value! Error at position: " + std::to_string(pos);
        return new Lexem(std::to_string(v1 + v2), type, pos);
    }
    if (o == "-")
    {
        if (isinf(v1 - v2)) throw "Large value! Error at position: " + std::to_string(pos);
        return new Lexem(std::to_string(v1 - v2), type, pos);
    }
    if (o == "*")
    {
        if (isinf(v1 * v2)) throw "Large value! Error at position: " + std::to_string(pos);
        return new Lexem(std::to_string(v1 * v2), type, pos);
    }
    if (o == "/")
    {
        if (v2 == 0) throw "Division by zero! Error at position: " + std::to_string(pos);
        if (isinf(v1 / v2)) throw "Large value! Error at position: " + std::to_string(pos);
        return new Lexem(std::to_string(v1 / v2), type, pos);
    }
    if (o == "^")
    {
        if (v1 == 0 && v2 == 0) throw "Uncertainty of the form 0 ^ 0! Error at position: " + std::to_string(pos);
        if (isinf(pow(v1, v2))) throw "Large value! Error at position: " + std::to_string(pos);
        if (v1 < 0 && abs(v2) < 1)
        {
            double tmp = (1 / abs(v2));
            if (fmod(tmp, 2) == 0) throw "Negative number under the root! Error at position: " + std::to_string(pos);
        }
        return new Lexem(std::to_string(pow(v1, v2)), type, pos);
    }
    if (o == "mod")
    {
        if (v2 == 0) throw "Division by zero! Error at position: " + std::to_string(pos);
        return new Lexem(std::to_string(fmod(v1, v2)), type, pos);
    }
    if (v2 == 0) throw "Division by zero! Error at position: " + std::to_string(pos);
    return new Lexem(std::to_string((v1 - fmod(v1, v2)) / v2), type, pos); // v1 div v2
}

class Compute
{
    ICollection<Lexem*>* stack; // Выходной стек (результат)
    ICollection<Lexem*>* input; // Входные данные
    double result = 0;

    Lexem* stackPop(Lexem* lexem) 
    { 
        if (stack->isEmpty()) throw "Not enough numbers! Error at position: " + std::to_string(lexem->getPosition()); 
        return stack->pop();
    }
public:
    Compute(ICollection<Lexem*>* in = nullptr)
    {
        stack = new Stack<Lexem*>;
        input = new Queue<Lexem*>;
        if (in) input = in;
    }
    void setRpn(ICollection<Lexem*>* in) { input = in; }
    double getResult() { return result; }
    double doCompute(ICollection<Lexem*>* in = nullptr)
    {
        if (in) input = in;
        while (!input->isEmpty())
        {
            Lexem* lexem = input->pop();
            if (lexem->getType() == TypeLexem::value) stack->push(lexem);
            else if (lexem->getType() == TypeLexem::uop) stack->push(uop(stackPop(lexem), lexem->getStr(), lexem->getPosition()));
            else
            {
                Lexem* op2 = stackPop(lexem);
                Lexem* op1 = stackPop(lexem);
                stack->push(op(op1, op2, lexem->getStr(), lexem->getPosition()));
            }
        }
        double res = stack->pop()->getVal();
        if (!stack->isEmpty()) throw "Not enough operations!";
        result = res;
        return res;
    }
};

