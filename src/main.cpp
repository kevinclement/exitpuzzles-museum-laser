#include <Arduino.h>
#include "EEPROM.h"
#include "SerialManager.h"
#include "Logic.h"
#include "BluetoothSerial.h"

// Globals
int  FOO_VAR;                  // some foo desc
int  FOO_VAR_ADDR = 0;         // where to store foo in eeprom

Logic logic;
BluetoothSerial SerialBT;

char CRLF[] = "\r\n";

void setup() {
  Serial.printf("Museum Laser Controller by kevinc...\n");

  logic.setup();
  pinMode(17, OUTPUT);

//  readStoredVars();
//  sm.printHelp();
//  printVariables();

  SerialBT.begin("FooBTName"); //Bluetooth device name

}

void p(char *fmt, ...){
    char buf[128];     // resulting string limited to 128 chars
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, 128, fmt, args);
    va_end(args);

    // print to serial
    Serial.print(buf);

    // print to bluetooth if available
    SerialBT.print(buf);
}

void printVariables() { 
  p(CRLF);   
  p("Current Variables:%s", CRLF);
  p("  foo:  %d%s", FOO_VAR, CRLF);
}

void readStoredVars() {
  EEPROM.begin(64); // don't need a big size

  //EEPROM.get(FOO_VAR_ADDR, FOO_VAR);
}

void handleMessage(String msg) {
  Serial.print("got '");
  Serial.print(msg);
  Serial.println("' command");

  String command = msg;
  int value = -1;

  // check if we need to split on space for advance commands
  for (int i = 0; i <= msg.length(); i++) {
      if (msg.charAt(i) == ' ') {         
          command = msg.substring(0, i);
          value = msg.substring(i+1, msg.length()).toInt();
      }
  }
 
  if (command == "enable") {
    p("enabling device to drop now...%s", CRLF);
    //ENABLED = true;
  }
  else if (command == "disable") {
    p("disabling device now...%s", CRLF);
    //ENABLED = false;
  }
  else if (command == "drop") {
    //FORCE_DROP = true;
    p("dropping bottom now...%s", CRLF);
  }
  else if (command == "threshold") {
    p("setting threshold to '%d'...%s", value, CRLF);
    // LIGHT_THRESHOLD = value;
    // EEPROM.put(LIGHT_THRESHOLD_ADDR, value);
    // EEPROM.commit();    
  }
  else if (command == "status") {
    //printVariables();
  }
  else if (command == "reset") {
    ESP.restart();    
  } else {
    int str_len = command.length() + 1; 
    char char_array[str_len];
    command.toCharArray(char_array, str_len);
    p("unknown command: %s%s", char_array, CRLF);
  } 
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