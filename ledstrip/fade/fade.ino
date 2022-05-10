#include <FastLED.h>
#define NUM_LEDS 90
#define DATA_PIN 6
CRGB leds[NUM_LEDS];
void setup() { 
        LEDS.addLeds<, WS2812B, RGB>(leds, NUM_LEDS);
}

uint16_t gHue = 0;
uint8_t  gHueDelta = 3;

void loop() { 
        leds[0] = 0xFF0000; 
        FastLED.show(); 
        delay(300); 
}
