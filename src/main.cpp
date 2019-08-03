#include <Arduino.h>

void setup() {
  Serial.begin(115200);
  Serial.printf("Museum Laser Controller by kevinc...\n");
  pinMode(17, OUTPUT);
}

void loop() {
    digitalWrite(17, HIGH);
}