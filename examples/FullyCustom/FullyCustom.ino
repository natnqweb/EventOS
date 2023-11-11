#define DEBUG
#include <EventOS.h>
// for this example Custom mapping pins in esp8266
// you can custom map any board as long as it is supported by arduino framework
// esp32 , esp8266 .. all arduino.. raspberrypi .. stm ... etc... 
static const ArrSizeType numberOfPins{ 2 };
#define PIN_A 4
#define PIN_B 5
PinType customPinMap[numberOfPins]
{
    //* REAL ACTUAL BOARD PIN - pin that you pass for example to digitalRead(REAL ACTUAL BOARD PIN)
    ADD_PIN(PIN_A)
    ADD_PIN(PIN_B)
};

// define PinEvent array it hold your events
PinEvent customEvents[numberOfPins]{};

void PinAFallingEvent()
{
    LOG("PinA state changed from 1 to ");
    LOGLN(GetPinState(PIN_A));
}

void PinBFallingEvent()
{
    LOG("PinB state changed from 1 to ");
    LOGLN(GetPinState(PIN_B));
}
// OVERRIDE DEFAULT PROGRAM_SETUP
__OVERRIDE void PROGRAM_SETUP(115200)
{
    // this ovverrides all default events with custom events
    ChangeEvents(customPinMap, customEvents, numberOfPins);

    //USER CODE
    //HERE ...
    AddEventListener(PIN_A, ON_FALLING_EDGE_EVENT, PinAFallingEvent);
    AddEventListener(PIN_B, ON_FALLING_EDGE_EVENT, PinBFallingEvent);
    LOGLN("program started");
}

void PROGRAM_LOOP()
{

}
