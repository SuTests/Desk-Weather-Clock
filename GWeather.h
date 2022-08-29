#ifndef _G_Weather_H
#define _G_Weather_H

//#include <ESP8266WiFi.h>
//#include <ESP8266HTTPClient.h>
//#include <ArduinoJson.h>

//当前天气
const String WeatherAPI = "http://api.seniverse.com/v3/weather/now.json?key=" + Key + "&location=" + City + "&language=zh-Hans&unit=c";
//三天天气
const String Weather3API = "http://api.seniverse.com/v3/weather/daily.json?key=" + Key + "&location=" + City + "&language=zh-Hans&unit=c";

DynamicJsonDocument GWeather(2048);
DynamicJsonDocument GGet(String URL) {
  DynamicJsonDocument doc(2048);
  HTTPClient http;
  http.begin(URL);
  if (http.GET() == HTTP_CODE_OK)
    deserializeJson(doc, http.getString());
  http.end();
  return doc;
}

struct Weather {
  String city;                //所在城市
  String text;                //天气现象文字
  int code;                   //天气现象代码
  int temp;                   //当前温度
} Weather;

struct Weather3 {
  String date;                //日期
  String text_day;            //白天天气现象文字
  int code_day;               //白天天气现象代码
  String text_night;          //晚间天气现象文字
  int code_night;             //晚间天气现象代码
  int high;                   //当天最高温度
  int low;                    //当天最低温度
  float rainfall;             //降水量，单位mm
  float precip;               //降水概率，范围0~100，单位百分比
  String wind_direction;      //风向文字
  int wind_direction_degree;  //风向角度，范围0~360
  float wind_speed;           //风速，单位km/h（当unit=c时）、mph（当unit=f时）
  int wind_scale;             //风力等级
  int humidity;               //相对湿度，0~100，单位为百分比
} Weather3[3];

void GGetWeather() {
  GWeather = GGet(WeatherAPI);
  Weather.city = GWeather["results"][0]["location"]["name"].as<String>();
  Weather.text = GWeather["results"][0]["now"]["text"].as<String>();
  Weather.code = GWeather["results"][0]["now"]["code"].as<int>();
  Weather.temp = GWeather["results"][0]["now"]["temperature"].as<int>();
}

void GGetWeather3() {
  GWeather = GGet(Weather3API);
  for (int i = 0; i < 3; i++) {
    Weather3[i].date = GWeather["results"][0]["daily"][i]["date"].as<String>();
    Weather3[i].text_day = GWeather["results"][0]["daily"][i]["text_day"].as<String>();
    Weather3[i].code_day = GWeather["results"][0]["daily"][i]["code_day"].as<int>();
    Weather3[i].text_night = GWeather["results"][0]["daily"][i]["text_night"].as<String>();
    Weather3[i].code_night = GWeather["results"][0]["daily"][i]["code_night"].as<int>();
    Weather3[i].high = GWeather["results"][0]["daily"][i]["high"].as<int>();
    Weather3[i].low = GWeather["results"][0]["daily"][i]["low"].as<int>();
    Weather3[i].rainfall = GWeather["results"][0]["daily"][i]["rainfall"].as<float>();
    Weather3[i].precip = GWeather["results"][0]["daily"][i]["precip"].as<float>();
    Weather3[i].wind_direction = GWeather["results"][0]["daily"][i]["wind_direction"].as<String>();
    Weather3[i].wind_direction_degree = GWeather["results"][0]["daily"][i]["wind_direction_degree"].as<int>();
    Weather3[i].wind_speed = GWeather["results"][0]["daily"][i]["wind_speed"].as<float>();
    Weather3[i].wind_scale = GWeather["results"][0]["daily"][i]["wind_scale"].as<int>();
    Weather3[i].humidity = GWeather["results"][0]["daily"][i]["humidity"].as<int>();
  }
}

#endif
