#include "Calculator.h"

int main()
{
    Calculator c;
    try
    {
        c.doCalculator("abs((sin(55*pi/180)2+cos(55*pi/180)2)(-tg(pi/9))/ctg(11*pi/18)-2((2.2sqrt(4))/2.2)^3mod9div2-8)");
        std::cout << c;
    }
    catch (std::string error)
    {
        std::cout << c.getExample() << '\n' << error << '\n';
    }

    return 0;
}