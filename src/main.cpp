#include <Arduino.h>
#include <funkyTime.h> // all the functions and vars for the time
// #include <LCDisplay.h> // all the funtions for the LCD
// #include <menu.h>

#include <Logger.h>

String TimeDate = "";

Logger SDCard(&TimeDate);

void setup()
{

    Serial.begin(115200);

    // startRTC();

    SDCard.begin();

    // pinMode(trialpinNo, INPUT);
}

void loop()
{

    SDCard.run(); // this needs to be in the loop

    /*
    while (digitalRead(trialpinNo))
    {
        LCDisplay("Ping", " ");
    }

    LCDisplay("Pong", "");

    */
    // Serial.println(timeLong());

    //  menuRun();

    // put your main code here, to run repeatedly:
}