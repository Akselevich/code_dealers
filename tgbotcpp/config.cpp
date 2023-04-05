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

    std::string get_temp_locale(std::string filename)
    {
        pt::ptree root;
        pt::read_json(filename, root);
        std::string temp = root.get<std::string>("temp");
        return temp;
    }

    std::string get_key(std::string filename)
    {
        pt::ptree root;
        pt::read_json(filename, root);
        std::string key = root.get<std::string>("key");
        return key;
    }

    void update_temp_locale(std::string filename, std::string locale)
    {
        pt::ptree root;
        pt::read_json(filename, root);
        std::string token = root.get<std::string>("token");
        std::string help = root.get<std::string>("help");
        std::string loc = root.get<std::string>("temp");
        pt::ptree root2;
        root2.put("token", token);
        root2.put("help", help);
        root2.put("temp", locale);
        pt::write_json(filename, root2);
        
    }
}