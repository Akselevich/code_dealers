#ifndef CONFIG
#define CONFIG

#include "libaries.h"

namespace config
{

    std::string get_token(std::string filename);
    std::string get_help(std::string filename);
    std::string get_loc_locale(std::string filename);
}

#endif