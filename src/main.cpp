#include <Arduino.h>
#define J9 22

void setup()
{

  pinMode(J9, OUTPUT);
}

void loop()
{
  digitalWrite(J9, LOW);
  delay(100);
  digitalWrite(J9, HIGH);
  delay(100);
}
