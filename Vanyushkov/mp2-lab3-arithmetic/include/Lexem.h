#pragma once
#include <iostream>
enum class TypeLexem { op, value, uop };
class Lexem
{
    std::string s;  // Число или операция
    TypeLexem type; // Тип операции
    double val;     // Значение числа (или 0 при операции)
    unsigned pos;   // Позиция в строке
public:
    Lexem(const std::string s, const TypeLexem type, const unsigned position = 0)
    {
        this->s = s;
        this->type = type;
        pos = position + 1;
        val = 0;
        if (type == TypeLexem::value) // Перевод строки в число
        {
            pos -= s.length();
            if (s == "pi") val = acos(-1); // Число Пи
            else
            {
                std::string st;
                bool e = false;
                int point = 0;
                for (size_t i = 0; i < s.length(); i++)
                {
                    if (s[i] == ',') throw "Wrong number! Error at position: " + std::to_string(pos + i);
                    if (s[i] == '.') // Проверка плавающей точки
                    {
                        point++;
                        if (point > 1) throw "Wrong number! Error at position: " + std::to_string(pos + i);
                    }
                    if (e) st += s[i];
                    if (s[i] == 'e') e = true;
                }
                if (st != "" && std::stod(st) >= 308) throw "Large number! Error at position: " + std::to_string(pos);
                val = std::stod(this->s);
            }
        }
    }

    TypeLexem getType() { return type; }
    double getVal() { return val; }
    std::string getStr() { return s; }
    unsigned getPosition() { return pos; }

    friend std::ostream& operator<< (std::ostream& o, const Lexem& p)
    {
        o << '|' << p.s << "\t " << static_cast<int>(p.type) << "\t pos: " << p.pos << '|';
        return o;
    }
};


