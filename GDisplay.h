#include <math.h>

//根据城市名确定温度的显示位置和是否显示
int tempx = 75;//两个字的城市名默认位置在75
void tempload() { //一开始要确定的一些参数
  if (Weather.city.length() > 6)//三个字城市名温度位置向右移动到105
    tempx = 105;
  if (Weather.city.length() > 9)//三个字以上城市名不显示大温度（移到屏幕外，假装不存在）
    tempx = 0;
}

//第二行的轮播字
const int n = 15; //轮播字行数
String SSS[n];    //用来存放字
void upSSS() {    //更新轮播字
  int i = 0, j = 0;
  String howday[3] = {"今", "明", "后"};
  for (int i = 0; i < 3; i++) {
    if (Weather3[i].code_day != 12)//雷阵雨伴有冰雹字太多显示不下惹
      SSS[j++] = howday[i] + "天白天" + Weather3[i].text_day;
    else SSS[j++] = howday[i] + "天雷阵雨冰雹";
    if (Weather3[i].code_night != 12)
      SSS[j++] = howday[i] + "天晚上" + Weather3[i].text_night;
    else SSS[j++] = howday[i] + "晚雷阵雨冰雹";
    SSS[j++] = howday[i] + "天最高" + String(Weather3[i].high) + "℃";
    SSS[j++] = howday[i] + "天最低" + String(Weather3[i].low) + "℃";
    if (Weather3[i].wind_direction.length() < 14)
      SSS[j++] = howday[i] + "天" + Weather3[i].wind_direction + "风" + Weather3[i].wind_scale + "级";
    else SSS[j++] = howday[i] + "天无持续风向";
  }
  //  SSS[j++] = "XD";
}

//轮播字的强度和更换下一行
int j = 0;
bool b = true;
int sinx() {
  int light = (sin(millis() / 1000.0) + 1) * 1020;
  if (light < 1)if (b)j++, b = false;
  if (light > 1)b = true;
  if (j == n)j = 0;
  if (light > 255)return 255;
  return light;
}

//时间冒号的强度
int asinx() {
  int light = abs(asin((millis() % 1000) / 1000.0 - 1)) / M_PI_2 * 510 + 50;
  if (light > 255)return 255;
  return light;
}

//坐标x,坐标y,字体,颜色,背景颜色,文字
void GGBond(int32_t x, int32_t y, const uint8_t array[], uint16_t color, uint16_t bgcolor, String SSS) {
  spr.setTextColor(color, bgcolor);
  spr.loadFont(array);
  spr.drawString(SSS, x, y);
  spr.unloadFont();
}

//如果时间是一位数，那便在前面加个0
String Num2Str(int n) {
  if (n > 9)return String(n);
  return "0" + String(n);
}

//判断天气对应的图片
int WNumber() {
  switch (Weather.code) {
    case 2: return 0;
    case 3: return 1;
    case 7: return 5;
    case 8: return 6;
    case 27: return 26;
    case 29: return 28;
    case 30: return 29;
    case 31: return 27;
    case 32: return 8;
    case 33: return 8;
    case 34: return 7;
    case 35: return 7;
    case 36: return 3;
    case 37: return 2;
    case 38: return 0;
    case 99: return 0;
    default: return Weather.code;
  }
}

//不同时间更新信息
int time1 = 0, time10 = 0, time100 = 0, WNum;
void Update1Min() { //每1分钟要刷新的放这里
  if (millis() > time1) {
    time1 = millis() + 60000;
    GGetFans(); //获取B站粉丝数
    upSSS();    //更新轮播字
    Serial.println("Update1Min");
  }
}
void Update10Min() { //每10分钟要刷新的放这里
  if (millis() > time10) {
    time10 = millis() + 600000;
    GGetWeather();            //获取当前天气
    WNum = WNumber();
    Serial.println("Update10Min");
  }
}
void Update100Min() { //每100分钟要刷新的放这里
  if (millis() > time100) {
    time100 = millis() + 6000000;
    GGetWeather3();           //获取三天天气
    GGetName();               //获取B站用户名
    tempload();               //确定温度显示位置
    timeClient.update();      //更新时间
    Serial.println("Update100Min");
  }
}

