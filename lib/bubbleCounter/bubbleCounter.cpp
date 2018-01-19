#include <Arduino.h>
#include <bubbleCounter.h>

bubbleCounter::bubbleCounter(int pinNo)
{
    pinMode(pinNo, INPUT); // sets the pin mode

    bubblePin = pinNo; // makes the pin No avalible later on

    // Serial.println("ending the threshold analasis");
}

void bubbleCounter::run()
{
    bool bubbleState = analogRead(bubblePin) > threshold;
    
    bool debounce = debounceTime > millis();

    if (!previousBubbleState && bubbleState && !debounce)
    {
        debounceTime = millis() + 5; // start timmer
        previousBubbleState = HIGH; // once this timer starts, this if() is locked out
    }
    if (previousBubbleState && bubbleState && debounce) // 
    {
        debounceTime = millis() +2000; // start timmer to lock out this if() for 2 secs
        count++;
        rollingAverage();
    }
    if (previousBubbleState && !bubbleState && debounce)
    {
        debounceTime = millis() - 2000; // this minuses the millis so that only the top if() can be true
        previousBubbleState = LOW;
    }
}

int bubbleCounter::pinVal()
{
    return analogRead(bubblePin) > threshold;
}

void bubbleCounter::rollingAverage()
{
    min5intervals[0]++;
}

 int bubbleCounter::BPH()
{
    int _BPH = 0;

    for (int i = 0; i < 11; i++)
    {
        _BPH += min5intervals[i];
    }

    if (nextRollTime < millis())
    {

        for (int i = 0; i < 11; i++)
        {
            min5intervals[i + 1] = min5intervals[i];
        }

        min5intervals[0] = 0;

        nextRollTime = millis() + (3600000) / 12;
    }

    return _BPH;
}
