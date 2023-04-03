#include "config.h"


namespace config
{
    namespace pt = boost::property_tree;

    std::string get_token(std::string filename)
    {
        pt::ptree root;
        pt::read_json(filename, root);
        std::string token = root.get<std::string>("token");
        return token;
    }
    std::string get_help(std::string filename)
    {
        pt::ptree root;
        pt::read_json(filename, root);
        std::string token = root.get<std::string>("help");
        return token;
    }
    std::string get_loc_locale(std::string filename)
    {
        pt::ptree root;
        pt::read_json(filename, root);
        std::string token = root.get<std::string>("loc");
        return token;
    }
}