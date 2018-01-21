#ifndef bubbleCounter_h
#define bubbleCounter_h

#include <Arduino.h>

class bubbleCounter
{
public:
  bubbleCounter(int pinNo);
  void run();
  //int pinVal();
  int threshold = 70;
  unsigned int timeBetween[10];
  // int State = 0;
  bool rollTimeState = 0;
  unsigned long nextRollTime = 0;
  int BPH = 0;

private:
  void BPHCalc();
  unsigned long lastBubbleTime = 0;

  bool previousBubbleState;
  int bubblePin;
  //void rollingAverage(double hours);

  //ool lastBubbleState = false;
  unsigned long debounceTime = 0;
};

// the #include statment and code go here...

#endif