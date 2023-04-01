#include "libaries.h"
#include "config.h"
#include "file_check.h"


using namespace std;
using namespace StringTools;
using namespace config;


int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        cerr << "Error! Config.json doesn't exist!" << endl;
        exit(1);
    }

    if (checking(argv[1]) != "Success!\n")
    {
        cout << "Error! Check failed! " << checking(argv[1]);;
        exit(1);
    }

    try
    {
        const auto token = get_token(argv[1]);
        const auto input_locale = get_input_locale(argv[1]);
        const auto output_locale = get_output_locale(argv[1]);
        const auto help_locale = get_help_locale(argv[1]);
        bool flag = false;
        auto bot = TgBot::Bot(token);
         

        // Bot config
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
                
            });
        bot.getEvents().onAnyMessage([&bot,&flag,&input_locale, &output_locale](TgBot::Message::Ptr message)
            {
                cout << ">> " << message->text.c_str() << endl;
            if (message->text != "/weather" && message->text != "/help" && message->text != "/start" && flag == true)
                {
                ofstream inputw(input_locale, ios::out | ios::trunc);
                cout << message->text.c_str() << endl;
                inputw << message->text.c_str();
                inputw.close();
                system("cd C:/Users/andre/PycharmProjects/Parsing/venv/Scripts/&python.exe C:/Users/andre/PycharmProjects/Parsing/main.py");
                ifstream outputw(output_locale);
                //outputw.open(output_locale, ios::in);
                string weather_f, line;
                while (getline(outputw, line))
                {
                    weather_f.append(line);
                    weather_f.append("\n");
                }
                outputw.close();
                cout << weather_f << endl;
                bot.getApi().sendMessage(message->chat->id, weather_f);
                flag = false;
                }


        
        //Commands checking
        if (startsWith(message->text, "/start") || startsWith(message->text, "/weather") ||
            startsWith(message->text, "/help")) { 
            return;
        }

        //bot.getApi().sendMessage(message->chat->id, "Your message is: " + message->text); 
            });

        // Start
        TgBot::TgLongPoll longPoll(bot);
        cout << "Long poll..." << endl;
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