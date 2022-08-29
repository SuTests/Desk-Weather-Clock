#include <WiFi.h>
#include <ESPmDNS.h>
#include <WebServer.h>
#include <HTTPClient.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
//#include <WiFiManager.h>
#include <ArduinoJson.h>
#include <TFT_eSPI.h>

#include "GConfig.h"        //一些参数配置
//#include "GWiFiManager.h"   //网页配网
#include "GNTPClient.h"     //获取NTP时间
#include "GBiliBili.h"      //获取B站数据
#include "GWeather.h"       //获取天气数据
#include "GTFT_eSPI.h"      //屏幕初始化
#include "GDisplay.h"       //显示

void setup(void) {
  Serial.begin(115200);
  Serial.println("Hello");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  //  GWiFiManager(); //网页配网
  GTFT();         //屏幕设置

  //先把需要的东西获取一遍
  GGetName();     //获取B站用户名
  GGetFans();     //获取B站粉丝数
  GGetWeather();  //获取当前天气
  GGetWeather3(); //获取三天天气
  GNTPClient();   //获取NTP时间
  delay(1000);
  Update1Min();
  delay(1000);
  Update10Min();
  delay(1000);
  Update100Min();
}


void loop(void) {
  GDisplay();
}
