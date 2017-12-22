#ifndef menu_h
#define menu_h

#include <LCDisplay.h>
#include <funkyTime.h>

int _ButtonPin = 0;

int menu[2] = {1, 0};
int NoOfMenus = 3;

int lastButtonState = 0; // while button press....

void menuSetup(int ButtonPin)
{
    pinMode(ButtonPin, INPUT);

    _ButtonPin = ButtonPin;
}

bool bottonPress()
{
    while (!digitalRead(_ButtonPin))
    {
        lastButtonState = true;
        return true;
    }

    lastButtonState = false;
    return false;
}
void ToggleMenu() // THIS IS DESIGNED AS A CONTROLLER FOR THE CURSOR
{
    if (menu[0] < NoOfMenus) // IF (WE ARE ON THE LAST SCREEN)
    {
        menu[0] = 0; // RESET COUNTER
    }
    else
    {
        menu[0] += 1; // ADD ONE TO THE COUNTS
    }
}
void menuRun()
{
    switch (menu[0])
    {
    case 0:                    // welcome page
        while (!bottonPress()) // if the button is not pressed
        {
            LCDisplay("hello, welcome", "to SD logger");
        }
        ToggleMenu();

    case 1:
        while (!bottonPress())
        { // if the button is not pressed
            LCDisplay("Hello world", timeShort());
        }
        ToggleMenu();

    case 2:
        while (!bottonPress())
        { // if the button is not pressed
            LCDisplay("hi", "low");
        }
        ToggleMenu();
    }
}

#endif