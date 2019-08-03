#pragma once

class Logic;

class SerialManager {
public:
  SerialManager(Logic &logic);
  void setup();
  void handle();
  void teardown();
  void printHelp();

private:
  Logic &_logic;
};

