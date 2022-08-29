#ifndef _G_TFT_eSPI_H
#define _G_TFT_eSPI_H

//#include <TFT_eSPI.h>

#include "Imgs/img_weather.h"   //天气图片
#include "Imgs/img_background.h"//背景图片

#include "Fonts/wendao.h"       //时间字体
#include "Fonts/XiaoTuTi20.h"   //小字体
#include "Fonts/XiaoTuTi25.h"   //中字体
#include "Fonts/XiaoTuTi28.h"   //大字体

TFT_eSPI tft = TFT_eSPI();
TFT_eSprite spr = TFT_eSprite(&tft);

void GTFT() {
  tft.init();                   //屏幕初始化
  tft.setRotation(TFTRotation); //设置屏幕方向
  tft.setSwapBytes(true);       //要显示图片必须启用
  spr.setSwapBytes(true);       //要显示图片必须启用

  tft.pushImage(0, 0, 240, 280, background);
}

#endif
