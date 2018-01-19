#include <Arduino.h>
#include <bubbleCounter.h>

bubbleCounter::bubbleCounter(int pinNo)
{
    pinMode(pinNo, INPUT); // sets the pin mode

    bubblePin = pinNo; // makes the pin No avalible later on

    // Serial.println("ending the threshold analasis");
    
    nextRollTime = millis() + (3600000) / 12;
}

void bubbleCounter::run()
{
    bool bubbleState = analogRead(bubblePin) > threshold;
    
    bool debounce = debounceTime > millis();

    if (!previousBubbleState && bubbleState && !debounce)
    {
        debounceTime = millis() + 5; // start timmer
        previousBubbleState = HIGH; // this prevous state locks out this if()
    }
    if (previousBubbleState && bubbleState && debounce) // only act if bubblestate has been high for 5 millis().
    {
        debounceTime = millis() +2000; // start timmer to lock out this if() for 2 secs
        count++;
        min5intervals[0]++;
    }
    if (previousBubbleState && !bubbleState && debounce)
    {
        debounceTime = millis() - 1; // this minuses the millis so that only the top if() can be true
        previousBubbleState = LOW; // this means only the top if() can be true
    }
    
    // the if statement below this mark, moves everything in the array up one level, then deletes the value in [0]
    
    if (nextRollTime < millis())
    {
        for (int i = 0; i < 11; i++)
        {
            min5intervals[i + 1] = min5intervals[i];
        }

        min5intervals[0] = 0;

        nextRollTime = millis() + (3600000) / 12;
    }
}

 unsigned int bubbleCounter::BPH()
{
   unsigned int _BPH = 0;

    for (int i = 0; i < 11; i++)
    {
        _BPH += min5intervals[i];
    }
    return _BPH;
}
