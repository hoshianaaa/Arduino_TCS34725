#include <Wire.h>
#include "Adafruit_TCS34725.h"
#define DEBUG 0
#define MODE 1

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
char GetColor();

void setup() {
  Serial.begin(9600);

  //カラーセンサセットアップ:失敗で無限ループ
  if (tcs.begin()) {
    if (DEBUG)Serial.println("Found color sensor");
  } else {
    if (DEBUG)Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }


}


void loop() {
  if(MODE == 1){
    Serial.write(255);
    Serial.write(GetColor());
  }
}



char GetColor() {
  
  uint16_t clear, red,green, blue;

  tcs.getRawData(&red, &green, &blue, &clear);

  char color;
  if (red < 45 && green < 45 && blue > 25)color = 'b';
  else if (red > 50 && green > 30)color = 'y';
  else if (red > 35 && green  > 25 && blue > 15)color = 'r';
  else color = 'n';
  if (DEBUG) {
    Serial.print(" "); Serial.print(red);
    Serial.print(" "); Serial.print(green);
    Serial.print(" "); Serial.print(blue);
    Serial.print(" "); Serial.println(color);
  }
  return color;
}
