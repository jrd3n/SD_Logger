#include "Wire.h"
#include <SPI.h>
#include <SD.h>
#include <Arduino.h>

#include <DS1307.h>

DS1307 rtc;

#define SDpin 10
String P[6] = {"0"};

uint8_t sec, min, hour, day, month;
uint16_t year;

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void updateCalVars() {

  File calStream = SD.open("cal.txt");

  if(calStream){
    while(calStream) {
      for (int N = 0; N < 6; N++){
        calStream.readStringUntil('=');
        P[N] = calStream.readStringUntil(';');
        P[N].trim();
      }
      calStream.close();
    }
  }

  else {
    File calWrite = SD.open("cal.txt",FILE_WRITE);
    if (calWrite) {
      calWrite.println("P0 = 0;//Offset");
      calWrite.println("P1 = 0;//X * P1");
      calWrite.println("P2 = 0;//P2 * (X^2)");
      calWrite.println("P3 = 0;//P3 * (X^3)");
      calWrite.println("P4 = 0;//P4 * (X^4)");
      calWrite.println("P5 = 0;//P5 * (X^5)");
      calWrite.println("P6 = 0;//P6 * (X^6)");
      calWrite.close();
    }


  }

}

short polyMap (double X) {

  double Y = P[6].toInt() * pow(X, 6);
  Y = + P[5].toInt() * pow(X, 5);
  Y = + P[4].toInt() * pow(X, 4);
  Y = + P[3].toInt() * pow(X, 3);
  Y = + P[2].toInt() * pow(X, 2);
  Y = + P[1].toInt() * X;

  return Y;

}

void UpDateTime() {

  File timeStream = SD.open("Time.txt");

  if(timeStream){
    while(timeStream) {

      String T[5] = {"0"};

      for (int N = 0; N < 4; N++){
        timeStream.readStringUntil('=');
        T[N] = timeStream.readStringUntil(';');
        T[N].trim();
      }
      timeStream.close();

      year = T[0].toInt();
      month = T[1].toInt();
      day = T[2].toInt();
      hour = T[3].toInt();
      min = T[4].toInt();
      sec = T[5].toInt();

    }
  }

  else {
    File TimeWrite = SD.open("time.txt",FILE_WRITE);
    if (TimeWrite) {
      TimeWrite.println("Year = 0; Example 2017");
      TimeWrite.println("Month = 0; Example 3, for march");
      TimeWrite.println("Day = 0; Please enter a value between 1 and 31");
      TimeWrite.println("hour = 0; Please enter a value between 0 and 23");
      TimeWrite.println("Minute = 0; Please enter a value between 0 and 59");
      TimeWrite.println("Seconds = 0; as above");
      TimeWrite.close();
    }

  }

  if(!year && !month && !hour && !min && !sec) {

    Serial.println("Yes they all equal zero");
    return;

  }

  else {

    rtc.set(sec, min, hour, day, month, year); //08:00:00 24.12.2014 //sec, min, hour, day, month, year

     SD.remove("time.txt");

    File TimeWrite = SD.open("time.txt",FILE_WRITE);
    if (TimeWrite) {
      TimeWrite.println("Year = 0; Example 2017");
      TimeWrite.println("Month = 0; Example 3, for march");
      TimeWrite.println("Day = 0; Please enter a value between 1 and 31");
      TimeWrite.println("hour = 0; Please enter a value between 0 and 23");
      TimeWrite.println("Minute = 0; Please enter a value between 0 and 59");
      TimeWrite.println("Seconds = 0; as above");
      TimeWrite.close();
    }
  }
}

void setup() {

  //start RTC
  rtc.start();

  lcd.init();                      // initialize the lcd
  lcd.backlight();

  Serial.begin(9600);
  while(!Serial){} // wait for serial link
  Serial.println("Coms port connected");

  while (!SD.begin(SDpin)) {   //Wait for SD card
  // could write a message to the user regarding inserting SD card.
  }
  updateCalVars();
  UpDateTime();
}

void loop() {

    //get time from RTC
  rtc.get(&sec, &min, &hour, &day, &month, &year);

String lineOne = String(hour) + ":" + String(min) + ":" + String(sec);

  lcd.clear();
  lcd.print(lineOne);

    //wait a second
  delay(1000);
}
