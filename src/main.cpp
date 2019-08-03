#include <Arduino.h>
#include "SerialManager.h"
#include "logic.h"
#include "BluetoothSerial.h"

// Globals
Logic logic;
BluetoothSerial SerialBT;

void setup() {
  Serial.printf("Museum Laser Controller by kevinc...\n");

  logic.setup();

  pinMode(17, OUTPUT);

//  sm.printHelp();
//  printVariables();

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

    // read bluetooth messages
    //readAnyBluetoothMessage();

    // read serial messages
    //readAnySerialMessage();
}