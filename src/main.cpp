#include <Arduino.h>
#include <string>
#include "heltec.h"
// using namespace std;

SSD1306Wire* oled;
void setup()
{
  Heltec.begin(true /* DisplayEnable Enable */, false /* LoRa Disable */, true /* Serial Enable */);
  Heltec.display->setContrast(255);
  oled = Heltec.display;
}

int progress = 0;
void loop()
{
  progress++;
  if (progress > 100)
  {
    progress = 0;
  }
  oled->clear();
  oled->drawString(0, 0, "o hi there rave fam");
  oled->drawProgressBar(0, 20, 128, 10, progress);
  oled->display();
  delay(10);
}
