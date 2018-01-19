#ifndef bubbleCounter_h
#define bubbleCounter_h

#include <Arduino.h>

class bubbleCounter
{
public:
  bubbleCounter(int pinNo);
  void run();
  unsigned int count = 0;
  int BPH();
  int threshold = 70;
  unsigned int min5intervals[12];

private:
  int bubblePin;
  unsigned long nextRollTime = 0;
  bool previousBubbleState= false;
  unsigned long debounceTime;
};

#endif

