#ifndef _G_NTPClient_H
#define _G_NTPClient_H

//#include <NTPClient.h>
//#include <ESP8266WiFi.h>
//#include <WiFiUdp.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

void GNTPClient() {
  timeClient.begin();
  timeClient.setTimeOffset(TZone * 3600); //设置时区，3600为一个时区
  while (!timeClient.forceUpdate()) {
    timeClient.update();//更新时间
    delay(500);
  }
}

#endif
