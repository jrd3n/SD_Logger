#include <Arduino.h>
#include <bubbleCounter.h>

#define hour 3600000

bubbleCounter::bubbleCounter(int pinNo)
{
    pinMode(pinNo, INPUT); // sets the pin mode

    bubblePin = pinNo; // makes the pin No avalible later on

    // Serial.println("ending the threshold analasis");
}

void bubbleCounter::run()
{
    bool bubbleState = analogRead(bubblePin) > threshold;

    bool debounce = debounceTime < millis();
    //debouceState = debounce;

    if (!previousBubbleState && bubbleState && debounce)
    {
        debounceTime = millis() + 2; // start timmer
        previousBubbleState = true;  // this prevous state locks out this if()
    }
    if (previousBubbleState && bubbleState && debounce) // only act if bubblestate has been high for 5 millis().
    {
        BPHCalc();
        debounceTime = millis() + 2000; // start timmer to lock out this if() for 2 secs
    }

    if (previousBubbleState && !bubbleState && debounce)
    {
        debounceTime = millis() - 1; // this minuses the millis so that only the top if() can be true
        previousBubbleState = false; // this means only the top if() can be true
    }
}
/*
unsigned int bubbleCounter::BPH()
{
    unsigned int _BPH = 0;

    for (int i = 11; i >= 0; i--)
    {
        //  _BPH += min5intervals[i];
    }

    return _BPH;
}
*/
void bubbleCounter::BPHCalc()
{
    unsigned long bubbleTime = millis();
    int countInArray = 1;
    unsigned long timeBetweenTotal = 0;

    if (lastBubbleTime == 0) // if there is no previous bubble time
    {
        BPH = 1;
        lastBubbleTime = bubbleTime; // this will give lastBubbleTime a value higher than 0, so this if is locked out
        return;
    }
    else
    {
        for (int i = 9; i >= 1; i--) // this will move all the values up on in the array
        {
            timeBetween[i] = timeBetween[i - 1];
            if (!timeBetween[i] == 0) // this counts how many array members have a value, used for the number in avarage.
            {
                countInArray++;
                timeBetweenTotal += timeBetween[i];
            }
        }
        timeBetween[0] = bubbleTime - lastBubbleTime;
        timeBetweenTotal += timeBetween[0];
        lastBubbleTime = bubbleTime;

        // everything  abouve this line, in the else, put the time between values into the array, and then move it up one slot

        unsigned int timeBetweenAverage = timeBetweenTotal / countInArray; // this will get average of the time beweens

        BPH = hour / timeBetweenAverage;
    }
}