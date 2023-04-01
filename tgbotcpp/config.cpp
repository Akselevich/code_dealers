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
    std::string get_help_locale(std::string filename)
    {
        pt::ptree root;
        pt::read_json(filename, root);
        std::string token = root.get<std::string>("help");
        return token;
    }
    std::string get_input_locale(std::string filename)
    {
        pt::ptree root;
        pt::read_json(filename, root);
        std::string token = root.get<std::string>("input");
        return token;
    }
    std::string get_output_locale(std::string filename)
    {
        pt::ptree root;
        pt::read_json(filename, root);
        std::string token = root.get<std::string>("output");
        return token;
    }
}