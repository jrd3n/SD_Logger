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
  int pinVal();
  int threshold = 70;
  unsigned int min5intervals[12];

private:
  
  int bubblePin;
  void rollingAverage(double hours);
  unsigned long nextRollTime = 0;
  bool previousBubbleState;
  bool lastBubbleState = false;
  unsigned long debounceTime;
};

// the #include statment and code go here...

#endif

