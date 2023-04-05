#include "libaries.h"
#include "config.h"


using namespace std;
using namespace config;

// Checking if loc.txt exists and creating if not 
bool if_loctxt_exists(string jsonloc, string loc_locale) 
{
    string path = jsonloc;
    path.erase(path.find_last_of('\\') + 1);
    fstream file(loc_locale);
    if (!file)
    {
        ofstream loc(path.append("loc.txt"));
        loc.close();
        update_loc_locale(jsonloc, path);
        return false;
    }
    else
        return true;
}
 
// Weather sync with GPS
string weather_sync_gps(string loc, float latitude, float longitude, string path)
{
    ofstream loc_localew(loc, ios::out | ios::trunc);
    cout << "latitude: " << latitude << " longitude: " << longitude << endl;
    loc_localew << "!" << latitude << endl << longitude << endl;
    loc_localew.close();
    string ss = "cd ";
    ss.append(path).append("Parsing\\venv\\Scripts\\&python.exe ").append(path).append("Parsing\\main.py ").append(loc.c_str());
    system(ss.c_str());
    
    ifstream outputw(loc);
    string weather_f, line;
    while (getline(outputw, line))
    {
        weather_f.append(line);
        weather_f.append("\n"); 
    }
    outputw.close();
    cout << weather_f << endl;

    return weather_f;
}

// Weather sync without GPS
string weather_sync(string loc, string message, string path)
{
    ofstream loc_localew(loc, ios::out | ios::trunc);
    cout << message << endl;
    loc_localew << message << endl;
    loc_localew.close();
    string ss = "cd ";
    ss.append(path).append("Parsing\\venv\\Scripts\\&python.exe ").append(path).append("Parsing\\main.py ").append(loc.c_str());
    system(ss.c_str());

    ifstream outputw(loc);
    string weather_f, line;
    while (getline(outputw, line))
    {
        weather_f.append(line);
        weather_f.append("\n");
    }
    outputw.close();
    cout << weather_f << endl;

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
        const auto help = get_help(argv[1]);
        const auto loc = get_loc_locale(argv[1]);
        if_loctxt_exists(argv[1], loc);
        const auto loc_locale = get_loc_locale(argv[1]);
        bool flag = false;
        auto bot = TgBot::Bot(token);
        string path = argv[1];
        path.erase(path.find_last_of('\\') + 1);
    

        // Declaring commands 
        bot.getEvents().onCommand(
            "start", [&bot, &help](TgBot::Message::Ptr message)
            {
                bot.getApi().sendMessage(message->chat->id, help);

                return;
            });

        bot.getEvents().onCommand(
            "help", [&bot, &help](TgBot::Message::Ptr message)
            {
                bot.getApi().sendMessage(message->chat->id, help);

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
        bot.getEvents().onAnyMessage([&bot,&flag,&loc_locale,&path](TgBot::Message::Ptr message)
            {

            // If message is a location
            if (message->location)
            {
                cout << ">> " << message->text.c_str() << endl;
                string weather_f = weather_sync_gps(loc_locale, message->location->latitude, message->location->longitude, path);
                bot.getApi().sendMessage(message->chat->id, weather_f);
                flag = false;
                return;
            }
            else
            {

                // If last message was a location and previous was a /weather command
                if (message->text != "/weather" && message->text != "/help" && message->text != "/start" && flag == true)
                {

                    // If message type is location
                    if (message->location)
                    {
                        cout << ">> " << message->text.c_str() << endl;
                        string weather_f = weather_sync_gps(loc_locale, message->location->latitude, message->location->longitude, path);
                        bot.getApi().sendMessage(message->chat->id, weather_f);
                        flag = false;
                        return;
                    }

                    // If message type is voice
                    if (message->voice)
                    {
                        cout << "Voice message" << endl;
                        bot.getApi().sendMessage(message->chat->id, "Sorry, we aren't support voice messages yet!");
                        return;
                    }

                    // If message type is text
                    else
                    {
                        cout << "Location input: " << endl;
                        string weather_f = weather_sync(loc_locale, message->text.c_str(), path);
                        bot.getApi().sendMessage(message->chat->id, weather_f);
                        flag = false;
                        return;
                    }
                }
            }
        });

        // Long poll
        TgBot::TgLongPoll longPoll(bot);
        cout << "Bot username: " << bot.getApi().getMe()->username.c_str() << endl;
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
