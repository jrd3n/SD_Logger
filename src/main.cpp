#include <Arduino.h>
#include <Logger.h>

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

Logger SD_log(123); //this number does nothing, i just need it with a constructor for some reason

void setup()
{

    Serial.begin(115200);

    SD_log.begin();

    /*
    for (int index = 0; index < 100; index++)
    {
        Serial.println(index);
    }

    */

    SD_log.record();

    Serial.println("About to enter Loop()");
}

void loop()
{
    SD_log.run(123); // the value in the brackets will get logged

    //  delay(300);
}