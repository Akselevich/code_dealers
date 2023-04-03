#include "libaries.h"
#include "config.h"
#include "file_check.h"


using namespace std;
using namespace StringTools;
using namespace config;


int main(int argc, char* argv[])
{
    // Config.json checking
    if (argc < 2)
    {
        cerr << "Error! Config.json doesn't exist!" << endl;
        exit(1);
    }
    // Files checking
    if (checking(argv[1]) != "Success!\n")
    {
        std::cout << "Error! Check failed! " << checking(argv[1]);;
        exit(1);
    }

    try
    {
        const auto token = get_token(argv[1]);
        const auto input_locale = get_input_locale(argv[1]);
        const auto output_locale = get_output_locale(argv[1]);
        const auto help_locale = get_help_locale(argv[1]);
        const auto loc_locale = get_loc_locale(argv[1]);
        bool flag = false;
        auto bot = TgBot::Bot(token);
         

        // Declaring commands 
        bot.getEvents().onCommand(
            "start", [&bot, &help_locale](TgBot::Message::Ptr message)
            {
                fstream helpw(help_locale);
                string current_raw, help_res;
                help_res = "Hello! Here is a list of availible commands:\n";
                while (getline(helpw, current_raw)) {
                    help_res.append(current_raw).append("\n");
                }
                bot.getApi().sendMessage(message->chat->id, help_res);
                helpw.close();

                return;
            });

        bot.getEvents().onCommand(
            "weather", [&bot,&flag](TgBot::Message::Ptr message)
            {
              bot.getApi().sendMessage(message->chat->id, "Enter your location");
              flag = true;
              
              return;
                      
            });

        bot.getEvents().onCommand(
            "help", [&bot,&help_locale](TgBot::Message::Ptr message)
            {
                fstream helpw(help_locale);
                string current_raw, help_res;
                help_res = "Here is a list of availible commands:\n";
                while (getline(helpw, current_raw)) {
                    help_res.append(current_raw).append("\n");
                }
                bot.getApi().sendMessage(message->chat->id, help_res);
                helpw.close();

                return;
            });

        // Messages checking 
        bot.getEvents().onAnyMessage([&bot,&flag,&input_locale, &output_locale, &loc_locale](TgBot::Message::Ptr message)
            {
                std::cout << ">> " << message->text.c_str() << endl;
            // if last message was a location and previous was a /weather command
            if (message->text != "/weather" && message->text != "/help" && message->text != "/start" && flag == true)
            {
                // if message type is location
                if (message->location)
                {
                    auto latitude = message->location->latitude;
                    auto longitude = message->location->longitude;
                    ofstream inputw(input_locale, ios::out | ios::trunc);
                    ofstream loc_localew(loc_locale, ios::out | ios::trunc);
                    std::cout << "latitude: " << latitude << "\nlongitude: " << longitude << endl;
                    string cords = "latitude: ";
                    loc_localew << latitude << endl << longitude << endl;
                    loc_localew.close();
                    inputw << "!!!";
                    inputw.close();
                    system("cd C:/Users/andre/code_dealers/tgbotcpp/Parsing/venv/Scripts/&python.exe C:/Users/andre/code_dealers/tgbotcpp/Parsing/main.py");
                    ifstream outputw(output_locale);
                    string weather_f, line;
                    while (getline(outputw, line))
                    {
                        weather_f.append(line);
                        weather_f.append("\n");
                    }
                    outputw.close();
                    std::cout << weather_f << endl;
                    bot.getApi().sendMessage(message->chat->id, weather_f);
                    flag = false;
                }
                // if message type is text
                else
                {
                    ofstream inputw(input_locale, ios::out | ios::trunc);
                    ofstream loc_localew(loc_locale, ios::out | ios::trunc);
                    std::cout << message->text.c_str() << endl;
                    inputw << message->text.c_str();
                    inputw.close();
                    loc_localew << "!!!";
                    loc_localew.close();
                    system("cd C:/Users/andre/code_dealers/tgbotcpp/Parsing/venv/Scripts/&python.exe C:/Users/andre/code_dealers/tgbotcpp/Parsing/main.py");
                    ifstream outputw(output_locale);
                    string weather_f, line;
                    while (getline(outputw, line))
                    {
                        weather_f.append(line);
                        weather_f.append("\n");
                    }
                    outputw.close();
                    std::cout << weather_f << endl;
                    bot.getApi().sendMessage(message->chat->id, weather_f);
                    flag = false;
                }
            }
        });
        

        // Long poll
        TgBot::TgLongPoll longPoll(bot);
        std::cout << "Long poll..." << endl;
        while (true)
        {  
            longPoll.start();
        }
    }   

    catch (const exception& e)
    {
        cerr << "Error! " << e.what() << '\n';
    }

    exit(0);
}
