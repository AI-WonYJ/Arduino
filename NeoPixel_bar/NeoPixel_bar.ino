#include <FastLED.h>

#define LED_PIN     7
#define NUM_LEDS    96
#define Delay       5
int Brightness = 250;

  CRGB leds[NUM_LEDS];

void setup() {

  FastLED.addLeds<WS2812, 7, GRB>(leds, NUM_LEDS);
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0, 0, 0);
  }
  FastLED.show();
  
}

void loop() {
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(Brightness, 0, 0);
    FastLED.show();
    delay(Delay);  
  }
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(Brightness, Brightness, 0);
    FastLED.show();
    delay(Delay);  
  }
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0, Brightness, 0);
    FastLED.show();
    delay(Delay);  
  }
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0, Brightness, Brightness);
    FastLED.show();
    delay(Delay);  
  }
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0, 0, Brightness);
    FastLED.show();
    delay(Delay);  
  }
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(Brightness, Brightness, Brightness);
    FastLED.show();
    delay(Delay);  
  }
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0, 0, 0);
    FastLED.show();
    delay(Delay);  
  }
  delay(100);
}







void Cycle() {
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(Brightness, 0, 0);
    FastLED.show();
    delay(Delay);  
  }
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(Brightness, Brightness, 0);
    FastLED.show();
    delay(Delay);  
  }
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0, Brightness, 0);
    FastLED.show();
    delay(Delay);  
  }
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0, Brightness, Brightness);
    FastLED.show();
    delay(Delay);  
  }
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0, 0, Brightness);
    FastLED.show();
    delay(Delay);  
  }
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(Brightness, Brightness, Brightness);
    FastLED.show();
    delay(Delay);  
  }
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0, 0, 0);
    FastLED.show();
    delay(Delay);  
  }
  delay(100);
}