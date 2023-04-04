#include "config.h"
#include <iostream>


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
        std::string help = root.get<std::string>("help");
        return help;
    }
    std::string get_loc_locale(std::string filename)
    {
        pt::ptree root;
        pt::read_json(filename, root);
        std::string loc = root.get<std::string>("loc");
        return loc;
    }
    void update_loc_locale(std::string filename, std::string locale)
    {
        pt::ptree root;
        pt::read_json(filename, root);
        std::string token = root.get<std::string>("token");
        std::string help = root.get<std::string>("help");
        std::string loc = root.get<std::string>("loc");
        pt::ptree root2;
        root2.put("token", token);
        root2.put("help", help);
        root2.put("loc", locale);
        pt::write_json(filename, root2);
        
    }
}