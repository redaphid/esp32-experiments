#include <Arduino.h>
#include <FastLED.h>
#define J9 22
#define J11 23

#define SOFT_LED_CHECK 23
#define NUM_LEDS 30

CRGB leds[NUM_LEDS];
#define DATA_PIN 22
void setup()
{
  pinMode(DATA_PIN, OUTPUT);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(SOFT_LED_CHECK, OUTPUT);
}

void loop()
{

  // if (digitalRead(J9) == HIGH)
  // {
  static uint8_t hue = 0;
  FastLED.showColor(CHSV(hue++, 255, 255));
  delay(10);
  // }
  // else
  // {
  //   digitalWrite(J11, LOW);

  // }
}
