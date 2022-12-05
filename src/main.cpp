#include <Arduino.h>
#define J9 22
#define J11 23
void setup()
{

  pinMode(J9, OUTPUT);
  pinMode(J11, OUTPUT);
}

void loop()
{
  digitalWrite(J9, LOW);

  digitalWrite(J11, LOW);
  delay(10);
  digitalWrite(J11, HIGH);
  digitalWrite(J9, HIGH);
  delay(50);
}
