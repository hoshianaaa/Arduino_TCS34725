#include <Wire.h>
#include "Adafruit_TCS34725.h"

// Pick analog outputs, for the UNO these three work well
// use ~560  ohm resistor between Red & Blue, ~1K for green (its brighter)
#define redpin 3
#define greenpin 5
#define bluepin 6
// for a common anode LED, connect the common pin to +5V
// for common cathode, connect the common to ground

// set to false if using a common cathode LED
#define commonAnode true

// our RGB -> eye-recognized gamma color
byte gammatable[256];

//y_min = {1000, 


Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setup() {
  Serial.begin(9600);
 // Serial.println("Color View Test!");

  if (tcs.begin()) {
  //  Serial.println("Found sensor");
  } else {
  //  Serial.println("No TCS34725 found ... check your connections");
    while (1); // halt!
  }
  
  // use these three pins to drive an LED
  pinMode(redpin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  pinMode(bluepin, OUTPUT);
  
  // thanks PhilB for this gamma table!
  // it helps convert RGB colors to what humans see
  for (int i=0; i<256; i++) {
    float x = i;
    x /= 255;
    x = pow(x, 2.5);
    x *= 255;
      
    if (commonAnode) {
      gammatable[i] = 255 - x;
    } else {
      gammatable[i] = x;      
    }
    //Serial.println(gammatable[i]);
  }
}


void loop() {
  uint16_t clear, red, green, blue;

  tcs.setInterrupt(false);      // turn on LED

  delay(60);  // takes 50ms to read 
  
  tcs.getRawData(&red, &green, &blue, &clear);

  tcs.setInterrupt(true);  // turn off LED
  
 // Serial.print(""); Serial.print(clear);
  Serial.print(" "); Serial.print(red);
  Serial.print(" "); Serial.print(green);
  Serial.print(" "); Serial.print(blue);
  Serial.print(" ");


  char color = 'n';


    if (red < 45 && green < 45 && blue > 25){
    color = 'b';
    Serial.println(color);
  }

    else if (red > 50 && green > 30){
    color = 'y';
    Serial.println(color);
  }
    else if (red > 35 && green  > 25 && blue > 15){
    color = 'r';
    Serial.println(color);
  }
  else 
  {
    Serial.println("n");
  }

  
  // Figure out some basic hex code for visualization
  uint32_t sum = clear;
  float r, g, b;
  r = red; r /= sum;
  g = green; g /= sum;
  b = blue; b /= sum;
  r *= 256; g *= 256; b *= 256;
 // Serial.print("\t");
 // Serial.print((int)r, HEX); Serial.print((int)g, HEX); Serial.print((int)b, HEX);
 // Serial.println();

  //Serial.print((int)r ); Serial.print(" "); Serial.print((int)g);Serial.print(" ");  Serial.println((int)b );

 // analogWrite(redpin, gammatable[(int)r]);
 // analogWrite(greenpin, gammatable[(int)g]);
 // analogWrite(bluepin, gammatable[(int)b]);

 /*
  * 
  * blue 
  * 25 27 23
  * 23 26 23
  * 20 24 21
  * 27 29 25
  * 26 29 25
  * 
  * yellow
  * 51 39 21
  * 48 37 19
  * 50 39 21
  * 51 40 22
  * 49 38 20
  * 
  * none 
  * 47 39 26
  * 49 39 26
  * 49 39 26
  * 49 39 26
  * 50 39 25
  * 
  * red
  * 32 26 19
  * 29 23 17
  * 31 25 18
  */

  
}
