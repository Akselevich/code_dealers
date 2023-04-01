#ifndef CONFIG
#define CONFIG

#include "libaries.h"

namespace config
{

    std::string get_token(std::string filename);
    std::string get_help_locale(std::string filename);
    std::string get_input_locale(std::string filename);
    std::string get_output_locale(std::string filename);
}

#endif