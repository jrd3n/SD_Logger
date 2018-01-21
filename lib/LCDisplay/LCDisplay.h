#ifndef LCDisplay_h
#define LCDisplay_h

#include <Arduino.h>

class LCDisplay
{
  public:
    LCDisplay();
    void begin();
    void run(String LineOne, String LineTwo);
    void run(String TopLeft, String TopRight,String BottomLeft,String BottomRight);

  private:
    String PrevousLine1;
    String PrevousLine2;
    int refreshRate = 100;
    unsigned long nextRefresh = 0;
    String consonate(String Left,String Right);
};

#endif