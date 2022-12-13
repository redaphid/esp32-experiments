#include <Arduino.h>
#include <string>
#include <BLEDevice.h>

typedef void onDeviceFoundCallback(BLEAdvertisedDevice device);

void scanForBleDevices (onDeviceFoundCallback callback) {
  BLEScan *pBLEScan;
  pBLEScan = BLEDevice::getScan();
  pBLEScan->setActiveScan(true);
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->start(1, EndScanCallback, false);
}
