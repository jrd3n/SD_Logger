#ifndef Logger_h
#define Logger_h

#include <Arduino.h>

class Logger
{
public:
  Logger(int *Column1);
  void record();
  void pause();
  void stop();
  void begin();

  void run();

  int interval = 1000;

private:
  int _pin;

};

#endif