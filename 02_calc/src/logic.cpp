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

        std::string input_ss;
        input_ss.append(expression);
        std::string output_ss;

        //int a;
        //int b;
        //char op;
        double a = te_interp(input_ss.c_str(), 0);
        //double output = te_interp("5+5", 0);
        output_ss = std::to_string(a); //костыли, чтобы убрать нули из целого числа
        output_ss.erase(output_ss.find_last_not_of('0') + 1, std::string::npos);
        if (output_ss.back() == '.')
            output_ss.replace(output_ss.find('.'), output_ss.find('.') + 1, "");
        /*switch (op)
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
        */

        return output_ss;
    }
}