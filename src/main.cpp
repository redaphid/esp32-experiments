#include <Arduino.h>
#include <string>
#include <FastLED.h>
#include <BLEDevice.h>
#include "heltec.h"

#define NUM_LEDS 20

CRGB leds[NUM_LEDS];
#define DATA_PIN 22

OLEDDisplay *oled;
BLEScan *pBLEScan;

int maxRssi = -70;
int strength = 0;
double distance = 0;
std::string name = "";

static uint8_t hue = 0;
int lerp(int a, int b, float f)
{
  return a + f * (b - a);
}


double rssiToDistance(int rssi)
{
  int txPower = -59; // hard coded power value. Usually ranges between -59 to -65

  if (rssi == 0)
  {
    return -1.0; // if we cannot determine accuracy, return -1.
  }

  double ratio = rssi * 1.0 / txPower;
  if (ratio < 1.0)
  {
    return pow(ratio, 10);
  }
  else
  {
    double accuracy = (0.89976) * pow(ratio, 7.7095) + 0.111;
    return accuracy;
  }
}

class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks
{
  void onResult(BLEAdvertisedDevice advertisedDevice)
  {
    name = advertisedDevice.getName();
    if (name[0] == 'M')
    {
      auto rssi = advertisedDevice.getRSSI();
      maxRssi = max(maxRssi, rssi);
    }
  }
};

void EndScanCallback(BLEScanResults results)
{
  distance = lerp(distance, rssiToDistance(maxRssi), 0.2);
  if (distance > 50) distance = 50;

  strength = map(distance * -1, -50, -1, 0, 100);
  maxRssi = -100;
  pBLEScan->start(1, EndScanCallback, false);
}
void scanForBleDevices()
{
  pBLEScan = BLEDevice::getScan();
  pBLEScan->setActiveScan(true);
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->start(1, EndScanCallback, false);
}

void advertiseBle()
{
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService("4fafc201-1fb5-459e-8fcc-c5c9c331914b");
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
      BLEUUID("beb5483e-36e1-4688-b7f5-ea07361b26a8"),
      BLECharacteristic::PROPERTY_READ |
          BLECharacteristic::PROPERTY_WRITE);


  pCharacteristic->setValue({0,0,(char)254});
  pService->start();
  pServer->getAdvertising()->start();
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
  advertiseBle();
}

void loop()
{
  oled->display();

  int ledsToLight = map(strength, 0, 100, 0, NUM_LEDS);
  int progress = strength;

  hue = map(strength, 0,100,0, 255 - (NUM_LEDS*5));
  oled->clear();
  oled->drawString(0, 0, String(distance));
  oled->drawProgressBar(0, 20, 128, 10, progress);
  for (int i = 0; i < NUM_LEDS; i++)
  {
    if (i < ledsToLight)
    {
      leds[i] = CHSV(hue+=5, 255, 255);
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
