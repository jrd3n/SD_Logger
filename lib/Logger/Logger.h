#ifndef Logger_h
#define Logger_h

#include <Arduino.h>

class Logger
{
public:
  Logger();
  void record(String title);
  //void pause();
  //void stop();
  void begin();

  void run(double logVal);

  int interval = 1000;

  String timeLong();
  String timeShort();

private:
  bool recording = 0;
  String timeFileName();
  uint8_t sec, min, hour, day, month;
  uint16_t year;
  unsigned long nextLogTime = 0;

  String logFile = "test.csv";

  String tenBelow(int input);

  unsigned int DumpNumber = 0;
  String dumpfile[];
  //int _pin;
};

#endif