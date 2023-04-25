#include "logic.h"
#include <sstream>

namespace calc
{
    std::string Logic::process_math()
    {
        if (expression.empty())
        {
            return "";
        }

        std::istringstream input_ss(expression);
        std::stringstream output_ss;

        int a;
        int b;
        char op;
        input_ss >> a >> op >> b;
        switch (op)
        {
        case '+':
            output_ss << a << op << b << "=" << a + b;
            break;
        case '-':
            output_ss << a << op << b << "=" << a - b;
            break;
        case '*':
            output_ss << a << op << b << "=" << a * b;
            break;
        case '/':
            output_ss << a << op << b << "=" << a / b;
            break;
        case '^':
            output_ss << a << op << b << "=" << pow(a,b);
            break;
        case '%':
            output_ss << a << op << b << "=" << a%b;
            break;
        default:
            output_ss << "Invalid expression!";
            break;
        }

        return output_ss.str();
    }
}