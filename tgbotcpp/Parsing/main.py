import requests
with open('C:/Users/andre/code_dealers/tgbotcpp/loc.txt') as f:
    s_city = f.read()
if s_city[0] == "!":
    s_city = s_city.replace("!", "")
    flag = True
else:
    flag = False
city_id = 0
key = "1d846a80425c1dd58e8efcc238341ff5"
filt = "!@#$%^&*()/?|\\:;<>"
for i in range(len(filt)):
    s_city = s_city.replace(filt[i], "")


try:
    if flag:
        lon = s_city[s_city.find('\n')+1::].replace("\n", "")
        lat = s_city[:s_city.find('\n')].replace("\n", "")
        res = requests.get("http://api.openweathermap.org/data/2.5/find",
                           params={'lat': lat, 'lon': lon, 'type': 'like', 'units': 'metric', 'APPID': key})
        data = res.json()
        cities = ["{} ({})".format(d['name'], d['sys']['country'])
                  for d in data['list']]
        city_id = data['list'][0]['id']
    else:
        res = requests.get("http://api.openweathermap.org/data/2.5/find",
                           params={'q': s_city, 'type': 'like', 'units': 'metric', 'APPID': key})
        data = res.json()
        cities = ["{} ({})".format(d['name'], d['sys']['country'])
                  for d in data['list']]
        city_id = data['list'][0]['id']


except Exception as e:
    print("Exception (find):", e)
    with open('C:/Users/andre/code_dealers/tgbotcpp/loc.txt', 'w', encoding='utf-8') as f:
        print("The region was not found!\n")
        f.write("The region was not found!\n")
    exit(1)
    pass


try:
    res = requests.get("http://api.openweathermap.org/data/2.5/weather",
                       params={'id': city_id, 'units': 'metric', 'lang': 'en', 'APPID': key})
    data = res.json()
    output = "Now in this place " + str(data['weather'][0]['description']) + ".\nTemperature: " + \
             str(round(data['main']['temp'])) + " °C\n"

    with open('C:/Users/andre/code_dealers/tgbotcpp/loc.txt', 'w', encoding='utf-8') as f:
        f.write(output)
    # print("Now in this place: ", data['weather'][0]['description'], ".")
    # print("Temperature:", data['main']['temp'], "°C")


except Exception as e:
    print("Exception (weather):", e)

    exit(1)
    pass
