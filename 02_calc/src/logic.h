#ifndef LOGIC_HPP
#define LOGIC_HPP

#include <string> // for char_traits, operator+, string, basic_string
#include <cmath>

namespace calc
{

    struct Logic
    {
        std::string process_math();
        std::string expression;
    };

}

#endif // LOGIC_HPP