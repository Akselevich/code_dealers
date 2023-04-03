#include "libaries.h"
#include "config.h"


using namespace std;
using namespace config;

// Weather sync with GPS
string weather_sync_gps(string loc, float latitude, float longitude)
{
    ofstream loc_localew(loc, ios::out | ios::trunc);
    std::cout << "latitude: " << latitude << "\nlongitude: " << longitude << endl;
    string cords = "latitude: ";
    loc_localew << "!" << latitude << endl << longitude << endl;
    loc_localew.close();
    system("cd C:/Users/andre/code_dealers/tgbotcpp/Parsing/venv/Scripts/&python.exe C:/Users/andre/code_dealers/tgbotcpp/Parsing/main.py");

    ifstream outputw(loc);
    string weather_f, line;
    while (getline(outputw, line))
    {
        weather_f.append(line);
        weather_f.append("\n"); 
    }
    outputw.close();
    std::cout << weather_f << endl;

    return weather_f;
}

// Weather sync without GPS
string weather_sync(string loc, string message)
{
    ofstream loc_localew(loc, ios::out | ios::trunc);
    std::cout << "location: " << message << endl;
    loc_localew << message << endl;
    loc_localew.close();
    system("cd C:/Users/andre/code_dealers/tgbotcpp/Parsing/venv/Scripts/&python.exe C:/Users/andre/code_dealers/tgbotcpp/Parsing/main.py");

    ifstream outputw(loc);
    string weather_f, line;
    while (getline(outputw, line))
    {
        weather_f.append(line);
        weather_f.append("\n");
    }
    outputw.close();
    std::cout << weather_f << endl;

    return weather_f;
}


int main(int argc, char* argv[])
{
    // Config.json checking
    if (argc < 2)
    {
        cerr << "Error! Config.json doesn't exist!" << endl;
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
                bot.getApi().sendMessage(message->chat->id, help_locale);

                return;
            });

        bot.getEvents().onCommand(
            "help", [&bot, &help_locale](TgBot::Message::Ptr message)
            {
                bot.getApi().sendMessage(message->chat->id, help_locale);

                return;
            });

        bot.getEvents().onCommand(
            "weather", [&bot,&flag](TgBot::Message::Ptr message)
            {
                bot.getApi().sendMessage(message->chat->id, "Enter your location");
                flag = true;
                
                return;
                      
            });

        // Messages checking 
        bot.getEvents().onAnyMessage([&bot,&flag,&input_locale, &output_locale, &loc_locale](TgBot::Message::Ptr message)
            {
            // If last message was a location and previous was a /weather command
            if (message->text != "/weather" && message->text != "/help" && message->text != "/start" && flag == true)
            {
                
                // If message type is location
                if (message->location)
                {
                    std::cout << ">> " << message->text.c_str() << endl;
                    string weather_f = weather_sync_gps(loc_locale, message->location->latitude, message->location->longitude);
                    bot.getApi().sendMessage(message->chat->id, weather_f);
                    flag = false;
                }
                // If message type is text
                else
                {
                    std::cout << "Location input " << endl;
                    string weather_f = weather_sync(loc_locale, message->text.c_str());
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