void GDisplay() {//不知道是为什么，Sprite设置成16bit就不能一次绘制240x280分辨率了，遂分三次绘制全屏
  Update1Min();
  Update10Min();
  Update100Min();
  //-----------------------------显示城市名、轮播字和天气图片-------------------
  spr.createSprite(240, 60);                          //创建雪碧精灵
  spr.pushImage(0, -32, 240,  280, background);       //显示背景图片
  spr.pushImage(150, 0, 90, 60, weather[WNum]);       //显示天气图片
  GGBond(17, 8, XiaoTuTi28, upCity, 0XFFFF, Weather.city);                              //城市名
  GGBond(17, 41, XiaoTuTi20, spr.alphaBlend(sinx(), loopWord, 0XFFFF), 0XFFFF, SSS[j]); //轮播字
  if (tempx)GGBond(tempx, 10, XiaoTuTi25, upTemp, 0XFFFF, String(Weather.temp) + "℃");  //顶部温度
  spr.pushSprite(0, 32);                              //显示到屏幕上
  spr.deleteSprite();                                 //删除雪碧精灵
  //-----------------------------显示时间(□-□)-----------------------------
  spr.createSprite(240, 70);                          //创建雪碧精灵
  spr.pushImage(0, -106, 240,  280, background);      //显示背景图片
  spr.setTextDatum(TR_DATUM);
  GGBond(90, 0, wendao, timeNum, 0XFFFF, Num2Str(timeClient.getHours()));       //小时
  spr.setTextDatum(TL_DATUM);
  GGBond(145, 0, wendao, timeNum, 0XFFFF, Num2Str(timeClient.getMinutes()));    //分钟
  spr.fillSmoothCircle(120, 29, 3, spr.alphaBlend(asinx(), timeColon, 0XFFFF)); //冒号
  spr.fillSmoothCircle(120, 49, 3, spr.alphaBlend(asinx(), timeColon, 0XFFFF)); //冒号
  spr.pushSprite(0, 106);                             //显示到屏幕上
  spr.deleteSprite();                                 //删除雪碧精灵
  //-----------------------------显示两个进度条------------------------------
  spr.createSprite(240, 45);                          //创建雪碧精灵
  spr.pushImage(0, -187, 240,  280, background);      //显示背景图
  GGBond(017, 02, XiaoTuTi20, BarAWord, 0XFFFF, "温度："); //温度文字
  GGBond(017, 27, XiaoTuTi20, BarBWord, 0XFFFF, "湿度："); //湿度文字
  GGBond(180, 02, XiaoTuTi20, BarANumb, 0XFFFF, String(Weather.temp) + "℃");         //温度数字
  GGBond(180, 27, XiaoTuTi20, BarBNumb, 0XFFFF, String(Weather3[0].humidity) + " %"); //湿度数字
  spr.drawRoundRect(67, 00, 106, 17, 6, BarASide);    //温度进度条
  spr.drawRoundRect(68, 01, 104, 15, 5, BarASide);    //温度进度条
  spr.drawRoundRect(67, 25, 106, 17, 6, BarBSide);    //湿度进度条
  spr.drawRoundRect(68, 26, 104, 15, 5, BarBSide);    //湿度进度条

  if (Weather.temp > BigA)BarAFill = spr.alphaBlend((Weather.temp - BigA) / (MaxA - BigA) * 255.0, RedA, colorC); else BarAFill = colorC;
  if (Weather.temp < SmlA)BarAFill = spr.alphaBlend((SmlA - Weather.temp) / (SmlA - MinA) * 255.0, BluA, colorC);
  spr.fillRoundRect(70, 3, int((Weather.temp - MinA) / (MaxA - MinA) * 100), 11, 4, BarAFill);          //进度条A填充
  if (Weather3[0].humidity > BigB)BarBFill = spr.alphaBlend((Weather3[0].humidity - BigB) / (MaxB - BigB) * 255.0, RedB, colorC); else BarBFill = colorC;
  if (Weather3[0].humidity < SmlB)BarBFill = spr.alphaBlend((SmlB - Weather3[0].humidity) / (SmlB - MinB) * 255.0, BluB, colorC);
  spr.fillRoundRect(70, 28, int((Weather3[0].humidity - MinB) / (MaxB - MinB) * 100), 11, 4, BarBFill); //进度条B填充

  spr.pushSprite(0, 187);                             //显示到屏幕上
  spr.deleteSprite();                                 //删除雪碧精灵
  //-----------------------------显示底部日期--------------------------------
  spr.createSprite(240, 25);                          //创建雪碧精灵
  spr.pushImage(0, -250, 240,  280, background);      //显示背景图
  spr.setTextDatum(TC_DATUM);
  GGBond(120, 5, XiaoTuTi20, lowDate, 0XFFFF, Weather3[0].date.substring(0, 4) + "年" + Weather3[0].date.substring(5, 7) + "月" + Weather3[0].date.substring(8, 10) + "日"); //底部时间
  spr.setTextDatum(TL_DATUM);
  spr.pushSprite(0, 250);                             //显示到屏幕上
  spr.deleteSprite();                                 //删除雪碧精灵
}
