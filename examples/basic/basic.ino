#define DEBUG
#include <EventOS.h>
// documentation
// https://github.com/natnqweb/EventOS

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

void PrintPinStateIsRising()
{
    LOGLN("Pin State is Rising");
}

void PROGRAM_SETUP(115200)
{
    pinMode(ledPin, OUTPUT);
    // this is purely implemented in software it has nothing to do with hardware interrupts
    AddEventListener(2, ON_CHANGE_EVENT, ChangeLedState); // event fired when state is changing 0 -> 1 or 1 -> 0
    AddEventListener(2, ON_RISING_EDGE_EVENT, PrintPinStateIsRising); // event fired on pin rising edge 0 -> 1
    AddEventListener(2, ON_FALLING_EDGE_EVENT, PrintPinStateIsFalling); // event fired on pin falling edge1 -> 0
}

void PROGRAM_LOOP()
{

}
