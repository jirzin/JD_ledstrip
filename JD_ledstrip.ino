#include <TimerOne.h>
#include "LPD6803.h"

int dataPin = 2;
int clockPin = 3;

int pixelCount = 60; // little bigger than actual length for complete fade out

LPD6803 strip = LPD6803(pixelCount, dataPin, clockPin);


int len = 12; // length of light streak 
int streakColors[12][3] = {
  {63, 14, 0},  // 0
  {63, 7, 0},
  {55, 3, 0},
  {25, 2, 0},
  {15, 1, 0},
  {10, 0, 0},
  {7, 0, 0},
  {5, 0, 0},
  {3, 0, 0},
  {2, 0, 0},
  {1, 0, 0},
  {0, 0, 0} // end state = black
};

typedef enum {LISTENING, STREAK} ProgState;
ProgState ps = STREAK;

void setup() {
  strip.setCPUmax(100);
  strip.begin();
  strip.show();
}

void loop() {
  switch (ps) {
    case LISTENING:
      break;
    case STREAK:
      colorWipe(20);
      delay(1000);
      ps = LISTENING;
      break;
  }
}

void colorWipe(uint8_t wait) {
  for (int i = 0; i < strip.numPixels(); i++) {

    for (int l = 0; l < len; l++) {
      strip.setPixelColor(i - l, Color(streakColors[l][0], streakColors[l][1], streakColors[l][2]));
    }

    strip.show();
    delay(wait);
  }
}

unsigned int Color(byte R, byte G, byte B)
{
  //Take the lowest 5 bits of each value and append them end to end
  return ( ((unsigned int)B & 0x1F ) << 10 | ((unsigned int)R & 0x1F) << 5 | (unsigned int)G & 0x1F);
}

