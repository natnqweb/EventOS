#define DEBUG
#include <EventOS.h>

static const int ledPin = 13;
bool ledState = true;

void ChangeLedState()
{
    LOGLN("pin state has changed");
    ledState = !ledState;
    digitalWrite(ledPin, ledState);
}

void PrintPinStateIsFalling()
{
    LOGLN("Pin State is falling");
}

void PrintPinStateIsRaising()
{
    LOGLN("Pin State is Rising");
}

PROGRAM_SETUP(115200)
{
    pinMode(ledPin, OUTPUT);
    // this is purely implemented in software it has nothing to do with hardware interrupts
    AddEventListener(_PIN_D2, ON_CHANGE_EVENT, ChangeLedState);
    AddEventListener(_PIN_D2, ON_RISING_EDGE_EVENT, ChangeLedState);
    AddEventListener(_PIN_D2, ON_FALLING_EDGE_EVENT, ChangeLedState);
}

PROGRAM_LOOP()
{

}
