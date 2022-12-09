#include <Arduino.h>
#include <string>
#include <FastLED.h>
#include <BLEDevice.h>
#include "heltec.h"
#define J9 22
#define J11 23

#define SOFT_LED_CHECK 23
#define NUM_LEDS 10

CRGB leds[NUM_LEDS];
#define DATA_PIN 22

OLEDDisplay *oled;

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) {
      oled->drawString(0, 30, "BLE Advertised Device found: ");
      oled->drawString(0, 40, advertisedDevice.toString().c_str());
    }
};

void scanForBleDevices()
{
  BLEDevice::init("");
  BLEScan *pBLEScan = BLEDevice::getScan();
  pBLEScan->setActiveScan(true);
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  BLEScanResults foundDevices = pBLEScan->start(5, false);
  oled->drawString(0, 0, "Devices found: ");
  oled->drawString(0, 10, std::to_string((foundDevices.getCount())).c_str());
  oled->drawString(0, 20, "Scan done!");
  pBLEScan->clearResults();
  delay(2000);
}

void setup()
{
  pinMode(DATA_PIN, OUTPUT);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(SOFT_LED_CHECK, OUTPUT);
  Heltec.begin(true /* DisplayEnable Enable */, false /* LoRa Disable */, true /* Serial Enable */);
  Heltec.display->setContrast(255);
  oled = Heltec.display;
}

void loop()
{
  oled->clear();
  scanForBleDevices();
  oled->display();
  static uint8_t hue = 0;
  FastLED.showColor(CHSV(hue++, 255, 255));
  delay(100);
}
