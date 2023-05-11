#ifndef CONFIG
#define CONFIG

#include "libaries.h"

namespace config
{

    std::string get_token(std::string filename);
    std::string get_help(std::string filename);
    std::string get_temp_locale(std::string filename);
    std::string get_key(std::string filename);
    void update_temp_locale(std::string filename, std::string locale);
}

#endif