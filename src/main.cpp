#include <Arduino.h>
#include <FastLED.h>
#include "heltec.h"
#define J9 22
#define J11 23

#define SOFT_LED_CHECK 23
#define NUM_LEDS 10

CRGB leds[NUM_LEDS];
#define DATA_PIN 22
uint8_t pikachu_width = 128;
uint8_t pikachu_height = 64;
uint8_t pikachu_bits[128*64];
void drawPikachu(OLEDDisplay *display)
{
for (int i = 0; i < 128*64; i++)
{
  pikachu_bits[i] = 255;
}
  display->drawXbm(0, 0, pikachu_width, pikachu_height, pikachu_bits);
}

void setup()
{
  pinMode(DATA_PIN, OUTPUT);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(SOFT_LED_CHECK, OUTPUT);
  Heltec.begin(true /* DisplayEnable Enable */, false /* LoRa Disable */, true /* Serial Enable */);
  Heltec.display->setContrast(255);
}

void loop()
{
  auto oled = Heltec.display;
  oled->clear();
  drawPikachu(oled);
  oled->display();


  // if (digitalRead(J9) == HIGH)
  // {
  static uint8_t hue = 0;
  FastLED.showColor(CHSV(hue++, 255, 255));
  delay(100);
  // }
  // else
  // {
  //   digitalWrite(J11, LOW);

  // }
}
