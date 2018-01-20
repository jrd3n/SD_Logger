#include "Arduino.h"
#include "Logger.h"
#include <SPI.h>
#include <SD.h>
#include <DS1307.h>

DS1307 rtc;
File myFile;

Logger::Logger()
{
}

void Logger::record(String title)
{
    recording = true;

    logFile = timeFileName();

    logFile += ".csv";

    myFile = SD.open(logFile, FILE_WRITE);

    myFile.print("Time");
    myFile.print(",");
    myFile.println(title);
 //   Serial.println("write sucseccful");

    myFile.close(); // close the file:
}
//void Logger::pause() {}
//void Logger::stop() {}

void Logger::begin()
{
    if (!SD.begin(4))
    {
        Serial.println("Card failed, or not present");
        // don't do anything more:
        while (1)
        {
        };
    }

    rtc.start();

} //

void Logger::run(double logVal)
{
    if (nextLogTime < millis())
    {
        myFile = SD.open(logFile);

        if (myFile)
        {
         //   Serial.print(logFile);
          //  Serial.println(" exists.");
            myFile.close();

            myFile = SD.open(logFile, FILE_WRITE);

            if (myFile)
            {

                myFile.print(timeLong());
                myFile.print(",");
                myFile.println(logVal);
              //  Serial.println("write sucseccful");

                myFile.close(); // close the file:
            }
        }
        else
        {
            Serial.print(logFile);
          //  Serial.println(" doesn't exist.");

          //  Serial.println("Writing to dump");

            DumpNumber += 1;

            //record();
        }

        nextLogTime = interval + millis();
    }
}

String Logger::tenBelow(int input)
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

String Logger::timeLong()
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

String Logger::timeShort()
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

String Logger::timeFileName()
{

    rtc.get(&sec, &min, &hour, &day, &month, &year);

    String timeString = "";

    timeString += tenBelow(hour);
    timeString += "-";
    timeString += tenBelow(min);
    timeString += "-";
    timeString += tenBelow(sec);

    return timeString;
}