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

void handleMessage(String msg) {
//   Serial.print("got '");
//   Serial.print(msg);
//   Serial.println("' command");

//   String command = msg;
//   int value = -1;

//   // check if we need to split on space for advance commands
//   for (int i = 0; i <= msg.length(); i++) {
//       if (msg.charAt(i) == ' ') {         
//           command = msg.substring(0, i);
//           value = msg.substring(i+1, msg.length()).toInt();
//       }
//   }
 
//   if (command == "enable") {
//     p("enabling device to drop now...%s", CRLF);
//     //ENABLED = true;
//   }
//   else if (command == "disable") {
//     p("disabling device now...%s", CRLF);
//     //ENABLED = false;
//   }
//   else if (command == "drop") {
//     //FORCE_DROP = true;
//     p("dropping bottom now...%s", CRLF);
//   }
//   else if (command == "threshold") {
//     p("setting threshold to '%d'...%s", value, CRLF);
//     // LIGHT_THRESHOLD = value;
//     // EEPROM.put(LIGHT_THRESHOLD_ADDR, value);
//     // EEPROM.commit();    
//   }
//   else if (command == "status") {
//     //printVariables();
//   }
//   else if (command == "reset") {
//     ESP.restart();    
//   } else {
//     int str_len = command.length() + 1; 
//     char char_array[str_len];
//     command.toCharArray(char_array, str_len);
//     p("unknown command: %s%s", char_array, CRLF);
//   } 
}

void readAnyBluetoothMessage() {
  if (!SerialBT.available()) {
    return;
  }

  // read and handle message from bluetooth
  String str = SerialBT.readStringUntil('\n');
  handleMessage(str);
}

void readAnySerialMessage() {
  if (!Serial.available()) {
    return;
  }

  // read and handle message from serial
  String str = Serial.readStringUntil('\n');
  handleMessage(str);
}

void loop() {
    digitalWrite(17, HIGH);

    // read bluetooth messages
    readAnyBluetoothMessage();

    // read serial messages
    readAnySerialMessage();
}