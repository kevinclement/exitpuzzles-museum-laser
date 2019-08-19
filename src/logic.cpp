#include "Arduino.h"
#include "EEPROM.h"
#include "logic.h"
#include "consts.h"

#define LASER_ENABLE_PIN 17

int  FOO_VAR;                  // some foo desc
int  FOO_VAR_ADDR = 0;         // where to store foo in eeprom
bool ENABLED = false;

Logic::Logic() 
  : serial(*this)
{
}

void Logic::setup() {
  serial.setup();
  serial.printHelp();
  readStoredVariables();
  printVariables();

  pinMode(LASER_ENABLE_PIN, OUTPUT);
}

void Logic::handle() {
  serial.handle();

  // enable/disable laser
  digitalWrite(LASER_ENABLE_PIN, ENABLED ? HIGH : LOW);
}

void Logic::enable() {
  ENABLED = true;
}

void Logic::disable() {
  ENABLED = false;
}

void Logic::readStoredVariables() {
  EEPROM.begin(64); // don't need a big size
  //EEPROM.get(FOO_VAR_ADDR, FOO_VAR);
}

void Logic::printVariables() { 
  serial.print(CRLF);
  serial.print("Current Variables:%s", CRLF);
  serial.print("  foo:  %d%s", FOO_VAR, CRLF);
}