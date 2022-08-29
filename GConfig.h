const int TFTRotation = 0;              //设置屏幕方向
const int TZone = 8;                    //时区，北京时间为UTC+8
const String UID = "24684337";          //哔哩哔哩UID
const String Key = "XXXXXXXXXXXXXXXXXX"; //心知天气私钥
const String City = "营口";              //城市拼音，汉字好像也彳亍
const char* ssid     = "Test";
const char* password = "12345677";

/*============以下是颜色设置============*/
uint16_t colorA = 0X148C;   //颜色A
uint16_t colorB = 0X2df2;   //颜色B
uint16_t colorC = 0Xa6b8;   //颜色C

uint16_t upCity = colorA;   //顶部城市
uint16_t upTemp = colorA;   //顶部时间
uint16_t loopWord = colorB; //循环文字

uint16_t timeNum = colorB;  //中间时间的数字
uint16_t timeColon = colorB;//中间时间的冒号

float MaxA = 50;            //进度条A最大
float MinA = -20;           //进度条A最小
float BigA = 35.0;          //进度条A大于变颜色
float SmlA = 0.0;           //进度条A小于变颜色
uint16_t BarAWord = colorB; //进度条A文字
uint16_t BarANumb = colorB; //进度条A数字
uint16_t BarASide = colorB; //进度条A边框
uint16_t BarAFill = colorC; //进度条A填充
uint16_t RedA = TFT_RED;    //进度条A大于时颜色
uint16_t BluA = TFT_BLUE;   //进度条A小于时颜色

float MaxB = 100;           //进度条B最大
float MinB = 0;             //进度条B最小
float BigB = 80;            //进度条B大于变颜色
float SmlB = 30;            //进度条B小于变颜色
uint16_t BarBWord = colorB; //进度条B文字
uint16_t BarBNumb = colorB; //进度条B数字
uint16_t BarBSide = colorB; //进度条B边框
uint16_t BarBFill = colorC; //进度条B填充
uint16_t RedB = TFT_RED;    //进度条B大于时颜色
uint16_t BluB = TFT_BLUE;   //进度条B小于时颜色

uint16_t lowDate = colorB;  //底部日期
