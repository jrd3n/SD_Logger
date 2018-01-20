#ifndef bubbleCounter_h
#define bubbleCounter_h

#include <Arduino.h>

class bubbleCounter
{
public:
  bubbleCounter(int pinNo);
  void run();
  unsigned int count = 0;
  unsigned int BPH();
  //int pinVal();
  int threshold = 70;
  unsigned int min5intervals[12];

  // int State = 0;
   bool rollTimeState = 0;
   unsigned long nextRollTime = 0;
private:
  bool previousBubbleState;
  int bubblePin;
  //void rollingAverage(double hours);
  

  //ool lastBubbleState = false;
  unsigned long debounceTime = 0;
  ;
};

// the #include statment and code go here...

#endif
