#include <Arduino.h>
#include <LCDisplay.h>
#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>

LiquidCrystal_PCF8574 lcd(0x27); // set the LCD address to 0x27 for a 16 chars and 2 line display

LCDisplay::LCDisplay(int i)
{
}

void LCDisplay::begin()
{
    Wire.begin();
    Wire.beginTransmission(0x27);

    lcd.begin(16, 2); // initialize the lcd

    lcd.setBacklight(255);
}
/*
void LCDExamples()
{

    if (show == 0)
    {
        lcd.setBacklight(255);
        lcd.home();
        lcd.clear();
        lcd.print("Hello LCD");
        delay(1000);

        lcd.setBacklight(0);
        delay(400);
        lcd.setBacklight(255);
    }
    else if (show == 1)
    {
        lcd.clear();
        lcd.print("Cursor On");
        lcd.cursor();
    }
    else if (show == 2)
    {
        lcd.clear();
        lcd.print("Cursor Blink");
        lcd.blink();
    }
    else if (show == 3)
    {
        lcd.clear();
        lcd.print("Cursor OFF");
        lcd.noBlink();
        lcd.noCursor();
    }
    else if (show == 4)
    {
        lcd.clear();
        lcd.print("Display Off");
        lcd.noDisplay();
    }
    else if (show == 5)
    {
        lcd.clear();
        lcd.print("Display On");
        lcd.display();
    }
    else if (show == 7)
    {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("*** first line.");
        lcd.setCursor(0, 1);
        lcd.print("*** second line.");
    }
    else if (show == 8)
    {
        lcd.scrollDisplayLeft();
    }
    else if (show == 9)
    {
        lcd.scrollDisplayLeft();
    }
    else if (show == 10)
    {
        lcd.scrollDisplayLeft();
    }
    else if (show == 11)
    {
        lcd.scrollDisplayRight();
    } // if

    delay(2000);
    show = (show + 1) % 12;
}
*/

String LCDisplay::consonate(String Left, String Right)
{

    int NoOfSpaces = 16 - (Left.length() + Right.length());

    String Line = Left;

    for (int index = 0; index < NoOfSpaces; index++)
    {
        Line += " ";
    }

    Line += Right;

    return Line;
}

void LCDisplay::run(String TopLeft, String TopRight, String BottomLeft, String BottomRight)
{
    String LineOne = consonate(TopLeft, TopRight);
    String LineTwo = consonate(BottomLeft, BottomRight);

    if (PrevousLine1 == LineOne && PrevousLine2 == LineTwo)
    {
        return;
    }
    else
    {
        if (nextRefresh < millis())
        {

            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print(LineOne);
            lcd.setCursor(0, 1);
            lcd.print(LineTwo);

            PrevousLine1 = LineOne;
            PrevousLine2 = LineTwo;

            nextRefresh = refreshRate + millis();
        }
    }
}