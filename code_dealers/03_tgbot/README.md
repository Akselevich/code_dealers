# 🚀 Telegram Bot 🚀

Telegram bot is a program that works through the messenger [Telegram](https://telegram.org) using a special [API](https://core.telegram.org/bots/api). The blank was prepared using the [Tgbot-cpp](https://github.com/reo7sp/tgbot-cpp.git) library. In addition, the example uses reading parameters from a configuration file in json format using the [Boost](https://www.boost.org) library. This is a huge library! It is necessary for Tgbot-cpp, so we use it in this project and for reading parameters. Also, we use special [Weather API](https://openweathermap.org/api) to get the weather using json requests.
## Implemented script for the bot
- Bot "Weather forecast by geolocation or region name" 🌦️
## 🤖 Supported commands 🤖
- `/start` - starts the bot and shows a list of available commands 
- `/help` - shows a list of available commands
- `/weather` - shows the weather in the specified region by asking the region name or [location](https://reo7sp.github.io/tgbot-cpp/class_tg_bot_1_1_location.html).
## 🤯 How the bot works 🤯
- The bot receives the source data in the form of text or geolocation using [Telegram API](https://core.telegram.org/bots/api).
- We use `config.json` file to get an API keys and and location of the `temp.txt` file.
- After that, the program checkes if `temp.txt` exists and if not creating it and rewriting the new location of the file to `config.json`
- Then it starts pooling.
- The bot converts the source code from the telegram to the json request for the [Openweathermap API](https://openweathermap.org/api) by saving it to `temp.txt`
- After getting the answer it saves it to `temp.txt` and then sends the message back to the user.

## 🔥 We have implemented the following functionality:

- [x]  Working app code 🩻
- [x]  Customizable API keys 🔥
- [x]  Customizable temprory file location 🔥
- [x]  Automatic rewriting of the temprory file location 🤯
- [x]  Text input type support 🔥
- [x]  Location input type support 🔥
- [x]  User-friendly interface with buttons and commands menu 🔥


## Realization of the following functionality:

### Rewriting of the temprory file location function🤯:
        
```c++
void update_temp_locale(std::string filename, std::string locale)
    {
        pt::ptree root;
        pt::read_json(filename, root);
        std::string token = root.get<std::string>("token");
        std::string help = root.get<std::string>("help");
        std::string loc = root.get<std::string>("temp");
        std::string key = root.get<std::string>("key");
        pt::ptree root2;
        root2.put("token", token);
        root2.put("help", help);
        root2.put("temp", locale);
        root2.put("key", key);
        pt::write_json(filename, root2);
        
    }
```

### Input message processing 🤯:

```c++
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
```
### Weather sync function 🤯:

```c++
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
```

### Weather sync with geolocation function 🤯:

```c++
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
```