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

    if (!previousBubbleState && bubbleState) // only register one buble per bubble, rather than rampng up numbers when high
    {
        debounceTime = millis() + 5; // start timmer
    }
    if (!previousBubbleState && bubbleState && debounceTime > millis())
    {
        previousBubbleState = HIGH;
        debounceTime = millis() + 2000; // start timmer
    }
    if (!bubbleState && previousBubbleState && debounceTime > millis())
    {
        count++;
        rollingAverage(1);
        previousBubbleState = LOW;
    }
}

int bubbleCounter::pinVal()
{
    return analogRead(bubblePin) > threshold;
}

void bubbleCounter::rollingAverage(double hours)
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