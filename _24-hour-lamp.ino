#include <Adafruit_NeoPixel.h>
#include <DS3232RTC.h>    //http://github.com/JChristensen/DS3232RTC
#include <Time.h>         //http://www.arduino.cc/playground/Code/Time
#include <Wire.h>
#define PIN 6
#define NUMPIX 61


// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIX, PIN, NEO_GRB + NEO_KHZ800);


// R, G, B, brightness, hours, minutes
unsigned int colors[][5] = {
  {255, 0, 0, 25, 0, 0},
  {255, 0, 0, 15, 3, 0},
  {255, 0, 0, 25, 5, 0},
  {0, 0, 255, 25, 6, 0},
  {0, 205, 0, 255, 7, 0},
  {246, 0, 0, 255, 8, 0},
  {0, 179, 0, 255, 9, 0},
  {0, 0, 150, 255, 10, 0},
  {0, 125, 0, 255, 11, 0},
  {105, 0, 0, 255, 12, 0},
  {0, 91, 0, 255, 13, 0},
  {0, 0, 83, 255, 14, 0},
  {0, 82, 0, 255, 15, 0},
  {81, 0, 0, 255, 16, 0},
  {0,97, 0, 255, 17, 0},
  {0, 0,116, 255, 18, 0},
  {0, 90, 0, 255, 19, 0},
  {65, 0, 0, 255, 20, 0},
  {0, 50, 0, 255, 21, 0},
  {37, 0, 0, 255, 22, 0},
  {0, 25, 0, 255, 23, 0},
  {255, 0, 0, 25, 24, 0}, //Make sure this is the same as the first line, becauze lazy
}


void setup() {
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  digitalWrite(A2, LOW);
  digitalWrite(A3, HIGH);
  setSyncProvider(RTC.get);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}


void loop() {
  for(int i=0; i<size(colors)-1; i++){
    unsigned int color_hour1 = colors[i][4];
    unsigned int color_min1 = colors[i][5];
    unsigned int color_hour2 = colors[i+1][4];
    unsigned int color_min2 = colors[i+1][5];
    if(hour() <= color_hour){
      unsigned int k1 = colors[i][3];
      unsigned int r1 = colors[i][0] * k1 / 255;
      unsigned int g1 = colors[i][1] * k1 / 255;
      unsigned int b1 = colors[i][2] * k1 / 255;
      unsigned int k2 = colors[i+1][3];
      unsigned int r2 = colors[i+1][0] * k2 / 255;
      unsigned int g2 = colors[i+1][1] * k2 / 255;
      unsigned int b2 = colors[i+1][2] * k2 / 255;
      break;
    }
  }
  unsigned int timespan = (color_hour2 - color_hour1) * 60 + (color_min2 - color_min1)
  unsigned int elapsed_time = (hour() - color_hour1) * 60 + (minute() - color_min1)
  unsigned int rout = map(elapsed_time, 0, timespan, r1, r2);
  unsigned int gout = map(elapsed_time, 0, timespan, g1, g2);
  unsigned int bout = map(elapsed_time, 0, timespan, b1, b2);
  solidColor(strip.color(rout, gout, bout));
  strip.show();
}


void solidColor(uint32_t color){
  for(int i=0; i<strip.numPixels(); i++) strip.setPixelColor(i, color);
}
