#include "libaries.h"
#include "config.h"


using namespace std;
using namespace config;

// Checking if temp.txt exists and creating if not 
void if_temptxt_exists(string jsonloc, string temp_locale) 
{
    string path = jsonloc;
    path.erase(path.find_last_of('\\') + 1);
    fstream file(temp_locale);
    if (!file)
    {
        ofstream temp(path.append("temp.txt"));
        temp.close();
        update_temp_locale(jsonloc, path);
    }
}

// Weather sync with GPS
string weather_sync_gps(string temp, string key, float latitude, float longitude, string path)
{
    // Writing input coordinates to a file temp.txt

    fstream temp_locale(temp, ios::out | ios::trunc);
    std::cout << "latitude: " << latitude << " longitude: " << longitude << endl;
    temp_locale << "!" << latitude << endl << longitude << endl;
    temp_locale.close();
    string ss = "cd ";
    ss.append(path).append("Parsing\\venv\\Scripts\\&python.exe ");
    ss.append(path).append("Parsing\\main.py ").append(temp.c_str());
    ss.append(" ").append(key);
    
    // Launching Python parser 
    system(ss.c_str());
    
    // Reading output from a file temp.txt
    ifstream output(temp);
    string out, line;
    while (getline(output, line))
    {
        out.append(line);
        out.append("\n"); 
    }
    std::cout << "<< " << out << endl;

    return out;
}

// Weather sync without GPS
string weather_sync(string temp, string key, string message, string path)
{
    // Writing input location to a file temp.txt
    ofstream temp_locale(temp, ios::out | ios::trunc);
    temp_locale << message << endl;
    temp_locale.close();
    string ss = "cd ";
    ss.append(path).append("Parsing\\venv\\Scripts\\&python.exe ");
    ss.append(path).append("Parsing\\main.py ").append(temp.c_str());
    ss.append(" ").append(key);
    
    // Launching Python parser 
    system(ss.c_str());

    // Reading output from a file temp.txt
    ifstream output(temp);
    string out, line;
    while (getline(output, line))
    {
        out.append(line);
        out.append("\n");
    }
    output.close();
    std::cout << "<< " << out << endl;

    return out;
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
        
        const auto token = get_token(argv[1]); // Getting token from config.json
        const auto help = get_help(argv[1]); // Getting help from config.json
        if_temptxt_exists(argv[1], get_temp_locale(argv[1])); // Checking if temp.txt exists and creating if not 
        const auto temp = get_temp_locale(argv[1]); // Getting temp.txt locale
        const auto key = get_key(argv[1]); // Getting Openweather.org API key
        bool flag = false;
        auto bot = TgBot::Bot(token);
        string path = argv[1];
        path.erase(path.find_last_of('\\') + 1);
    

        // Declaring commands 
        bot.getEvents().onCommand(
            "start", [&bot, &help](TgBot::Message::Ptr message)
            {
                std::cout << "<< " << help << endl;
                bot.getApi().sendMessage(message->chat->id, help);

                return;
            });

        bot.getEvents().onCommand(
            "help", [&bot, &help](TgBot::Message::Ptr message)
            {
                std::cout << "<< " << help << endl;
                bot.getApi().sendMessage(message->chat->id, help);

                return;
            });

        bot.getEvents().onCommand(
            "weather", [&bot,&flag](TgBot::Message::Ptr message)
            {
                std::cout << "<< Enter your location" << endl;
                bot.getApi().sendMessage(message->chat->id, "Enter your location");
                flag = true;
                
                return;
                      
            });

        // Messages checking 
        bot.getEvents().onAnyMessage([&bot,&flag,&temp,&path,&key](TgBot::Message::Ptr message)
            {
            
            // If message is a location
            if (message->location)
            {
                std::cout << ">> location" << endl;
                string out = weather_sync_gps(temp, key, message->location->latitude, message->location->longitude, path);
                bot.getApi().sendMessage(message->chat->id, out);
                flag = false;

                return;
            }
            else

            // If message type is a voice
            if (message->voice)
            {
                std::cout << ">> voice" << endl;
                bot.getApi().sendMessage(message->chat->id, "Sorry, we aren't support voice messages yet!");

                return;
            }   
            
            else
            {
                std::cout << ">> " << message->text.c_str() << endl;

                // If last message was a text location and previous was a /weather command
                if (message->text != "/weather" && message->text != "/help" && message->text != "/start" && flag == true)
                {
                    string out = weather_sync(temp, key, message->text.c_str(), path);
                    bot.getApi().sendMessage(message->chat->id, out);
                    flag = false;

                    return;
                }
            }
        });

        // Long poll
        TgBot::TgLongPoll longPoll(bot);
        std::cout << "Bot username: " << bot.getApi().getMe()->username.c_str() << endl;
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
