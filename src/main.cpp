#include <Arduino.h>
#include "SerialManager.h"
#include "logic.h"
#include "BluetoothSerial.h"

// Globals
Logic logic;
BluetoothSerial SerialBT;

void setup() {
  logic.setup();

  pinMode(17, OUTPUT);

  SerialBT.begin("FooBTName"); //Bluetooth device name
}

// void readAnyBluetoothMessage() {
//   if (!SerialBT.available()) {
//     return;
//   }

//   // read and handle message from bluetooth
//   String str = SerialBT.readStringUntil('\n');
//   handleMessage(str);
// }

// void readAnySerialMessage() {
//   if (!Serial.available()) {
//     return;
//   }

//   // read and handle message from serial
//   String str = Serial.readStringUntil('\n');
//   handleMessage(str);
// }

void loop() {
    digitalWrite(17, HIGH);

    logic.handle();
}