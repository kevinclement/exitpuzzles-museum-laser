#pragma once

#include "SerialManager.h"

class Logic {
public:
  Logic();
  SerialManager serial;

  void setup();
  void handle();
  void enable();
  void disable();
  void printVariables();

private:
  void readStoredVariables();
  
};

