#include "Arduino.h"
#include "Logic.h"

Logic::Logic() 
  : serial(*this)
{
}

void Logic::setup() {
    serial.setup();
}