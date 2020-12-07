#pragma once
#include "LexemAnalysis.h"
#include "Rpn.h"
#include "Compute.h"

class Calculator
{
    LexemAnalysis analysis;
    Rpn rpn;
    Compute compute;
    std::string example = "0";
    double result = 0;

public:
    Calculator(const std::string example = "") { if (example != "") this->example = example; }
    void setExample(const std::string example) { if (example != "") this->example = example; }

    double doCalculator(const std::string example = "")
    {
        if (example != "") this->example = example;
        //analysis.setExample(this->example);
        std::string ex = analysis.analysis(this->example);
        //std::cout << analysis;
        //rpn.setLexem(analysis.getLexem());
        rpn.doRpn(analysis.getLexem());
        //std::cout << rpn;
        //compute.setRpn(rpn.getRpn());
        result = compute.doCompute(rpn.getRpn());
        //result = compute.getResult();
        this->example = ex;
        return result;
    }
    double getResult() { return result; }
    std::string getExample() { return example; }

    friend std::ostream& operator<< (std::ostream& o, const Calculator& c)
    {
        o << c.example << "= "; 
        if (abs(c.result) >= 1e+9 || abs(c.result) <= 1e-4) o << c.result << '\n';
        else if (fmod(c.result, 1) == 0.0) o << int(c.result) << '\n'; // Вывод int
        else o << std::fixed << c.result << '\n';
        return o;
    }
};

