#include <Arduino.h>
#define J9 22
#define J11 23
void setup()
{
  pinMode(J9, INPUT);
  pinMode(J11, OUTPUT);
}

void loop()
{

  if (digitalRead(J9) == HIGH)
  {
    delay(100);
    digitalWrite(J11, HIGH);
    delay(100);
    digitalWrite(J11, LOW);
  }
  else
  {
    digitalWrite(J11, LOW);
  }
}
