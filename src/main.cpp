#include <Arduino.h>
#include <Logger.h>
#include <LCDisplay.h>
#include <bubbleCounter.h>

int BubblePinVal = 0;
int pinValMax = 0;

/*
  SD card read/write

 This example shows how to read and write data to and from an SD card file
 The circuit:
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)

 created   Nov 2010
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe

 This example code is in the public domain.

 */
bubbleCounter bubble(A3); // choose the pin number
Logger SD_log;       //this number does nothing, i just need it with a constructor for some reason
LCDisplay LCD(1);

void setup()
{
    Serial.begin(115200);
    LCD.begin();
    SD_log.begin();
    SD_log.record("Bubble per hour (BPH)"); //title at the top fo the coloumn
   // Serial.println("About to enter Loop()");
}

void loop()
{
   
    bubble.run();             // for the counter to work this needs to be in the loop
    SD_log.run(bubble.BPH()); // the value in the brackets will get logged
    LCD.run("Time:", String(SD_log.timeShort()),"BPH:",String(bubble.BPH()));

}