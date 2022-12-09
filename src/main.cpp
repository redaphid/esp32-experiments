#include <Arduino.h>
#include <string>
#include <FastLED.h>
#include <BLEDevice.h>
#include "heltec.h"
#define J9 22
#define J11 23

#define SOFT_LED_CHECK 23
#define NUM_LEDS 20

CRGB leds[NUM_LEDS];
#define DATA_PIN 22

OLEDDisplay *oled;
BLEScan *pBLEScan;

int maxRssi = -70;
int strength = 0;
static uint8_t hue = 0;

class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks
{
  void onResult(BLEAdvertisedDevice advertisedDevice)
  {
    auto rssi = advertisedDevice.getRSSI();
    maxRssi = max(maxRssi, rssi);
  }
};

void EndScanCallback(BLEScanResults results)
{
  pBLEScan->clearResults();
  strength = map(maxRssi, -100, -60, 0, 100);
  maxRssi = -100;
  pBLEScan->start(5, EndScanCallback);
}
void scanForBleDevices()
{
  pBLEScan = BLEDevice::getScan();
  pBLEScan->setActiveScan(true);
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->start(5, EndScanCallback);
}

void setup()
{
  pinMode(DATA_PIN, OUTPUT);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  pinMode(LED_BUILTIN, OUTPUT);
  Heltec.begin(true /* DisplayEnable Enable */, false /* LoRa Disable */, true /* Serial Enable */);
  Heltec.display->setContrast(255);
  oled = Heltec.display;

  BLEDevice::init("");
  scanForBleDevices();
}

void loop()
{
  oled->display();

  int ledsToLight = map(strength, 0, 100, 0, NUM_LEDS);
  int progress = strength;
  oled->clear();
  oled->drawString(0, 0, "RSSI: " + String(maxRssi));
  oled->drawProgressBar(0, 20, 128, 10, progress);
  for (int i = 0; i < NUM_LEDS; i++)
  {
    if (i < ledsToLight)
    {
      hue = (hue + 1) % 255;
      leds[i] = CHSV(hue, 255, 255);
    }
    else
    {
      leds[i] = CRGB::Black;
    }
  }
  FastLED.show();
  // FastLED.showColor(CHSV(hue++, 255, brightness));
  delay(10);
}
