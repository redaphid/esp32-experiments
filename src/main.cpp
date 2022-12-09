#include <Arduino.h>
#include <FastLED.h>
#define J9 22
#define J11 23

#define NUM_LEDS 10
#define DATA_PIN 22
#define SOFT_LED_CHECK 2
CRGB leds[NUM_LEDS];
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
    leds[0] = CRGB::Red;
    FastLED.show();
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(SOFT_LED_CHECK, HIGH);

    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(SOFT_LED_CHECK, LOW);
    leds[0] = CRGB::Black;
    FastLED.show();
    delay(1000);
  // }
  // else
  // {
  //   digitalWrite(J11, LOW);

  // }
}
