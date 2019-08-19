#include "Arduino.h"
#include "consts.h"
#include "Logic.h"
#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

SerialManager::SerialManager(Logic &logic)
: _logic(logic)
{  
}

void SerialManager::setup() {
  Serial.begin(115200);

  Serial.printf("Museum Laser Controller by kevinc...\n");

  // set read timeout to something really low so we don't hang
  //Serial.setTimeout(10);

  while (!Serial); // Wait untilSerial is ready 

  // Bluetooth device name
  SerialBT.begin("ExitMuseumLaser");
}

void SerialManager::print(const char *fmt, ...) {
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

void SerialManager::handle() {
    // read bluetooth messages
    readAnyBluetoothMessage();

    // read serial messages
    readAnySerialMessage();
}

void SerialManager::readAnyBluetoothMessage() {
  if (!SerialBT.available()) {
    return;
  }

  // read and handle message from bluetooth
  String str = SerialBT.readStringUntil('\n');
  handleMessage(str);
}

void SerialManager::readAnySerialMessage() {
  if (!Serial.available()) {
    return;
  }

  // read and handle message from serial
  String str = Serial.readStringUntil('\n');
  handleMessage(str);
}

void SerialManager::handleMessage(String msg) {
  Serial.print("got '");
  Serial.print(msg);
  Serial.println("' command");

  String command = msg;

  if (command == "enable") {
    print("turning on laser...%s", CRLF);
    _logic.enable();
  }
  else if (command == "disable") {
    print("turning off laser...%s", CRLF);
    _logic.disable();
  }
  else if (command == "status") {
    _logic.printVariables();
  }
  else if (command == "reset") {
    ESP.restart();
  } else {
    int str_len = command.length() + 1; 
    char char_array[str_len];
    command.toCharArray(char_array, str_len);
    print("unknown command: %s%s", char_array, CRLF);
  } 
}

void SerialManager::printHelp() {
  Serial.println("Available commands:");
  Serial.println("  enable         - turns laser on");
  Serial.println("  disable        - turns laser off");  
  Serial.println("  status         - prints the status of the device variables");
  Serial.println("  reset          - software reset the device");
}