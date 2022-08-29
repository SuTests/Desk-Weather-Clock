#ifndef _G_WiFiManager_H
#define _G_WiFiManager_H

//#include <WiFiManager.h>

void GWiFiManager() {
  WiFi.mode(WIFI_AP_STA);   //设置WiFi模式
  WiFiManager wm;           //创建一个实例
  wm.autoConnect("ESP32");  //自动连接WiFi，如果连不上则启用一个名为ESP32的AP
}

#endif
