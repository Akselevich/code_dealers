import requests
with open('C:/Users/andre/Documents/tgbotcpp/input.txt') as f:
    s_city = f.read()
city_id = 0
key = "1d846a80425c1dd58e8efcc238341ff5"
try:
    res = requests.get("http://api.openweathermap.org/data/2.5/find",
                 params={'q': s_city, 'type': 'like', 'units': 'metric', 'APPID': key})
    data = res.json()
    cities = ["{} ({})".format(d['name'], d['sys']['country'])
              for d in data['list']]
    # print("city:", cities)
    city_id = data['list'][0]['id']
    # print('city_id=', city_id)
except Exception as e:
    print("Exception (find):", e)
    with open('C:/Users/andre/Documents/tgbotcpp/output.txt', 'w', encoding='utf-8') as f:
        f.write("The region was not found!\n")
        exit(1)
    pass
try:
    res = requests.get("http://api.openweathermap.org/data/2.5/weather",
                       params={'id': city_id, 'units': 'metric', 'lang': 'en', 'APPID': key})
    data = res.json()
    # print(data)
    output = "Now in this place " + str(data['weather'][0]['description']) + ".\nTemperature: " + \
             str(round(data['main']['temp'])) + " °C\n"
    '''
    output = output + " °C\nМинимальная температура за последний час: " + \
             str(data['main']['temp_min']) + " °C\nМаксимальная температура за последний час: " +\
             str(data['main']['temp_max']) + " °C\n"
    '''

    with open('C:/Users/andre/Documents/tgbotcpp/output.txt', 'w', encoding='utf-8') as f:
        f.write(output)
    print("Сейчас в городе", data['weather'][0]['description'], ".")
    print("Температура:", data['main']['temp'], "°C")
    # print("Минимальная температура за последний час:", data['main']['temp_min'], "°C")
    # print("Максимальная температура за последний час:", data['main']['temp_max'], "°C")
except Exception as e:
    print("Exception (weather):", e)
    pass
'''
try:
    res = requests.get("http://api.openweathermap.org/data/2.5/forecast",
                       params={'id': city_id, 'units': 'metric', 'lang': 'ru', 'APPID': key})
    data = res.json()
    for i in data['list']:
        print(i['dt_txt'], '{0:+3.0f}'.format(i['main']['temp']), i['weather'][0]['description'])
except Exception as e:
    print("Exception (forecast):", e)
    pass
'''