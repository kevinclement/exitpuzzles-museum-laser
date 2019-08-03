#include "Arduino.h"
#include "Logic.h"

SerialManager::SerialManager(Logic &logic)
: _logic(logic)
{  
}

void SerialManager::setup() {
  // set read timeout to something really low so we don't hang
  Serial.setTimeout(10);

  while (!Serial); // Wait untilSerial is ready 
}

void SerialManager::teardown() {
  // noop: I actually want to keep this working
}

void SerialManager::handle() {
  
}

void SerialManager::printHelp() {
  Serial.println("Available commands:");
  Serial.println("  enable         - turns device on");
  Serial.println("  foo N          - set foo to value N");
  Serial.println("  status         - prints the status of the device variables");
  Serial.println("  reset          - software reset the device");
}