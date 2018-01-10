#include <Arduino.h>
#include <funkyTime.h>
#include <DS1307.h>

uint8_t sec, min, hour, day, month;
uint16_t year;

DS1307 rtc;

void startRTC()
{
    rtc.start();
}

String tenBelow(int input)
{

    if (input < 10)
    {
        String lessthanTen = "";

        lessthanTen += "0";
        lessthanTen += String(input);

        return lessthanTen;
    }
    else
    {
        return String(input);
    }
}

String timeLong()
{

    rtc.get(&sec, &min, &hour, &day, &month, &year);

    String timeString = "";

    timeString += tenBelow(hour);
    timeString += ":";
    timeString += tenBelow(min);
    timeString += ":";
    timeString += tenBelow(sec);

    timeString += " ";
    timeString += tenBelow(day);
    timeString += "-";
    timeString += tenBelow(month);
    timeString += "-";
    timeString += year;

    return timeString;
}

String timeShort()
{

    rtc.get(&sec, &min, &hour, &day, &month, &year);

    String timeString = "";

    timeString += tenBelow(hour);
    timeString += ":";
    timeString += tenBelow(min);
    timeString += ":";
    timeString += tenBelow(sec);

    return timeString;
}