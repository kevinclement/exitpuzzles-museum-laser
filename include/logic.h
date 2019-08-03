#pragma once

#include "SerialManager.h"

class Logic {
public:
  Logic();
  SerialManager serial;

  void setup();

private:
  void readStoredVariables();
  void printVariables();
};

