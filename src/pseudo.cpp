#include <Arduino.h>
#include <string>
#include <FastLED.h>
#include <BLEDevice.h>
#include "heltec.h"

void setup()
{
  setupBLE();
  broadcastBLE(bleName);
  scanBLE([](BLEAdvertisedDevice advertisedDevice) {
    auto name = advertisedDevice.getName();
    if (name[0] == 'M')
    {
      auto rssi = advertisedDevice.getRSSI();
      maxRssi = max(maxRssi, rssi);
    }
  });
  setupDisplay();
}

void loop()
{

}
