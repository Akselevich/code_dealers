#include "file_check.h"


using namespace std;
using namespace config;


string checking(const char* config)
{
    fstream inFile;

    inFile.open(get_help_locale(config));
    if (!inFile)
    {
        return "Unable to open help file!\n";
    }
    inFile.close();

    inFile.open(get_input_locale(config));
    if (!inFile)
    {
        return "Unable to open input file!\n";
    }
    inFile.close();

    inFile.open(get_output_locale(config));
    if (!inFile)
    {
       return "Unable to open output file!\n";
    }
    inFile.close();

    return "Success!\n";
}