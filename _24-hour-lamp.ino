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

byte black[] = {0, 0, 0};
byte a[] = {23,0,0};
byte b[] = {20,0,0};
byte c[] = {18,0,0};
byte d[] = {15,0,0};
byte e[] = {20,0,0};
byte f[] = {25,0,0};
byte g[] = {0,0,55};
byte h[] = {0,205,0};
byte i[] = {246,0,0};
byte j[] = {0,179,0};
byte k[] = {0,0,150};
byte l[] = {0,125,0};
byte m[] = {105,0,0};
byte n[] = {0,91, 0};
byte o[] = {0, 0,83};
byte p[] = {0, 82, 0};
byte q[] = {81, 0, 0};
byte r[] = {0,97, 0};
byte s[] = {0, 0,116};
byte t[] = {0,90, 0};
byte u[] = {65, 0, 0};
byte v[] = {0,50, 0};
byte w[] = {37, 0, 0};
byte x[] = {0,25, 0};

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
  sunrise();
  strip.show();
}

uint32_t getColorByTime(int hours , int minutes, int seconds){
  byte* cA;
  byte* cB;
  byte interpolated[3];
  
  uint32_t color;
    
  switch(hours){
    case 0:
      cA = (byte*)a;
      cB = (byte*)b;
      break;
    case 1:
      cA = (byte*)b;
      cB = (byte*)c;
     break;
    case 2:
      cA = (byte*)c;
      cB = (byte*)d;
      break;
      case 3:
      cA = (byte*)d;
      cB = (byte*)e;
      break;
    case 4:
      cA = (byte*)e;
      cB = (byte*)f;
      break;
    case 5:
      cA = (byte*)f;
      cB = (byte*)g;
      break;
      case 6:
      cA = (byte*)g;
      cB = (byte*)h;
      break;
    case 7:
      cA = (byte*)h;
      cB = (byte*)i;
      break;
    case 8:
      cA = (byte*)i;
      cB = (byte*)j;
      break;
      case 9:
      cA = (byte*)j;
      cB = (byte*)k;
      break;
    case 10:
      cA = (byte*)k;
      cB = (byte*)l;
      break;
    case 11:
      cA = (byte*)l;
      cB = (byte*)m;
      break;
      case 12:
      cA = (byte*)m;
      cB = (byte*)n;
      break;
      case 13:
      cA = (byte*)n;
      cB = (byte*)o;
      break;
      case 14:
      cA = (byte*)o;
      cB = (byte*)p;
      break;
    case 15:
      cA = (byte*)p;
      cB = (byte*)q;
      break;
    case 16:
      cA = (byte*)q;
      cB = (byte*)r;
      break;
    case 17:
      cA = (byte*)r;
      cB = (byte*)s;
      break;
    case 18:
      cA = (byte*)s;
      cB = (byte*)t;
      break;
    case 19:
      cA = (byte*)t;
      cB = (byte*)u;
      break;
      case 20:
      cA = (byte*)u;
      cB = (byte*)v;
      break;
    case 21:
      cA = (byte*)v;
      cB = (byte*)w;
      break;
    case 22:
      cA = (byte*)w;
      cB = (byte*)x;
      break;
      case 23:
      cA = (byte*)x;
      cB = (byte*)a;
      break;
       
    default:
      cA = (byte*)black;
      cB = (byte*)black;
  }
  
  // use 60 instead of 59 so that it never quite gets to the final color in this hour.
  // the true final color will happen on the first minute of the next hour
  // if you use 59 you'll see two consecutive minutes that are identical
  interpolated[0] = map(minutes, 0, 60, cA[0], cB[0]);  //red channel
  interpolated[1] = map(minutes, 0, 60, cA[1], cB[1]);  //green channel
  interpolated[2] = map(minutes, 0, 60, cA[2], cB[2]);  //blue channel
  return strip.Color(interpolated[0],interpolated[1],interpolated[2]);
}

void getColorByTimeRange(double percentOfDay){
  
  
}

void sunrise() {
  uint32_t color;
  color = getColorByTime(hour(), minute(),second());
  for(int i=0; i<NUMPIX; i++) strip.setPixelColor(i,color);
}



void solidColor(uint32_t color){
  for(int i=0; i<strip.numPixels(); i++) strip.setPixelColor(i,color);
}


