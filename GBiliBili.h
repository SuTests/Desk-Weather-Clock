#ifndef _G_BiliBili_H
#define _G_BiliBili_H

//#include <ESP8266WiFi.h>
//#include <ESP8266HTTPClient.h>
//#include <ArduinoJson.h>
#include "GWeather.h"

const String NameAPI = "http://api.bilibili.com/x/space/acc/info?mid=" + UID;
const String FansAPI = "http://api.bilibili.com/x/relation/stat?vmid=" + UID;

struct BiliBili {
  String Name = "114514";
  String Fans = "114514";
} BiliBili;

void GGetName() {
  BiliBili.Name = GGet(NameAPI)["data"]["name"].as<String>();
}

void GGetFans() {
  BiliBili.Fans = GGet(FansAPI)["data"]["follower"].as<String>();
}

#endif
