#include <Arduino.h>
#include <BLEDevice.h>

int lerp(int a, int b, float f)
{
  return a + f * (b - a);
}

class BleScanner extends BLEAdvertisedDeviceCallbacks
{
  BLEScan *pBLEScan;
  int maxRssi = -70;
  int strength = 0;
  double distance = 0;
  std::string name = "";

  double rssiToDistance(int rssi)
  {
    static uint8_t hue = 0;
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
  void onResult(BLEAdvertisedDevice advertisedDevice)
  {
    name = advertisedDevice.getName();
    if (name[0] == 'M')
    {
      auto rssi = advertisedDevice.getRSSI();
      this->maxRssi = max(maxRssi, rssi);
    }
  }

  void scanForBleDevices()
  {
    pBLEScan = BLEDevice::getScan();
    this->pBLEScan->setActiveScan(true);
    this->pBLEScan->setInterval(100);
    this->pBLEScan->setWindow(99);
    this->pBLEScan->setAdvertisedDeviceCallbacks(this);
    this->pBLEScan->start(1, this, false);
  }

  void advertiseBle()
  {
    BLEServer *pServer = BLEDevice::createServer();
    BLEService *pService = pServer->createService("4fafc201-1fb5-459e-8fcc-c5c9c331914b");
    BLECharacteristic *pCharacteristic = pService->createCharacteristic(
        BLEUUID("beb5483e-36e1-4688-b7f5-ea07361b26a8"),
        BLECharacteristic::PROPERTY_READ |
            BLECharacteristic::PROPERTY_WRITE);

    pCharacteristic->setValue({0, 0, (char)254});
    pService->start();
    pServer->getAdvertising()->start();
  }

  void setup()
  {

    BLEDevice::init("");
    scanForBleDevices();
    advertiseBle();
  }
s
}
