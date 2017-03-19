#include "Wire.h"
#include <SPI.h>
#include <SD.h>
#include <Arduino.h>

#define SDpin 10
String P[6] = {"0"};

void updateCalVars() {

    while (!SD.begin(SDpin)) {   //Wait for SD card
    // could write a message to the user regarding inserting SD card.

  }

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

    else {
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

void setup() {

  updateCalVars();

  Serial.begin(9600);
  while(!Serial){} // wait for serial link
  Serial.println("Coms port connected");

}

void loop() {

}
