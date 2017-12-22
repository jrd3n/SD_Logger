#include <Arduino.h>
#include <funkyTime.h> // all the functions and vars for the time
#include <LCDisplay.h> // all the funtions for the LCD
#include <menu.h>

void setup()
{

    Serial.begin(115200);
    menuSetup(2); //PIN NUMBER FOR MENU INPUT
    startRTC();
    LCDbegin();

    // pinMode(trialpinNo, INPUT);
}

void loop()
{

    menuRun();

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